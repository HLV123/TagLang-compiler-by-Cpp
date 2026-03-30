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
                    consume(); consume(); // ..
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

        if (check(TokenType::IDENTIFIER)) {
            std::string varName = consume().value;
            if (match(TokenType::ASSIGN)) {
                auto n = std::make_unique<AssignNode>();
                n->varName = varName;
            
                std::string rhs;
                while (!check(TokenType::NEWLINE) && !check(TokenType::END_OF_FILE)
                       && !check(TokenType::RBRACE)) {
                    if (current().type == TokenType::STRING)
                        rhs += "\"" + consume().value + "\"";
                    else { rhs += current().value; consume(); }
                }
                while (!rhs.empty() && rhs.back()==' ') rhs.pop_back();
                auto expr = std::make_unique<ExprNode>();
                expr->raw = rhs;
                n->value = std::move(expr);
                skipNewlines();
                return n;
            }
            if (check(TokenType::LPAREN)) {
                consume();
                std::string args;
                int depth = 0;
                while (!isEnd()) {
                    if (check(TokenType::LPAREN)) { depth++; args += "("; consume(); }
                    else if (check(TokenType::RPAREN)) {
                        if (depth == 0) break;
                        depth--; args += ")"; consume();
                    } else { args += current().value; consume(); }
                }
                expect(TokenType::RPAREN, "@iter: expected ')'");
                auto n2 = std::make_unique<IterPrintNode>();
                n2->expr = varName + "(" + args + ")";
                skipNewlines();
                return n2;
            }
        }
        if (check(TokenType::IDENTIFIER)) {
            std::string varname = current().value;
            if (peek().type == TokenType::ASSIGN) {
                consume(); 
                consume(); 
                auto n = std::make_unique<AssignNode>();
                n->varName = varname;
                auto expr = std::make_unique<ExprNode>();
                while (!check(TokenType::NEWLINE) && !check(TokenType::RBRACE) && !isEnd()) {
                    switch(current().type) {
                        case TokenType::EQUAL:      expr->raw += " == "; consume(); break;
                        case TokenType::LESS:       expr->raw += " < ";  consume(); break;
                        case TokenType::GREATER:    expr->raw += " > ";  consume(); break;
                        case TokenType::LESS_EQ:    expr->raw += " <= "; consume(); break;
                        case TokenType::GREATER_EQ: expr->raw += " >= "; consume(); break;
                        case TokenType::PLUS:       expr->raw += " + ";  consume(); break;
                        case TokenType::MINUS:      expr->raw += " - ";  consume(); break;
                        case TokenType::STAR:       expr->raw += " * ";  consume(); break;
                        case TokenType::SLASH:      expr->raw += " / ";  consume(); break;
                        case TokenType::STRING:     expr->raw += "\"" + consume().value + "\""; break;
                        default:                    expr->raw += consume().value; break;
                    }
                }
                while (!expr->raw.empty() && expr->raw.back()==' ') expr->raw.pop_back();
                n->value = std::move(expr);
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
