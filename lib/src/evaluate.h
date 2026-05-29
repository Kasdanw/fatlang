#pragma once

#include "AST.h"
#include <string>
#include <map>

int evaluate(ASTNode* node, std::map<std::string, std::string>& variables);
