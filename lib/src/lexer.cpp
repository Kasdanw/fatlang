#include "lexer.h"
#include <string>
#include <string_view>
#include <vector>

std::vector<Token> lexer::process(std::string_view code) {
    std::vector<Token> tokens;

    int line = 0;
    // The cycle that will go to the end of the lines in the code
    while (line < code.length()) {
        char c = code[line];
        // Check for spaces, line skips, or tabs
        if (c == ' ' || c == '\t' || c == '\n') {
            line++;
            continue;
        }
        // Check for number or not
        if (c >= '0' && c <= '9') {
            int start = line;
            while (code[line] >= '0' && code[line] <= '9') {
                line++;
            }
            std::string value = std::string(code.substr(start, line - start));
            tokens.push_back(Token{TokenType::NUMBER, value});
            continue;
        }

        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_') {
            int start = line;
            while (line < code.length() &&
                    ((code[line] >= 'A' && code[line] <= 'Z') || 
                     (code[line] >= 'a' && code[line] <= 'z') ||
                     (code[line] >= '0' && code[line] <= '9') ||
                     code[line] == '_')) {
                line++;
            }
            std::string value = std::string(code.substr(start, line - start));
            tokens.push_back(Token{TokenType::IDENTIFIER, value});
            continue;
        }

        // Checking for the presence or absence of data characters.
        if (c == '-' || c == '+' || c == '*' || c == '/' || c == '=') {
            if (c == '-') {
                tokens.push_back(Token{TokenType::MINUS, std::string(1, c)});
            }
            else if (c == '+') {
                tokens.push_back(Token{TokenType::PLUS, std::string(1, c)});
            }
            else if (c == '*') {
                tokens.push_back(Token{TokenType::STAR, std::string(1, c)});
            }
            else if (c == '/') {
                tokens.push_back(Token{TokenType::SLASH, std::string(1, c)});
            }
            else if (c == '=') {
                tokens.push_back(Token{TokenType::EQUALS, std::string(1, c)});
            }
            line++;
        }



        if (c == '(' || c == ')') {
            if (c == '(') {
                tokens.push_back(Token{TokenType::LPAR, std::string(1, c)});
            }
            else if (c == ')') {
                tokens.push_back(Token{TokenType::RPAR, std::string(1, c)});
            }
            line++;
        }
    }

    tokens.push_back(Token{TokenType::EOFILE, ""});

    return tokens;
}
