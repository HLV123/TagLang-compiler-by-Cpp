#pragma once
#include "base_parser.h"

class RScriptParser : public BaseParser {
public:
    using BaseParser::BaseParser;

    NodePtr parse() override {
        auto block = std::make_unique<RScriptBlockNode>();
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
            expect(TokenType::LPAREN, "@rscript: expected '(' after print");
            auto n = std::make_unique<RPrintNode>();
            n->expr = collectUntil(TokenType::RPAREN);
            expect(TokenType::RPAREN, "@rscript: expected ')'");
            skipNewlines();
            return n;
        }
        if (check(TokenType::IDENTIFIER)) {
            std::string name = consume().value;
            if (check(TokenType::LESS) && peek().type == TokenType::MINUS) {
                consume(); consume(); 

                if (check(TokenType::IDENTIFIER) && current().value == "c"
                    && peek().type == TokenType::LPAREN) {
                    consume(); 
                    consume(); 
                    auto vec = std::make_unique<RVecNode>();
                    vec->name = name;
                    while (!check(TokenType::RPAREN) && !isEnd()) {
                        skipNewlines();
                        if (check(TokenType::RPAREN)) break;
                        vec->elements.push_back(consume().value);
                        skipNewlines();
                        match(TokenType::COMMA);
                    }
                    expect(TokenType::RPAREN, "@rscript: expected ')' after c(");
                    skipNewlines();
                    return vec;
                }

                auto n = std::make_unique<RAssignNode>();
                n->lhs = name;
                if (check(TokenType::STRING))
                    n->rhs = "\"" + consume().value + "\"";
                else
                    n->rhs = collectUntil(TokenType::NEWLINE);
                skipNewlines();
                return n;
            }
        }
        throw std::runtime_error(
            "@rscript: unexpected token '" + current().value +
            "' at line " + std::to_string(current().line));
    }

    std::string collectUntil(TokenType stop) {
        std::string r;
        while (!check(stop) && !isEnd()) {
            r += current().value; consume();
        }
        while (!r.empty() && r.back()==' ') r.pop_back();
        return r;
    }
};
