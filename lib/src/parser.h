#pragma once

#include "AST.h"
#include <vector>

class parser {
public:
    ASTNode* parse(const std::vector<Token>& tokens);
private:

    std::vector<Token> tokens;

    int pos;

    ASTNode* ParseExpresion();
    ASTNode* ParseTerm();
    ASTNode* ParseFactor();

    Token currentToken();
    void advance();
    bool match(TokenType);
    Token consume(TokenType);
};
