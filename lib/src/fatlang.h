#pragma once

#include <any>
#include <iostream>
#include <string_view>

class fatlang {
public:
    int evaluate(std::string_view code);
};
