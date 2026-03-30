#pragma once
#include "base_parser.h"

class ArrayParser : public BaseParser {
public:
    using BaseParser::BaseParser;

    NodePtr parse() override {
        auto block = std::make_unique<CArrayBlockNode>();
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
            expect(TokenType::LPAREN, "@array: expected '('");
            auto n = std::make_unique<CArrayPrintNode>();
            n->name = expect(TokenType::IDENTIFIER, "@array: expected array name").value;
            if (check(TokenType::LBRACKET)) {
                consume();
                n->index = collectUntil(TokenType::RBRACKET);
                expect(TokenType::RBRACKET, "@array: expected ']'");
            }
            expect(TokenType::RPAREN, "@array: expected ')'");
            skipNewlines();
            return n;
        }

        if (!check(TokenType::IDENTIFIER))
            throw std::runtime_error("@array: expected type at line " +
                                     std::to_string(current().line));

        std::string typeName = consume().value;

        if (typeName == "char") {
            bool isPtr = false;
            if (check(TokenType::STAR)) { consume(); isPtr = true; }
            std::string name = expect(TokenType::IDENTIFIER, "@array: expected name").value;
            if (!isPtr && check(TokenType::LBRACKET)) {
                consume(); 
                if (!check(TokenType::RBRACKET)) consume(); 
                expect(TokenType::RBRACKET, "@array: expected ']'");
            }
            expect(TokenType::ASSIGN, "@array: expected '='");
            auto n = std::make_unique<CCharStrNode>();
            n->name = name; n->isPtr = isPtr;
            n->value = expect(TokenType::STRING, "@array: expected string literal").value;
            skipNewlines();
            return n;
        }

        std::string name = expect(TokenType::IDENTIFIER, "@array: expected array name").value;
        expect(TokenType::LBRACKET, "@array: expected '['");
        int size = 0;
        if (check(TokenType::NUMBER)) size = std::stoi(consume().value);
        expect(TokenType::RBRACKET, "@array: expected ']'");
        expect(TokenType::ASSIGN, "@array: expected '='");
        expect(TokenType::LBRACE, "@array: expected '{'");

        auto n = std::make_unique<CArrayDeclNode>();
        n->name = name; n->elemType = typeName; n->size = size;
        while (!check(TokenType::RBRACE) && !isEnd()) {
            skipNewlines();
            if (check(TokenType::RBRACE)) break;
            std::string val;
            if (check(TokenType::MINUS)) { consume(); val = "-"; }
            val += expect(TokenType::NUMBER, "@array: expected number").value;
            n->elements.push_back(val);
            skipNewlines();
            match(TokenType::COMMA);
        }
        expect(TokenType::RBRACE, "@array: expected '}'");
        skipNewlines();
        return n;
    }

    std::string collectUntil(TokenType stop) {
        std::string r;
        while (!check(stop) && !isEnd()) { r += current().value; consume(); }
        return r;
    }
};
