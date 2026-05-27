#include "AST.h"
#include "token.h"
#include <iostream>
#include <map>

int evaluate(ASTNode* node, std::map<std::string, int>& variables) { 
    switch (node->type) {
        case Number: return node->numValue;
        case Identifier: {
            auto it = variables.find(node->idValue);
            if (it != variables.end()) return it->second;
            else return 0;
        }
        case Assigment: {
            int value = evaluate(node->right, variables);
            variables[node->idValue] = value;
            return value;
        }

        case BinaryOp: {
            int left = evaluate(node->left, variables);
            int right = evaluate(node->right, variables);
            switch (node->op) {
                case TokenType::PLUS: return left + right;
                case TokenType::MINUS: return left - right;
                case TokenType::STAR: return left * right;
                case TokenType::SLASH: return left / right;
                default: std::cerr << "Unknow operation"; return 0;
            }
        }

        case Let: {
            int value = evaluate(node->right, variables);
            variables[node->idValue] = value;
            return value;
        }

        case Print: {
            if (node->left->type == StringLiteral) {
                std::cout << node->left->idValue << std::endl;
                return 0;
            } else {
                int value = evaluate(node->left, variables);
                std::cout << value << std::endl;            
                return value;
            }
        }
    }
}
