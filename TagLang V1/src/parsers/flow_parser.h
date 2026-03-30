#pragma once
#include "base_parser.h"

class FlowParser : public BaseParser {
public:
    using BaseParser::BaseParser;

    NodePtr parse() override {
        auto block = std::make_unique<FlowBlockNode>();
        block->entry = "start";
        skipNewlines();

        while (!isEnd()) {
            skipNewlines();
            if (isEnd()) break;

            if (check(TokenType::KW_START)) {
                consume();
                expect(TokenType::COLON, "@flow: expected ':' after 'start'");
                block->entry = consume().value;
                skipNewlines();
                continue;
            }

            if (check(TokenType::IDENTIFIER)) {
                auto step = std::make_unique<FlowStepNode>();
                step->from = consume().value;

                expect(TokenType::ARROW, "@flow: expected '->' after label name");
                if (!check(TokenType::IDENTIFIER))
                    throw std::runtime_error(
                        "@flow: expected target label at line " +
                        std::to_string(current().line));
                step->to = consume().value;

                if (check(TokenType::KW_IF)) {
                    consume(); 
                    while (!check(TokenType::NEWLINE) &&
                           !check(TokenType::END_OF_FILE) &&
                           !check(TokenType::RBRACE)) {
                        step->condition += current().value + " ";
                        consume();
                    }
                    while (!step->condition.empty() && step->condition.back() == ' ')
                        step->condition.pop_back();
                }

                block->steps.push_back(std::move(step));
                skipNewlines();
                continue;
            }

            if (check(TokenType::KW_STOP)) {
                consume();
                match(TokenType::COLON);
                while (!check(TokenType::NEWLINE) && !isEnd()) consume();
                skipNewlines();
                continue;
            }

            throw std::runtime_error(
                "@flow: unexpected token '" + current().value +
                "' at line " + std::to_string(current().line));
        }
        return block;
    }
};
