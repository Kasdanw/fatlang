#pragma once
#include <string>

enum class TokenType { 
    IDENTIFIER, // Variables or name functions
    NUMBER, // This number or not 1, 2, 3, 4, 5, 6........
    PLUS, MINUS, STAR, SLASH, EQUALS, // + - * / =
    LPAR, RPAR, // ( )
    EOFILE, // End of file
    SEMICOLON, // ;
};

struct Token {
    TokenType type;
    std::string value;

    bool operator==(const Token& other) const {
        return type == other.type && value == other.value;
    }
};
