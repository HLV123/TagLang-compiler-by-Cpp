#include "lexer.h"
#include <stdexcept>
#include <unordered_map>

std::string Token::typeStr() const {
    static const std::unordered_map<int,std::string> names = {
        {(int)TokenType::NUMBER,"NUMBER"},{(int)TokenType::STRING,"STRING"},
        {(int)TokenType::IDENTIFIER,"IDENTIFIER"},{(int)TokenType::AT_LABEL,"AT_LABEL"},
        {(int)TokenType::PLUS,"PLUS"},{(int)TokenType::MINUS,"MINUS"},
        {(int)TokenType::STAR,"STAR"},{(int)TokenType::SLASH,"SLASH"},
        {(int)TokenType::ASSIGN,"ASSIGN"},{(int)TokenType::EQUAL,"EQUAL"},
        {(int)TokenType::ARROW,"ARROW"},{(int)TokenType::NEWLINE,"NEWLINE"},
        {(int)TokenType::END_OF_FILE,"EOF"},
    };
    auto it = names.find((int)type);
    return it != names.end() ? it->second : "TOKEN("+std::to_string((int)type)+")";
}

TokenType Lexer::keywordType(const std::string& w) {
    static const std::unordered_map<std::string,TokenType> kw = {
        {"if",    TokenType::KW_IF},    {"then",  TokenType::KW_THEN},
        {"else",  TokenType::KW_ELSE},  {"end",   TokenType::KW_END},
        {"while", TokenType::KW_WHILE}, {"do",    TokenType::KW_DO},
        {"repeat",TokenType::KW_REPEAT},{"times", TokenType::KW_TIMES},
        {"print", TokenType::KW_PRINT}, {"true",  TokenType::KW_TRUE},
        {"false", TokenType::KW_FALSE}, {"and",   TokenType::KW_AND},
        {"or",    TokenType::KW_OR},    {"not",   TokenType::KW_NOT},
        {"start", TokenType::KW_START}, {"goto",  TokenType::KW_GOTO},
        {"stop",  TokenType::KW_STOP},
    };
    auto it = kw.find(w);
    return it != kw.end() ? it->second : TokenType::IDENTIFIER;
}

void Lexer::skipLineComment() {
    while (pos < (int)src.size() && current() != '\n') advance();
}

void Lexer::skipBlockComment() {
    advance(); advance(); 
    while (pos < (int)src.size()) {
        if (current() == '\n') line++;
        if (current() == '*' && peek() == '/') { advance(); advance(); return; }
        advance();
    }
    throw std::runtime_error("Block comment not closed (line " + std::to_string(line) + ")");
}

Token Lexer::readNumber() {
    std::string num;
    while (pos < (int)src.size() && (isdigit(current()) || current() == '.'))
        num += advance();
    return {TokenType::NUMBER, num, line};
}

Token Lexer::readString() {
    advance(); 
    std::string s;
    while (pos < (int)src.size() && current() != '"') {
        if (current() == '\\') { advance(); s += advance(); }
        else s += advance();
    }
    if (current() != '"')
        throw std::runtime_error("String not closed at line " + std::to_string(line));
    advance(); 
    return {TokenType::STRING, s, line};
}

Token Lexer::readAtLabel() {
    advance(); 
    std::string name;
    while (pos < (int)src.size() && (isalnum(current()) || current() == '_'))
        name += advance();
    if (name.empty())
        throw std::runtime_error("Expected label name after '@' at line " + std::to_string(line));
    return {TokenType::AT_LABEL, name, line};
}

Token Lexer::readIdentifierOrKeyword() {
    std::string word;
    while (pos < (int)src.size() && (isalnum(current()) || current() == '_'))
        word += advance();
    return {keywordType(word), word, line};
}

Token Lexer::nextToken() {
    char c = current();

    if (isdigit(c)) return readNumber();
  
    if (c == '"')   return readString();
  
    if (c == '@')   return readAtLabel();
   
    if (isalpha(c) || c == '_') return readIdentifierOrKeyword();

    advance(); 
    switch (c) {
        case '+': return {TokenType::PLUS,      "+", line};
        case '-':
            if (current() == '>') { advance(); return {TokenType::ARROW, "->", line}; }
            return {TokenType::MINUS, "-", line};
        case '*': return {TokenType::STAR,      "*", line};
        case '/': return {TokenType::SLASH,     "/", line};
        case '^': return {TokenType::CARET,     "^", line};
        case '%': return {TokenType::PERCENT,   "%", line};
        case ';': return {TokenType::SEMICOLON, ";", line};
        case ':': return {TokenType::COLON,     ":", line};
        case ',': return {TokenType::COMMA,     ",", line};
        case '.': return {TokenType::DOT,       ".", line};
        case '{': return {TokenType::LBRACE,    "{", line};
        case '}': return {TokenType::RBRACE,    "}", line};
        case '(': return {TokenType::LPAREN,    "(", line};
        case ')': return {TokenType::RPAREN,    ")", line};
        case '[': return {TokenType::LBRACKET,  "[", line};
        case ']': return {TokenType::RBRACKET,  "]", line};
        case '=':
            if (current()=='='){advance(); return {TokenType::EQUAL,     "==", line};}
            return {TokenType::ASSIGN, "=", line};
        case '!':
            if (current()=='='){advance(); return {TokenType::NOT_EQUAL, "!=", line};}
            throw std::runtime_error(std::string("Unexpected '!' at line ")+std::to_string(line));
        case '<':
            if (current()=='='){advance(); return {TokenType::LESS_EQ,    "<=", line};}
            return {TokenType::LESS,    "<", line};
        case '>':
            if (current()=='='){advance(); return {TokenType::GREATER_EQ, ">=", line};}
            return {TokenType::GREATER, ">", line};
        default:
            throw std::runtime_error(
                std::string("Unknown character '") + c + "' at line " + std::to_string(line));
    }
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (pos < (int)src.size()) {
    
        while (pos < (int)src.size() && (current()==' ' || current()=='\t' || current()=='\r'))
            advance();

        if (pos >= (int)src.size()) break;

        if (current() == '\n') {
            tokens.push_back({TokenType::NEWLINE, "\\n", line});
            line++;
            advance();
            continue;
        }

        if (current()=='/' && peek()=='/') { skipLineComment(); continue; }

        if (current()=='/' && peek()=='*') { skipBlockComment(); continue; }

        if (current()=='#') { skipLineComment(); continue; }

        tokens.push_back(nextToken());
    }
    tokens.push_back({TokenType::END_OF_FILE, "", line});
    return tokens;
}
