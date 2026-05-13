#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "../src/lexer.h"

TEST(lexer, case1) {
    auto processed = lexer::process(R"(
        2 + 2 * 2
    )");
    std::vector<Token> expected {
        Token{TokenType::NUMBER, "2"},
        Token{TokenType::PLUS, "+"},
        Token{TokenType::NUMBER, "2"},
        Token{TokenType::STAR, "*"},
        Token{TokenType::NUMBER, "2"},
        Token{TokenType::EOFILE, ""}
    };
    EXPECT_EQ(processed, expected);
}

TEST(lexer, case2) {
    auto tokens = lexer::process(R"(2000 * 100 - 21;
12300 - 2000;
)");

    for (size_t i = 0; i < tokens.size(); i++) {
        std::cout << static_cast<int>(tokens[i].type) 
                  << " '" << tokens[i].value << "'" << std::endl;
    }
}
