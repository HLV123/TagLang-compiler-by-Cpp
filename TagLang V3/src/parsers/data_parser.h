#pragma once
#include "base_parser.h"

class DataParser : public BaseParser {
public:
    using BaseParser::BaseParser;

    NodePtr parse() override {
        auto block = std::make_unique<DataBlockNode>();
        skipNewlines();

        while (!isEnd()) {
            skipNewlines();
            if (isEnd()) break;

            if (!check(TokenType::IDENTIFIER))
                throw std::runtime_error(
                    "@data: expected variable name at line " +
                    std::to_string(current().line));

            auto entry = std::make_unique<DataEntryNode>();
            entry->name = consume().value; 

            expect(TokenType::COLON, "@data: expected ':' after variable name");

            parseValue(*entry);

            block->entries.push_back(std::move(entry));
            skipNewlines();
        }
        return block;
    }

private:
    void parseValue(DataEntryNode& entry) {
        skipNewlines();
        const Token& t = current();

        if (t.type == TokenType::LBRACKET) {
            consume(); 
            entry.dataType = "array";
            while (!check(TokenType::RBRACKET) && !isEnd()) {
                skipNewlines();
                if (check(TokenType::RBRACKET)) break;
                const Token& item = current();
                if (item.type == TokenType::STRING)
                    entry.arrayItems.push_back("STR:" + consume().value);
                else
                    entry.arrayItems.push_back(consume().value);
                skipNewlines();
                match(TokenType::COMMA);
            }
            expect(TokenType::RBRACKET, "@data: expected ']' to close array");
            return;
        }

        if (t.type == TokenType::STRING) {
            entry.value    = consume().value;
            entry.dataType = "string";
            return;
        }

        if (t.type == TokenType::KW_TRUE || t.type == TokenType::KW_FALSE) {
            entry.value    = consume().value;
            entry.dataType = "bool";
            return;
        }

        if (t.type == TokenType::MINUS && peek().type == TokenType::NUMBER) {
            consume(); // -
            entry.value    = "-" + consume().value;
            entry.dataType = entry.value.find('.') != std::string::npos ? "float" : "int";
            return;
        }

        if (t.type == TokenType::NUMBER) {
            entry.value    = consume().value;
            entry.dataType = entry.value.find('.') != std::string::npos ? "float" : "int";
            return;
        }

        throw std::runtime_error(
            "@data: unexpected value token '" + t.value +
            "' at line " + std::to_string(t.line));
    }
};
