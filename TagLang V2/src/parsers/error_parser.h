#pragma once
#include "base_parser.h"

class ErrorParser : public BaseParser {
public:
    using BaseParser::BaseParser;

    NodePtr parse() override {
        auto block = std::make_unique<ErrorBlockNode>();
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
        if (check(TokenType::IDENTIFIER) && current().value == "try") {
            consume();
            skipNewlines();
            expect(TokenType::LBRACE, "@error: expected '{' after try");
            skipNewlines();

            auto node = std::make_unique<TryCatchNode>();

            while (!check(TokenType::RBRACE) && !isEnd()) {
                skipNewlines();
                if (check(TokenType::RBRACE)) break;
                node->tryBody.push_back(parseStmt());
            }
            expect(TokenType::RBRACE, "@error: expected '}' to close try");
            skipNewlines();

            if (check(TokenType::IDENTIFIER) && current().value == "catch") {
                consume();
                expect(TokenType::LPAREN, "@error: expected '(' after catch");
                node->exceptionType = expect(TokenType::IDENTIFIER, "@error: expected exception type").value;
                node->exceptionVar  = expect(TokenType::IDENTIFIER, "@error: expected exception var").value;
                expect(TokenType::RPAREN, "@error: expected ')'");
                skipNewlines();
                expect(TokenType::LBRACE, "@error: expected '{' after catch(...)");
                skipNewlines();
                while (!check(TokenType::RBRACE) && !isEnd()) {
                    skipNewlines();
                    if (check(TokenType::RBRACE)) break;
                    node->catchBody.push_back(parseStmt());
                }
                expect(TokenType::RBRACE, "@error: expected '}' to close catch");
                skipNewlines();
            }

            if (check(TokenType::IDENTIFIER) && current().value == "finally") {
                consume();
                skipNewlines();
                expect(TokenType::LBRACE, "@error: expected '{' after finally");
                skipNewlines();
                while (!check(TokenType::RBRACE) && !isEnd()) {
                    skipNewlines();
                    if (check(TokenType::RBRACE)) break;
                    node->finallyBody.push_back(parseStmt());
                }
                expect(TokenType::RBRACE, "@error: expected '}' to close finally");
                skipNewlines();
            }
            return node;
        }

        if (check(TokenType::IDENTIFIER) && current().value == "throw") {
            consume();
            auto n = std::make_unique<ThrowNode>();
            n->exceptionType = expect(TokenType::IDENTIFIER, "@error: expected exception type").value;
            expect(TokenType::LPAREN, "@error: expected '('");
            if (check(TokenType::STRING))
                n->message = consume().value;
            expect(TokenType::RPAREN, "@error: expected ')'");
            skipNewlines();
            return n;
        }

        if (check(TokenType::KW_PRINT)) {
            consume();
            expect(TokenType::LPAREN, "@error: expected '('");
            auto n = std::make_unique<ErrorPrintNode>();
            n->expr = collectUntil(TokenType::RPAREN);
            expect(TokenType::RPAREN, "@error: expected ')'");
            skipNewlines();
            return n;
        }

        throw std::runtime_error("@error: unexpected '" + current().value +
                                 "' at line " + std::to_string(current().line));
    }

    std::string collectUntil(TokenType stop) {
        std::string r;
        while (!check(stop) && !isEnd()) {
            if (current().type == TokenType::STRING) r += "\"" + current().value + "\"";
            else r += current().value;
            consume();
        }
        while (!r.empty() && r.back()==' ') r.pop_back();
        return r;
    }
};
