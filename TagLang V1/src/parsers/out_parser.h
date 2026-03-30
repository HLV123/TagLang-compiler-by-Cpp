#pragma once
#include "base_parser.h"

class OutParser : public BaseParser {
public:
    using BaseParser::BaseParser;

    NodePtr parse() override {
        auto block = std::make_unique<OutBlockNode>();
        skipNewlines();

        while (!isEnd()) {
            skipNewlines();
            if (isEnd()) break;

            if (!check(TokenType::STRING))
                throw std::runtime_error(
                    "@out: expected string template at line " +
                    std::to_string(current().line));

            auto line = std::make_unique<OutLineNode>();
            line->tmpl = consume().value;
            block->lines.push_back(std::move(line));
            skipNewlines();
        }
        return block;
    }
};
