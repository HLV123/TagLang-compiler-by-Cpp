#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>

enum class TokenType {
    NUMBER,       
    STRING,        
    IDENTIFIER,    

    AT_LABEL,       

    PLUS,          
    MINUS,          
    STAR,          
    SLASH,          
    CARET,        
    PERCENT,       

    ASSIGN,        
    EQUAL,         
    NOT_EQUAL,     
    LESS,          
    LESS_EQ,        
    GREATER,       
    GREATER_EQ,    

    KW_IF,         
    KW_THEN,        
    KW_ELSE,        
    KW_END,         
    KW_WHILE,      
    KW_DO,         
    KW_REPEAT,      
    KW_TIMES,       
    KW_PRINT,      
    KW_TRUE,     
    KW_FALSE,       
    KW_AND,        
    KW_OR,        
    KW_NOT,       

    KW_START,      
    KW_GOTO,        
    KW_STOP,       

    COLON,       
    SEMICOLON,   
    COMMA,       
    DOT,          
    ARROW,         
    LBRACE,        
    RBRACE,        
    LPAREN,       
    RPAREN,         
    LBRACKET,      
    RBRACKET,       

    NEWLINE,       
    END_OF_FILE
};

struct Token {
    TokenType   type;
    std::string value;
    int         line;

    std::string typeStr() const; 
};

class Lexer {
public:
    explicit Lexer(const std::string& source) : src(source) {}

    std::vector<Token> tokenize();

private:
    std::string src;
    int pos  = 0;
    int line = 1;

    char current()        const { return pos < (int)src.size() ? src[pos] : '\0'; }
    char peek(int off=1)  const { int p=pos+off; return p<(int)src.size()?src[p]:'\0'; }
    char advance()              { return src[pos++]; }

    void        skipLineComment();
    void        skipBlockComment();
    Token       readNumber();
    Token       readString();
    Token       readIdentifierOrKeyword();
    Token       readAtLabel();
    Token       nextToken();
    TokenType   keywordType(const std::string& w);
};
