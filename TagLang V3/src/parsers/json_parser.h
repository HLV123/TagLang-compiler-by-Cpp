#pragma once
#include "base_parser.h"

class JsonParser : public BaseParser {
public:
    using BaseParser::BaseParser;

    NodePtr parse() override {
        auto block = std::make_unique<JsonBlockNode>();
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
      
        if (check(TokenType::KW_PRINT)) {
            consume();
            expect(TokenType::LPAREN, "@json: expected '('");
            auto n = std::make_unique<JsonStringifyNode>();
        
            n->varName = "";
            n->objName = collectUntil(TokenType::RPAREN);
            expect(TokenType::RPAREN, "@json: expected ')'");
            skipNewlines();
           
            auto p = std::make_unique<ErrorPrintNode>(); 
            p->expr = n->objName;
            return p;
        }

        if (!check(TokenType::IDENTIFIER))
            throw std::runtime_error("@json: expected declaration at line " +
                                     std::to_string(current().line));

        std::string typeOrName = consume().value;

        if (typeOrName == "obj") {
            std::string name = expect(TokenType::IDENTIFIER, "@json: expected object name").value;
            expect(TokenType::ASSIGN, "@json: expected '='");
            skipNewlines();

            if (check(TokenType::IDENTIFIER) && current().value == "JSON") {
                consume(); 
                expect(TokenType::DOT, "@json: expected '.'");
                std::string method = expect(TokenType::IDENTIFIER, "@json: expected method").value;
                if (method == "parse") {
                    expect(TokenType::LPAREN, "@json: expected '('");
                    auto n = std::make_unique<JsonParseNode>();
                    n->varName = name;
                    n->jsonStr = collectUntil(TokenType::RPAREN);
                    expect(TokenType::RPAREN, "@json: expected ')'");
                    skipNewlines();
                    return n;
                }
            }

            expect(TokenType::LBRACE, "@json: expected '{'");
            auto obj = std::make_unique<JsonObjNode>();
            obj->name = name;
            skipNewlines();
            while (!check(TokenType::RBRACE) && !isEnd()) {
                skipNewlines();
                if (check(TokenType::RBRACE)) break;
                auto field = std::make_unique<JsonFieldNode>();
                field->key = expect(TokenType::IDENTIFIER, "@json: expected field name").value;
                expect(TokenType::COLON, "@json: expected ':'");
                parseFieldValue(*field);
                obj->fields.push_back(std::move(field));
                skipNewlines();
                match(TokenType::COMMA);
                skipNewlines();
            }
            expect(TokenType::RBRACE, "@json: expected '}'");
            skipNewlines();
            return obj;
        }

        if (typeOrName == "str") {
            std::string name = expect(TokenType::IDENTIFIER, "@json: expected var name").value;
            expect(TokenType::ASSIGN, "@json: expected '='");
       
            std::string jsIdent = expect(TokenType::IDENTIFIER, "@json: expected JSON").value;
            expect(TokenType::DOT, "@json: expected '.'");
            std::string method = expect(TokenType::IDENTIFIER, "@json: expected stringify").value;
            expect(TokenType::LPAREN, "@json: expected '('");
            auto n = std::make_unique<JsonStringifyNode>();
            n->varName = name;
            n->objName = collectUntil(TokenType::RPAREN);
            expect(TokenType::RPAREN, "@json: expected ')'");
            skipNewlines();
            return n;
        }

        throw std::runtime_error("@json: unexpected token '" + typeOrName + "'");
    }

    void parseFieldValue(JsonFieldNode& f) {
        const Token& t = current();
        if (t.type == TokenType::STRING) {
            f.value = consume().value; f.valueType = "string"; return;
        }
        if (t.type == TokenType::KW_TRUE || t.type == TokenType::KW_FALSE) {
            f.value = consume().value; f.valueType = "bool"; return;
        }
        if (t.type == TokenType::MINUS && peek().type == TokenType::NUMBER) {
            consume();
            f.value = "-" + consume().value;
            f.valueType = f.value.find('.')!=std::string::npos?"float":"int";
            return;
        }
        if (t.type == TokenType::NUMBER) {
            f.value = consume().value;
            f.valueType = f.value.find('.')!=std::string::npos?"float":"int";
            return;
        }
        throw std::runtime_error("@json: unexpected field value '" + t.value + "'");
    }

    std::string collectUntil(TokenType stop) {
        std::string r;
        while (!check(stop) && !isEnd()) { r += current().value; consume(); }
        while (!r.empty() && r.back()==' ') r.pop_back();
        return r;
    }
};
