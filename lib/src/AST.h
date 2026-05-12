#pragma once

#include "lexer.h"
#include <string>
enum NodeType {Number, Identifier, BinaryOp};

struct ASTNode {
    int numValue;
    std::string idValue;
    TokenType op;
    NodeType type;
    ASTNode* left;
    ASTNode* right;
};

