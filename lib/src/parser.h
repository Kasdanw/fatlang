#pragma once

#include "AST.h"
#include <vector>

class parser {
public:
    ASTNode* parse(const std::vector<Token>& tokens);
    void parseAll(const std::vector<Token>& tokens, std::vector<ASTNode*>& statements);
private:

    std::vector<Token> tokens;

    int pos;

    ASTNode* ParseComparison();
    ASTNode* ParseExpresion();
    ASTNode* ParseAssigment();
    ASTNode* ParseTerm();
    ASTNode* ParseFactor();

    Token currentToken();
    void advance();
    bool match(TokenType);
    Token consume(TokenType);
};
