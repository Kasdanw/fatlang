#pragma once

#include "lexer.h"
#include "token.h"
#include <string>
enum NodeType {Number, Identifier, BinaryOp, Assigment, Print, StringLiteral, Let, If};

struct ASTNode {
    int numValue;
    std::string idValue;
    TokenType op;
    NodeType type;
    ASTNode* left;
    ASTNode* right;
};

