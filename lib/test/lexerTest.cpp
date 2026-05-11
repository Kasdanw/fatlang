#include <gtest/gtest.h>
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
