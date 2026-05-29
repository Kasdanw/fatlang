#include "AST.h"
#include "token.h"
#include "parser.h"

#include <string>

ASTNode* parser::parse(const std::vector<Token>& tokens) {
    this->tokens = tokens;
    pos = 0;
    
    ASTNode* result = nullptr;
    
    while (currentToken().type != TokenType::EOFILE) {
        result = ParseAssigment();
        
        if (currentToken().type == TokenType::SEMICOLON) {
            advance();
        }
    }
    
    return result;
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
        numValue->type = Number;
        numValue->numValue = num;
        return numValue;
    }
    else if (currentToken().type == TokenType::STRING) {
        Token t = consume(TokenType::STRING);
        ASTNode* str = new ASTNode;
        str->type = StringLiteral;
        str->idValue = t.value;
        return str;
    }
    else if (currentToken().type == TokenType::IDENTIFIER) {
        Token t = consume(TokenType::IDENTIFIER);
        std::string str = t.value;
        ASTNode* strValue = new ASTNode;
        strValue->type = Identifier;
        strValue->idValue = str;
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
        node->type = BinaryOp;
        node->op = op;
        node->left = left;
        node->right = right;
        left = node;
    }
    return left;
}

ASTNode* parser::ParseAssigment() {
    
    if (currentToken().type == TokenType::PRINT) {
        consume(TokenType::PRINT);
        consume(TokenType::LPAR);
        ASTNode* arg = ParseComparison();
        consume(TokenType::RPAR);
        ASTNode* node = new ASTNode;
        node->left = arg;
        node->type = Print;
        return node;
    }

    if (currentToken().type == TokenType::IF) {
        consume(TokenType::IF);
        consume(TokenType::LPAR);
        ASTNode* condition = ParseAssigment();
        consume(TokenType::RPAR);
        ASTNode* body = ParseAssigment();
        ASTNode* node = new ASTNode;
        node->left = condition;
        node->right = body;
        node->type = If;
        return node;
     }

    if (currentToken().type == TokenType::LET) {
        consume(TokenType::LET);
        std::string name = currentToken().value;
        consume(TokenType::IDENTIFIER);
        consume(TokenType::EQUALS);
        ASTNode* arg = ParseComparison();
        ASTNode* node = new ASTNode;
        node->idValue = name;
        node->right = arg;
        node->type = Let;
        return node;
    }

    if (currentToken().type == TokenType::IDENTIFIER && 
        pos + 1 < tokens.size() && 
        tokens[pos + 1].type == TokenType::EQUALS) {
        
        std::string name = currentToken().value;
        advance();
        advance();
        
        ASTNode* right = ParseComparison();
        ASTNode* node = new ASTNode;
        node->type = Assigment;
        node->idValue = name;
        node->right = right;
        return node;
    }

    return ParseComparison();
}

ASTNode* parser::ParseComparison() {
    ASTNode* left = ParseExpresion();
    while (currentToken().type == TokenType::EQEQ || currentToken().type == TokenType::LT || currentToken().type == TokenType::GT || currentToken().type == TokenType::GE || currentToken().type == TokenType::LE || currentToken().type == TokenType::NE) {
        TokenType op = currentToken().type;
        advance();
        ASTNode* right = ParseExpresion();
        ASTNode* node = new ASTNode;
        node->type = BinaryOp;
        node->op = op;
        node->left = left;
        node->right = right;
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
        node->type = BinaryOp;
        node->op = op;
        node->left = left;
        node->right = right;
        left = node;
    }
    return left;
}

void parser::parseAll(const std::vector<Token>& tokens, std::vector<ASTNode*>& statements) {
    this->tokens = tokens;
    pos = 0;
    
    while (currentToken().type != TokenType::EOFILE) {
        ASTNode* stmt = ParseAssigment();
        if (stmt) statements.push_back(stmt);
        
        if (currentToken().type == TokenType::SEMICOLON) {
            advance();
        }
    }
}
