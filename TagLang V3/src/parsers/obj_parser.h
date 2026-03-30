#pragma once
#include "base_parser.h"

class ObjParser : public BaseParser {
public:
    using BaseParser::BaseParser;

    NodePtr parse() override {
        auto block = std::make_unique<ObjBlockNode>();
        skipNewlines();
        while (!isEnd()) {
            skipNewlines();
            if (isEnd()) break;
            block->stmts.push_back(parseStmt());
        }
        return block;
    }

private:
    NodePtr parseStmt() {
        if (check(TokenType::IDENTIFIER) && current().value == "print_row") {
            consume();
            expect(TokenType::LPAREN, "@obj: expected '('");
            auto n = std::make_unique<ObjPrintRowNode>();
            n->objName = expect(TokenType::IDENTIFIER, "@obj: expected object name").value;
            expect(TokenType::RPAREN, "@obj: expected ')'");
            skipNewlines();
            return n;
        }

        if (check(TokenType::KW_PRINT)) {
            consume();
            expect(TokenType::LPAREN, "@obj: expected '('");
            auto n = std::make_unique<ObjPrintNode>();
            n->expr = collectUntilRParen();
            expect(TokenType::RPAREN, "@obj: expected ')'");
            skipNewlines();
            return n;
        }

        if (!check(TokenType::IDENTIFIER))
            throw std::runtime_error("@obj: expected identifier at line " +
                                     std::to_string(current().line));

        std::string name = consume().value;

        if (match(TokenType::ASSIGN)) {
            if (check(TokenType::LBRACE) && peek().type == TokenType::RBRACE) {
                consume(); consume();
                auto n = std::make_unique<ObjTableNode>();
                n->name = name;
                skipNewlines();
                return n;
            }

            if (check(TokenType::LBRACE)) {
                consume(); // {
                skipNewlines();
                auto n = std::make_unique<ObjTableNode>();
                n->name = name;

                bool isKeyVal = (check(TokenType::IDENTIFIER) &&
                                 peek().type == TokenType::COLON);

                while (!check(TokenType::RBRACE) && !isEnd()) {
                    skipNewlines();
                    if (check(TokenType::RBRACE)) break;
                    if (isKeyVal) {
                        std::string k = consume().value;
                        expect(TokenType::COLON, "@obj: expected ':'");
                        std::string v = parseSimpleValue();
                        n->fields.push_back({k, v});
                    } else {
                       
                        std::string v = parseSimpleValue();
                        n->fields.push_back({"", v});
                    }
                    skipNewlines();
                    match(TokenType::COMMA);
                    skipNewlines();
                }
                expect(TokenType::RBRACE, "@obj: expected '}'");
                skipNewlines();
                return n;
            }
            if (check(TokenType::IDENTIFIER)) {
                std::string objName = consume().value;
                if (check(TokenType::DOT)) {
                    consume();
                    std::string method = expect(TokenType::IDENTIFIER, "@obj: expected method").value;
                    auto n = std::make_unique<ObjQueryNode>();
                    n->varName = name; n->objName = objName; n->method = method;
                    if (check(TokenType::LPAREN)) {
                        consume();
                        n->arg = collectUntil(TokenType::RPAREN);
                        expect(TokenType::RPAREN, "@obj: expected ')'");
                    }
                    skipNewlines();
                    return n;
                }
            
                auto n = std::make_unique<ObjSetFieldNode>();
                n->objName = name; n->field = ""; n->value = objName;
                skipNewlines();
                return n;
            }
        }

        if (check(TokenType::DOT)) {
            consume();
            std::string field = expect(TokenType::IDENTIFIER, "@obj: expected field name").value;
            expect(TokenType::ASSIGN, "@obj: expected '='");
            auto n = std::make_unique<ObjSetFieldNode>();
            n->objName = name; n->field = field; n->isBracket = false;
            n->value = parseSimpleValue();
            skipNewlines();
            return n;
        }

        if (check(TokenType::LBRACKET)) {
            consume();
            std::string key = collectUntil(TokenType::RBRACKET);
            expect(TokenType::RBRACKET, "@obj: expected ']'");
            expect(TokenType::ASSIGN, "@obj: expected '='");
            auto n = std::make_unique<ObjSetFieldNode>();
            n->objName = name; n->field = key; n->isBracket = true;
            n->value = parseSimpleValue();
            skipNewlines();
            return n;
        }

        throw std::runtime_error("@obj: unexpected after '" + name + "'");
    }

    std::string parseSimpleValue() {
        const Token& t = current();
        if (t.type == TokenType::STRING) return "\"" + consume().value + "\"";
        if (t.type == TokenType::KW_TRUE)  { consume(); return "true"; }
        if (t.type == TokenType::KW_FALSE) { consume(); return "false"; }
        if (t.type == TokenType::MINUS && peek().type == TokenType::NUMBER) {
            consume(); return "-" + consume().value;
        }
        if (t.type == TokenType::NUMBER) return consume().value;
        if (t.type == TokenType::IDENTIFIER) return consume().value;
        throw std::runtime_error("@obj: unexpected value token '" + t.value + "'");
    }

    std::string collectUntil(TokenType stop) {
        std::string r;
        while (!check(stop) && !isEnd()) { r += current().value; consume(); }
        while (!r.empty() && r.back()==' ') r.pop_back();
        return r;
    }

    std::string collectUntilRParen() {
        std::string r;
        while (!check(TokenType::RPAREN) && !isEnd()) {
            if (current().type == TokenType::STRING) r += "\"" + consume().value + "\"";
            else r += current().value, consume();
        }
        while (!r.empty() && r.back()==' ') r.pop_back();
        return r;
    }
};
