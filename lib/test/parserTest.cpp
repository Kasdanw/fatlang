#include "../src/AST.h"
#include "../src/parser.h"
// #include "../src/lexer.h"

#include <gtest/gtest.h>
#include <string_view>

TEST(parse, case1) {
    std::string_view code = "1 + 2 * 4";
    auto tokens = lexer::process(code);
    parser p;
    ASTNode* root = p.parse(tokens);
    ASSERT_NE(root, nullptr);
}
