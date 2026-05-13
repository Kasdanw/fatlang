#include "AST.h"
#include <iostream>

int evaluate(ASTNode* node) { 
    switch (node->type) {
        case Number: return node->numValue;
        case Identifier: return 0;
        case BinaryOp:
            int left = evaluate(node->left);
            int right = evaluate(node->right);
            switch (node->op) {
                case TokenType::PLUS: return left + right;
                case TokenType::MINUS: return left - right;
                case TokenType::STAR: return left * right;
                case TokenType::SLASH: return left / right;
                default: std::cerr << "Unknow operation"; return 0;
            }
    }
}
