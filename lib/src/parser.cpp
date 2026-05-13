#include "AST.h"
#include <string>
#include "parser.h"


ASTNode* parser::parse(const std::vector<Token>& tokens) {
    this -> tokens = tokens;
    pos = 0;
    ASTNode* result = ParseExpresion();

    if (currentToken().type == TokenType::EOFILE) {
        return result;
    }
    return nullptr;
}

Token parser::currentToken() {
    return tokens[pos];
}

void parser::advance() {
    pos++;
}

bool parser::match(TokenType type) {
    if (type == currentToken().type) {
        advance();
        return true;
    }

    return false;
}

Token parser::consume(TokenType type) {
    Token t = currentToken();
    if (match(type)) {
        return t;
    }
    return Token{};
}

ASTNode* parser::ParseFactor() {
    if (currentToken().type == TokenType::NUMBER) {
        Token t = consume(TokenType::NUMBER);
        int num = std::stoi(t.value);
        ASTNode* numValue = new ASTNode;
        numValue -> type = Number;
        numValue -> numValue = num;
        return numValue;
    }
    else if (currentToken().type == TokenType::IDENTIFIER) {
        Token t = consume(TokenType::IDENTIFIER);
        std::string str = t.value;
        ASTNode* strValue = new ASTNode;
        strValue -> type = Identifier;
        strValue -> idValue = str;
        return strValue;
    }
    else if (currentToken().type == TokenType::LPAR) {
        consume(TokenType::LPAR);
        ASTNode* expr = ParseExpresion();
        consume(TokenType::RPAR);
        return expr;
    }
    return nullptr;
}

ASTNode* parser::ParseTerm() {
    ASTNode* left = ParseFactor();
    while (currentToken().type == TokenType::STAR || currentToken().type == TokenType::SLASH) {
        TokenType op = currentToken().type;
        advance();
        ASTNode* right = ParseFactor();
        ASTNode* node = new ASTNode;
        node -> type = BinaryOp;
        node -> op = op;
        node -> left = left;
        node -> right = right;
        left = node;
    }
    return left;
}

ASTNode* parser::ParseExpresion() {
    ASTNode* left = ParseTerm();
    while (currentToken().type == TokenType::PLUS || currentToken().type == TokenType::MINUS) {
        TokenType op = currentToken().type;
        advance();
        ASTNode* right = ParseTerm();
        ASTNode* node = new ASTNode;
        node -> type = BinaryOp;
        node -> op = op;
        node -> left = left;
        node -> right = right;
        left = node;
    }
    return left;
}
