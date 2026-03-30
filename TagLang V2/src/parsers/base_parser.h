#pragma once
#include "../lexer.h"
#include "../ast/ast_nodes.h"
#include <vector>
#include <stdexcept>

class BaseParser {
public:
    explicit BaseParser(const std::vector<Token>& tokens)
        : toks(tokens), pos(0) {}

    virtual ~BaseParser() = default;
    virtual NodePtr parse() = 0;

protected:
    const std::vector<Token>& toks;
    int pos;

    const Token& current() const {
        return toks[pos < (int)toks.size() ? pos : (int)toks.size()-1];
    }
    const Token& peek(int off = 1) const {
        int p = pos + off;
        return toks[p < (int)toks.size() ? p : (int)toks.size()-1];
    }
    Token consume() {
        return toks[pos < (int)toks.size() ? pos++ : pos];
    }
    Token expect(TokenType t, const std::string& msg) {
        if (current().type != t)
            throw std::runtime_error(msg + " (got '" + current().value +
                                     "' at line " + std::to_string(current().line) + ")");
        return consume();
    }
    bool check(TokenType t) const { return current().type == t; }
    bool match(TokenType t) { if (check(t)) { consume(); return true; } return false; }
    void skipNewlines() { while (check(TokenType::NEWLINE)) consume(); }
    bool isEnd() const {
        return current().type == TokenType::END_OF_FILE ||
               current().type == TokenType::RBRACE;
    }
};
