#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "lexer.h"
#include "parser.h"
#include "evaluate.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: fatlang <file>" << std::endl;
        return 1;
    }
    
    std::ifstream fis(argv[1]);
    if (!fis) {
        std::cerr << "Cannot open file: " << argv[1] << std::endl;
        return 1;
    }
    
    std::string code((std::istreambuf_iterator<char>(fis)),
                     std::istreambuf_iterator<char>());
    
    auto tokens = lexer::process(code);
    std::vector<ASTNode*> statements;
    parser p;
    p.parseAll(tokens, statements);
    
    if (statements.empty()) {
        std::cerr << "Parse error: no statements" << std::endl;
        return 1;
    }
    
    std::map<std::string, std::string> variables;
    
    int result = 0;
    for (ASTNode* stmt : statements) {
        result = evaluate(stmt, variables);
    }
    
    // std::cout << result << std::endl;
    return 0;
}
