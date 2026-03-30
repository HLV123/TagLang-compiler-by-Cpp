#pragma once
#include "base_parser.h"

class LambdaParser : public BaseParser {
public:
    using BaseParser::BaseParser;

    NodePtr parse() override {
        auto block = std::make_unique<LambdaBlockNode>();
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
            expect(TokenType::LPAREN, "@lambda: expected '('");
            auto n = std::make_unique<LambdaPrintNode>();
            n->expr = collectBalanced(); 
            expect(TokenType::RPAREN, "@lambda: expected ')'");
            skipNewlines();
            return n;
        }

        if (!check(TokenType::IDENTIFIER))
            throw std::runtime_error("@lambda: expected identifier at line " +
                                     std::to_string(current().line));

        std::string name = consume().value;
        if (match(TokenType::ASSIGN)) {
            if (isLambdaDef()) {
                auto n = std::make_unique<LambdaDeclNode>();
                n->name = name;
                parseLambdaBody(*n);
                skipNewlines();
                return n;
            }

            std::string callee = expect(TokenType::IDENTIFIER, "@lambda: expected function name").value;
            expect(TokenType::LPAREN, "@lambda: expected '('");
            auto n = std::make_unique<LambdaCallNode>();
            n->resultVar = name;
            n->lambdaName = callee;
            while (!check(TokenType::RPAREN) && !isEnd()) {
                skipNewlines();
                if (check(TokenType::RPAREN)) break;
                n->args.push_back(consume().value);
                skipNewlines();
                match(TokenType::COMMA);
            }
            expect(TokenType::RPAREN, "@lambda: expected ')'");
            skipNewlines();
            return n;
        }

        if (check(TokenType::LPAREN)) {
            consume();
            auto n = std::make_unique<LambdaCallNode>();
            n->resultVar = "";
            n->lambdaName = name;
            while (!check(TokenType::RPAREN) && !isEnd()) {
                skipNewlines();
                if (check(TokenType::RPAREN)) break;
                n->args.push_back(consume().value);
                skipNewlines();
                match(TokenType::COMMA);
            }
            expect(TokenType::RPAREN, "@lambda: expected ')'");
            skipNewlines();
            return n;
        }

        throw std::runtime_error("@lambda: unexpected '" + current().value + "'");
    }

    bool isLambdaDef() {
        int save = pos;
        bool result = false;
        if (check(TokenType::LPAREN)) {
            int depth = 0;
            int i = pos;
            while (i < (int)toks.size()) {
                if (toks[i].type == TokenType::LPAREN) depth++;
                if (toks[i].type == TokenType::RPAREN) { depth--; if (depth==0){i++;break;} }
                i++;
            }
            if (i < (int)toks.size() && toks[i].type == TokenType::ASSIGN &&
                i+1 < (int)toks.size() && toks[i+1].type == TokenType::GREATER)
                result = true;
        } else if (check(TokenType::IDENTIFIER)) {
            int i = pos + 1;
            if (i < (int)toks.size() && toks[i].type == TokenType::ASSIGN &&
                i+1 < (int)toks.size() && toks[i+1].type == TokenType::GREATER)
                result = true;
        }
        pos = save;
        return result;
    }

    void parseLambdaBody(LambdaDeclNode& n) {
        if (check(TokenType::LPAREN)) {
            consume(); // (
            while (!check(TokenType::RPAREN) && !isEnd()) {
                skipNewlines();
                if (check(TokenType::RPAREN)) break;
                n.params.push_back(consume().value);
                match(TokenType::COMMA);
            }
            expect(TokenType::RPAREN, "@lambda: expected ')'");
        } else {
            n.params.push_back(expect(TokenType::IDENTIFIER, "@lambda: expected param").value);
        }
        expect(TokenType::ASSIGN, "@lambda: expected '=>'");
        expect(TokenType::GREATER, "@lambda: expected '>' in '=>'");
        n.body = collectUntil(TokenType::NEWLINE);
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
