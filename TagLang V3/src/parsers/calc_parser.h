#pragma once
#include "base_parser.h"
#include <sstream>

class CalcParser : public BaseParser {
public:
    using BaseParser::BaseParser;

    NodePtr parse() override {
        auto block = std::make_unique<CalcBlockNode>();
        skipNewlines();

        while (!isEnd()) {
            skipNewlines();
            if (isEnd()) break;

            if (!check(TokenType::IDENTIFIER))
                throw std::runtime_error(
                    "@calc: expected variable name at line " +
                    std::to_string(current().line));

            auto expr = std::make_unique<CalcExprNode>();
            expr->lhs = consume().value;

            expect(TokenType::ASSIGN, "@calc: expected '=' after variable name");

            expr->expr = collectExpression();

            block->exprs.push_back(std::move(expr));
            skipNewlines();
        }
        return block;
    }

private:
   
    std::string collectExpression() {
        std::string result;
        while (!check(TokenType::NEWLINE) &&
               !check(TokenType::END_OF_FILE) &&
               !check(TokenType::RBRACE)) {

            const Token& t = current();

            if (t.type == TokenType::CARET) {
                std::string base = extractLastOperand(result);
                consume(); 
                skipWhitespaceTokens();
                std::string exp = collectSingleTerm();
                result += "pow(" + base + ", " + exp + ")";
            } else {
                result += tokenToCpp(t);
                consume();
            }
        }
 
        while (!result.empty() && result.back() == ' ') result.pop_back();
        return result;
    }

    void skipWhitespaceTokens() { /* spaces already skipped by lexer */ }

    std::string collectSingleTerm() {
        std::string r;
        if (check(TokenType::LPAREN)) {
            r += "("; consume();
            int depth = 1;
            while (!isEnd() && depth > 0) {
                if (check(TokenType::LPAREN))  depth++;
                if (check(TokenType::RPAREN))  depth--;
                if (depth > 0) r += tokenToCpp(current());
                consume();
            }
            r += ")";
        } else {
            r += tokenToCpp(current());
            consume();
        }
        return r;
    }

    std::string extractLastOperand(std::string& expr) {
      
        int i = (int)expr.size() - 1;
        while (i >= 0 && expr[i] == ' ') i--;
        int end = i;
        while (i >= 0 && (isalnum(expr[i]) || expr[i] == '_' || expr[i] == '.')) i--;
        std::string op = expr.substr(i + 1, end - i);
        expr = expr.substr(0, i + 1);
        while (!expr.empty() && expr.back() == ' ') expr.pop_back();
        return op;
    }

    std::string tokenToCpp(const Token& t) {
        switch (t.type) {
            case TokenType::PLUS:    return " + ";
            case TokenType::MINUS:   return " - ";
            case TokenType::STAR:    return " * ";
            case TokenType::SLASH:   return " / ";
            case TokenType::PERCENT: return " % ";
            case TokenType::LPAREN:  return "(";
            case TokenType::RPAREN:  return ")";
            default:                 return t.value;
        }
    }
};
