#pragma once
#include "base_parser.h"

class LogicParser : public BaseParser {
public:
    using BaseParser::BaseParser;

    NodePtr parse() override {
        auto block = std::make_unique<LogicBlockNode>();
        skipNewlines();
        while (!isEnd()) {
            skipNewlines();
            if (isEnd()) break;
            block->statements.push_back(parseStatement());
        }
        return block;
    }

private:
    NodePtr parseStatement() {
        const Token& t = current();

        if (t.type == TokenType::KW_IF)     return parseIf();
        if (t.type == TokenType::KW_WHILE)  return parseWhile();
        if (t.type == TokenType::KW_REPEAT) return parseRepeat();
        if (t.type == TokenType::KW_PRINT)  return parsePrint();
        if (t.type == TokenType::IDENTIFIER) {
            if (peek().type == TokenType::ASSIGN)
                return parseAssign();
        }
        throw std::runtime_error(
            "@logic: unexpected token '" + t.value +
            "' at line " + std::to_string(t.line));
    }

    NodePtr parseIf() {
        consume(); // if
        auto node = std::make_unique<IfNode>();
        node->condition = parseCondition(TokenType::KW_THEN, "then");
        expect(TokenType::KW_THEN, "@logic: expected 'then' after if condition");
        skipNewlines();

        while (!check(TokenType::KW_ELSE) &&
               !check(TokenType::KW_END)  &&
               !isEnd()) {
            skipNewlines();
            if (check(TokenType::KW_ELSE) || check(TokenType::KW_END)) break;
            node->thenBody.push_back(parseStatement());
            skipNewlines();
        }

        if (match(TokenType::KW_ELSE)) {
            skipNewlines();
            while (!check(TokenType::KW_END) && !isEnd()) {
                skipNewlines();
                if (check(TokenType::KW_END)) break;
                node->elseBody.push_back(parseStatement());
                skipNewlines();
            }
        }

        expect(TokenType::KW_END, "@logic: expected 'end' to close if block");
        return node;
    }

    NodePtr parseWhile() {
        consume(); 
        auto node = std::make_unique<WhileNode>();
        node->condition = parseCondition(TokenType::KW_DO, "do");
        expect(TokenType::KW_DO, "@logic: expected 'do' after while condition");
        skipNewlines();

        while (!check(TokenType::KW_END) && !isEnd()) {
            skipNewlines();
            if (check(TokenType::KW_END)) break;
            node->body.push_back(parseStatement());
            skipNewlines();
        }
        expect(TokenType::KW_END, "@logic: expected 'end' to close while block");
        return node;
    }

    NodePtr parseRepeat() {
        consume(); 
        auto node = std::make_unique<RepeatNode>();

        if (!check(TokenType::NUMBER))
            throw std::runtime_error(
                "@logic: expected number after 'repeat' at line " +
                std::to_string(current().line));
        node->times = std::stoi(consume().value);

        expect(TokenType::KW_TIMES, "@logic: expected 'times' after repeat count");
        skipNewlines();

        while (!check(TokenType::KW_END) && !isEnd()) {
            skipNewlines();
            if (check(TokenType::KW_END)) break;
            node->body.push_back(parseStatement());
            skipNewlines();
        }
        expect(TokenType::KW_END, "@logic: expected 'end' to close repeat block");
        return node;
    }

    NodePtr parsePrint() {
        consume(); 
        auto node = std::make_unique<PrintNode>();
        bool hasParen = match(TokenType::LPAREN);
        node->expr = collectExprUntil(hasParen ? TokenType::RPAREN : TokenType::NEWLINE);
        if (hasParen) expect(TokenType::RPAREN, "@logic: expected ')' after print(");

        return node;
    }

    NodePtr parseAssign() {
        auto node = std::make_unique<AssignNode>();
        node->varName = consume().value; 
        consume(); // =
        node->value = collectExprUntil(TokenType::NEWLINE);
        return node;
    }

    std::unique_ptr<ExprNode> parseCondition(TokenType stopAt, const std::string&) {
        auto expr = std::make_unique<ExprNode>();
        while (current().type != stopAt && !isEnd() &&
               current().type != TokenType::NEWLINE) {
            expr->raw += tokenToCpp(current());
            consume();
        }
        trimStr(expr->raw);
        return expr;
    }

    std::unique_ptr<ExprNode> collectExprUntil(TokenType stopAt) {
        auto expr = std::make_unique<ExprNode>();
        while (current().type != stopAt && !isEnd()) {
            expr->raw += tokenToCpp(current());
            consume();
        }
        trimStr(expr->raw);
        return expr;
    }

    std::string tokenToCpp(const Token& t) {
        switch (t.type) {
            case TokenType::KW_AND: return " && ";
            case TokenType::KW_OR:  return " || ";
            case TokenType::KW_NOT: return "!";
            case TokenType::KW_TRUE:  return "true";
            case TokenType::KW_FALSE: return "false";
            case TokenType::EQUAL:      return " == ";
            case TokenType::NOT_EQUAL:  return " != ";
            case TokenType::LESS:       return " < ";
            case TokenType::LESS_EQ:    return " <= ";
            case TokenType::GREATER:    return " > ";
            case TokenType::GREATER_EQ: return " >= ";
            case TokenType::PLUS:  return " + ";
            case TokenType::MINUS: return " - ";
            case TokenType::STAR:  return " * ";
            case TokenType::SLASH: return " / ";
            case TokenType::STRING: return "\"" + t.value + "\"";
            default: return t.value;
        }
    }

    void trimStr(std::string& s) {
        while (!s.empty() && s.front() == ' ') s.erase(s.begin());
        while (!s.empty() && s.back()  == ' ') s.pop_back();
    }
};
