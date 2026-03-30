#pragma once
#include "base_parser.h"

class FuncParser : public BaseParser {
public:
    using BaseParser::BaseParser;

    NodePtr parse() override {
        auto block = std::make_unique<FuncBlockNode>();
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
     
        if (check(TokenType::IDENTIFIER) && current().value == "func") {
            return parseFuncDef();
        }

        if (check(TokenType::KW_PRINT)) {
            consume();
            expect(TokenType::LPAREN, "@func: expected '('");
            auto n = std::make_unique<FuncPrintNode>();
            n->expr = collectBalanced();
            expect(TokenType::RPAREN, "@func: expected ')'");
            skipNewlines();
            return n;
        }

        if (check(TokenType::IDENTIFIER)) {
            std::string name = consume().value;
            if (match(TokenType::ASSIGN)) {
              
                if (check(TokenType::IDENTIFIER) && peek().type == TokenType::LPAREN) {
                    std::string callee = consume().value;
                    consume(); 
                    auto n = std::make_unique<FuncCallStmtNode>();
                    n->resultVar = name;
                    n->funcName = callee;
                    while (!check(TokenType::RPAREN) && !isEnd()) {
                        skipNewlines();
                        if (check(TokenType::RPAREN)) break;
                        n->args.push_back(collectUntilCommaOrParen());
                        match(TokenType::COMMA);
                    }
                    expect(TokenType::RPAREN, "@func: expected ')'");
                    skipNewlines();
                    return n;
                }
              
                auto n = std::make_unique<FuncCallStmtNode>();
                n->resultVar = name;
                n->funcName = "__assign__";
                n->args.push_back(collectUntilNewline());
                skipNewlines();
                return n;
            }
           
            if (check(TokenType::LPAREN)) {
                consume();
                auto n = std::make_unique<FuncCallStmtNode>();
                n->resultVar = "";
                n->funcName = name;
                while (!check(TokenType::RPAREN) && !isEnd()) {
                    skipNewlines();
                    if (check(TokenType::RPAREN)) break;
                    n->args.push_back(collectUntilCommaOrParen());
                    match(TokenType::COMMA);
                }
                expect(TokenType::RPAREN, "@func: expected ')'");
                skipNewlines();
                return n;
            }
        }

        throw std::runtime_error("@func: unexpected '" + current().value +
                                 "' at line " + std::to_string(current().line));
    }

    NodePtr parseFuncDef() {
        consume(); 
        std::string name = expect(TokenType::IDENTIFIER, "@func: expected function name").value;
        expect(TokenType::LPAREN, "@func: expected '('");

        auto node = std::make_unique<FuncDefNode>();
        node->name = name;

        while (!check(TokenType::RPAREN) && !isEnd()) {
            skipNewlines();
            if (check(TokenType::RPAREN)) break;
            node->params.push_back(
                expect(TokenType::IDENTIFIER, "@func: expected param name").value);
            match(TokenType::COMMA);
        }
        expect(TokenType::RPAREN, "@func: expected ')'");
        skipNewlines();
        expect(TokenType::LBRACE, "@func: expected '{'");
        skipNewlines();

        while (!check(TokenType::RBRACE) && !isEnd()) {
            skipNewlines();
            if (check(TokenType::RBRACE)) break;
        
            if (check(TokenType::IDENTIFIER) && current().value == "return") {
                consume();
                node->retExpr = collectUntilNewline();
                skipNewlines();
            } else {
               
                node->body.push_back(parseStmt());
            }
        }
        expect(TokenType::RBRACE, "@func: expected '}'");
        skipNewlines();
        return node;
    }

    std::string collectUntilNewline() {
        std::string r;
        while (!check(TokenType::NEWLINE) && !check(TokenType::RBRACE) && !isEnd()) {
            if (current().type == TokenType::STRING) r += "\"" + consume().value + "\"";
            else r += current().value, consume();
        }
        while (!r.empty() && r.back()==' ') r.pop_back();
        return r;
    }

    std::string collectUntilCommaOrParen() {
        std::string r;
        int depth = 0;
        while (!isEnd()) {
            if (check(TokenType::LPAREN)) { depth++; r += "("; consume(); }
            else if (check(TokenType::RPAREN)) {
                if (depth == 0) break;
                depth--; r += ")"; consume();
            }
            else if (check(TokenType::COMMA) && depth == 0) break;
            else if (current().type == TokenType::STRING) r += "\"" + consume().value + "\"";
            else r += current().value, consume();
        }
        while (!r.empty() && r.back()==' ') r.pop_back();
        return r;
    }

    std::string collectBalanced() {
        std::string r;
        int depth = 0;
        while (!isEnd()) {
            if (check(TokenType::LPAREN)) { depth++; r += "("; consume(); }
            else if (check(TokenType::RPAREN)) {
                if (depth == 0) break;
                depth--; r += ")"; consume();
            } else if (current().type == TokenType::STRING) {
                r += "\"" + consume().value + "\"";
            } else { r += current().value; consume(); }
        }
        while (!r.empty() && r.back()==' ') r.pop_back();
        return r;
    }
};
