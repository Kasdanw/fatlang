#include "AST.h"
#include "token.h"
#include <iostream>
#include <map>
#include <string>

int evaluate(ASTNode* node, std::map<std::string, std::string>& variables) { 
    switch (node->type) {
        case Number: return node->numValue;
        case Identifier: {
            auto it = variables.find(node->idValue);
            if (it != variables.end()) {
                try {
                    return std::stoi(it->second);
                } catch (...) {
                    return 0;
                }
            }
            else return 0;
        }
        case Assigment: {
            if (variables.find(node->idValue) == variables.end()) {
                std::cerr << "variable not found" << std::endl;
                exit(1);
            }
            if (node->right->type == StringLiteral) {
                variables[node->idValue] = node->right->idValue;
            }
            else {
                int value = evaluate(node->right, variables);
                variables[node->idValue] = std::to_string(value);
                return value;
            }
            return 0;
        }

        case StringLiteral: {
            return 0;
        }

        case BinaryOp: {
            int left = evaluate(node->left, variables);
            int right = evaluate(node->right, variables);
            switch (node->op) { 
                case TokenType::EQEQ: 
                    if (node->left->type == StringLiteral && node->right->type == StringLiteral) {
                        return (node->left->idValue == node->right->idValue) ? 1 : 0;
                    }
                    if (node->left->type == Identifier && node->right->type == StringLiteral) {
                        auto it = variables.find(node->left->idValue);
                        if (it != variables.end() && it->second == node->right->idValue) return 1;
                        return 0;
                    }
                    return (left == right) ? 1 : 0;
                case TokenType::GE: return left >= right;
                case TokenType::LE: return left <= right;
                case TokenType::LT: return left < right;
                case TokenType::GT: return left > right;
                case TokenType::NE: return left != right;
                case TokenType::PLUS: return left + right;
                case TokenType::MINUS: return left - right;
                case TokenType::STAR: return left * right;
                case TokenType::SLASH: return left / right;
                default: std::cerr << "Unknow operation"; return 0;
            }
        }

        case Let: {
            if (variables.find(node->idValue) != variables.end()) {
                std::cerr << "variable already exists" << std::endl;
                exit(1);
            }

            if (node->right->type == StringLiteral) {
                variables[node->idValue] = node->right->idValue;
            }
            else {
                int value = evaluate(node->right, variables);
                variables[node->idValue] = std::to_string(value);
                return value;
            }
            return 0;
        }

        case If: {
            int condition = evaluate(node->left, variables);
            if (condition != 0) {
                return evaluate(node->right, variables);
            }
            return 0;
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
