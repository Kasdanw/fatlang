#include "token.h"

#include <string_view>
#include <vector>

namespace lexer {
    std::vector<Token> process(std::string_view code);
}
