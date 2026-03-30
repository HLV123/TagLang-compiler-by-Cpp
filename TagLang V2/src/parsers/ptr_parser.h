#pragma once
#include "base_parser.h"

class PtrParser : public BaseParser {
public:
    using BaseParser::BaseParser;

    NodePtr parse() override {
        auto block = std::make_unique<PtrBlockNode>();
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
            expect(TokenType::LPAREN, "@ptr: expected '('");
            auto n = std::make_unique<PtrPrintNode>();
            n->expr = collectUntil(TokenType::RPAREN);
            expect(TokenType::RPAREN, "@ptr: expected ')'");
            skipNewlines();
            return n;
        }

        if (check(TokenType::STAR)) {
            consume();
            std::string pname = expect(TokenType::IDENTIFIER, "@ptr: expected pointer name").value;
            expect(TokenType::ASSIGN, "@ptr: expected '='");
            auto n = std::make_unique<PtrDerefAssignNode>();
            n->ptrName = pname;
            n->value = collectUntil(TokenType::NEWLINE);
            skipNewlines();
            return n;
        }

        if (check(TokenType::IDENTIFIER) && current().value == "var") {
            consume(); 
            std::string name = expect(TokenType::IDENTIFIER, "@ptr: expected variable name").value;

            if (check(TokenType::STAR)) {
                consume();
                std::string type = expect(TokenType::IDENTIFIER, "@ptr: expected type").value;
                auto n = std::make_unique<PtrDeclNode>();
                n->name = name; n->type = type;
                skipNewlines();
                return n;
            }

            std::string type = expect(TokenType::IDENTIFIER, "@ptr: expected type").value;
            if (match(TokenType::ASSIGN)) {
                auto n = std::make_unique<PtrVarDeclNode>();
                n->name = name; n->type = type;
                n->value = collectUntil(TokenType::NEWLINE);
                skipNewlines();
                return n;
            }
            auto n = std::make_unique<PtrVarDeclNode>();
            n->name = name; n->type = type; n->value = "0";
            skipNewlines();
            return n;
        }

        if (check(TokenType::IDENTIFIER) && current().value == "func") {
            consume();
            std::string fname = expect(TokenType::IDENTIFIER, "@ptr: expected func name").value;
            expect(TokenType::LPAREN, "@ptr: expected '('");
            std::string pname = expect(TokenType::IDENTIFIER, "@ptr: expected param name").value;
            expect(TokenType::STAR, "@ptr: expected '*'");
            std::string ptype = expect(TokenType::IDENTIFIER, "@ptr: expected param type").value;
            expect(TokenType::RPAREN, "@ptr: expected ')'");
            skipNewlines();
            expect(TokenType::LBRACE, "@ptr: expected '{'");
            skipNewlines();

            auto fn = std::make_unique<PtrFuncNode>();
            fn->funcName = fname;
            fn->paramName = pname;
            fn->paramType = ptype;

            while (!check(TokenType::RBRACE) && !isEnd()) {
                skipNewlines();
                if (check(TokenType::RBRACE)) break;
                fn->body.push_back(parseStmt());
            }
            expect(TokenType::RBRACE, "@ptr: expected '}'");
            skipNewlines();
            return fn;
        }

        if (check(TokenType::IDENTIFIER)) {
            std::string name = consume().value;
            if (match(TokenType::ASSIGN)) {
                if (check(TokenType::IDENTIFIER) && peek().type == TokenType::IDENTIFIER) {
                }
                if (check(TokenType::AMPERSAND)) {
                    consume(); 
                    auto n = std::make_unique<PtrAssignAddrNode>();
                    n->ptrName = name;
                    n->varName = expect(TokenType::IDENTIFIER, "@ptr: expected var name after &").value;
                    skipNewlines();
                    return n;
                }
                std::string rhs = collectUntil(TokenType::NEWLINE);
                skipNewlines();
                auto n = std::make_unique<PtrDerefAssignNode>();
                n->ptrName = name; n->value = rhs;
                return n;
            }
            if (check(TokenType::LPAREN)) {
                consume();
                auto n = std::make_unique<PtrCallNode>();
                n->funcName = name;
                if (check(TokenType::AMPERSAND)) {
                    consume();
                    n->arg = "&" + expect(TokenType::IDENTIFIER, "@ptr: expected var").value;
                } else {
                    n->arg = collectUntil(TokenType::RPAREN);
                }
                expect(TokenType::RPAREN, "@ptr: expected ')'");
                skipNewlines();
                return n;
            }
        }

        throw std::runtime_error("@ptr: unexpected '" + current().value +
                                 "' at line " + std::to_string(current().line));
    }

    std::string collectUntil(TokenType stop) {
        std::string r;
        while (!check(stop) && !isEnd()) { r += current().value; consume(); }
        while (!r.empty() && r.back()==' ') r.pop_back();
        return r;
    }
};
