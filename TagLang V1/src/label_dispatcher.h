#pragma once
#include "lexer.h"
#include "ast/ast_nodes.h"
#include "parsers/data_parser.h"
#include "parsers/calc_parser.h"
#include "parsers/logic_parser.h"
#include "parsers/out_parser.h"
#include "parsers/flow_parser.h"
#include <memory>
#include <stdexcept>

class LabelDispatcher {
public:
    explicit LabelDispatcher(const std::vector<Token>& tokens)
        : toks(tokens), pos(0) {}

    std::unique_ptr<ProgramNode> dispatch() {
        auto program = std::make_unique<ProgramNode>();

        while (!isEnd()) {
            skipNewlines();
            if (isEnd()) break;

            if (current().type != TokenType::AT_LABEL)
                throw std::runtime_error(
                    "Expected @label at top level, got '" +
                    current().value + "' at line " +
                    std::to_string(current().line));

            std::string label = consume().value; 
            skipNewlines();
            expect(TokenType::LBRACE, "Expected '{' after @" + label);
            std::vector<Token> block = extractBlock();
            NodePtr node = createParser(label, block);
            program->blocks.push_back(std::move(node));
        }
        return program;
    }

private:
    const std::vector<Token>& toks;
    int pos;

    const Token& current() const {
        return toks[pos < (int)toks.size() ? pos : (int)toks.size()-1];
    }
    Token consume() {
        return toks[pos < (int)toks.size() ? pos++ : pos];
    }
    bool isEnd() const {
        return current().type == TokenType::END_OF_FILE;
    }
    void skipNewlines() {
        while (current().type == TokenType::NEWLINE) consume();
    }
    Token expect(TokenType t, const std::string& msg) {
        if (current().type != t)
            throw std::runtime_error(msg + " (got '" + current().value +
                                     "' at line " + std::to_string(current().line) + ")");
        return consume();
    }

    std::vector<Token> extractBlock() {
        std::vector<Token> block;
        int depth = 1;
        while (!isEnd() && depth > 0) {
            const Token& t = current();
            if (t.type == TokenType::LBRACE) depth++;
            if (t.type == TokenType::RBRACE) {
                depth--;
                if (depth == 0) { consume(); break; }
            }
            block.push_back(consume());
        }
        block.push_back({TokenType::END_OF_FILE, "", 0});
        return block;
    }
    NodePtr createParser(const std::string& label,
                         const std::vector<Token>& block) {
        if (label == "data")  return DataParser(block).parse();
        if (label == "calc")  return CalcParser(block).parse();
        if (label == "logic") return LogicParser(block).parse();
        if (label == "out")   return OutParser(block).parse();
        if (label == "flow")  return FlowParser(block).parse();

        throw std::runtime_error(
            "Unknown label '@" + label + "'. "
            "Supported: @data, @calc, @logic, @out, @flow");
    }
};
