#pragma once
#include "base_parser.h"

class IterParser : public BaseParser {
public:
    using BaseParser::BaseParser;

    NodePtr parse() override {
        auto block = std::make_unique<IterBlockNode>();
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
            expect(TokenType::LPAREN, "@iter: expected '('");
            auto n = std::make_unique<IterPrintNode>();
            if (check(TokenType::STRING))
                n->expr = "\"" + consume().value + "\"";
            else
                n->expr = collectUntil(TokenType::RPAREN);
            expect(TokenType::RPAREN, "@iter: expected ')'");
            skipNewlines();
            return n;
        }

        if (check(TokenType::IDENTIFIER) && current().value == "break") {
            consume();
            auto n = std::make_unique<BreakNode>();
            if (check(TokenType::IDENTIFIER) && current().value[0]=='\'') {
                n->label = consume().value.substr(1);
            } else if (check(TokenType::IDENTIFIER)) {

                n->label = "";
            }
            skipNewlines();
            return n;
        }

        if (check(TokenType::IDENTIFIER) && current().value == "loop") {
            consume();
            skipNewlines();
            expect(TokenType::LBRACE, "@iter: expected '{'");
            skipNewlines();
            auto n = std::make_unique<LoopNode>();
            while (!check(TokenType::RBRACE) && !isEnd()) {
                skipNewlines();
                if (check(TokenType::RBRACE)) break;
                n->body.push_back(parseStmt());
            }
            expect(TokenType::RBRACE, "@iter: expected '}'");
            skipNewlines();
            return n;
        }

        if (check(TokenType::KW_WHILE)) {
            consume();
            auto n = std::make_unique<IterWhileNode>();
            n->condition = collectUntilBrace();
            skipNewlines();
            expect(TokenType::LBRACE, "@iter: expected '{'");
            skipNewlines();
            while (!check(TokenType::RBRACE) && !isEnd()) {
                skipNewlines();
                if (check(TokenType::RBRACE)) break;
                n->body.push_back(parseStmt());
            }
            expect(TokenType::RBRACE, "@iter: expected '}'");
            skipNewlines();
            return n;
        }

        std::string loopLabel = "";
        if (check(TokenType::IDENTIFIER) && !current().value.empty()
            && current().value[0] == '\'') {
            loopLabel = current().value.substr(1); 
            consume();
            expect(TokenType::COLON, "@iter: expected ':' after label");
        }

        if (check(TokenType::IDENTIFIER) && current().value == "for") {
            consume();
            std::string var = expect(TokenType::IDENTIFIER, "@iter: expected loop var").value;
            if (!check(TokenType::IDENTIFIER) || current().value != "in")
                throw std::runtime_error("@iter: expected 'in' after loop variable");
            consume(); 

            bool isRef = false;
            if (check(TokenType::IDENTIFIER) && current().value[0]=='&') {
            }

            std::string from, to;
            bool inclusive = false;
            std::string collection = "";

            if (check(TokenType::NUMBER)) {
                from = consume().value;
                if (check(TokenType::DOT) && peek().type == TokenType::DOT) {
                    consume(); consume(); 
                    if (check(TokenType::ASSIGN)) { consume(); inclusive = true; } 
                    to = collectUntilBrace();
                } else {
                    collection = from; from = "";
                }
            } else {
                collection = collectUntilBrace();
                if (!collection.empty() && collection[0]=='&') collection = collection.substr(1);
            }

            skipNewlines();
            expect(TokenType::LBRACE, "@iter: expected '{'");
            skipNewlines();

            if (!collection.empty()) {
                auto n = std::make_unique<ForInNode>();
                n->var = var; n->collection = collection; n->label = loopLabel;
                while (!check(TokenType::RBRACE) && !isEnd()) {
                    skipNewlines();
                    if (check(TokenType::RBRACE)) break;
                    n->body.push_back(parseStmt());
                }
                expect(TokenType::RBRACE, "@iter: expected '}'");
                skipNewlines();
                return n;
            } else {
                auto n = std::make_unique<ForRangeNode>();
                n->var = var; n->from = from; n->to = to;
                n->inclusive = inclusive; n->label = loopLabel;
                while (!check(TokenType::RBRACE) && !isEnd()) {
                    skipNewlines();
                    if (check(TokenType::RBRACE)) break;
                    n->body.push_back(parseStmt());
                }
                expect(TokenType::RBRACE, "@iter: expected '}'");
                skipNewlines();
                return n;
            }
        }

        throw std::runtime_error("@iter: unexpected '" + current().value +
                                 "' at line " + std::to_string(current().line));
    }

    std::string collectUntil(TokenType stop) {
        std::string r;
        while (!check(stop) && !isEnd()) { r += current().value; consume(); }
        while (!r.empty() && r.back()==' ') r.pop_back();
        return r;
    }

    std::string collectUntilBrace() {
        std::string r;
        while (!check(TokenType::LBRACE) && !check(TokenType::NEWLINE) && !isEnd()) {
            r += current().value; consume();
        }
        while (!r.empty() && r.back()==' ') r.pop_back();
        return r;
    }
};
