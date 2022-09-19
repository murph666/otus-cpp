#pragma once

#include "astnode.hpp"

class Variable : public ASTNode {
public:
    Variable(std::string str)
        : ASTNode{ str }
        , str_{ str } {}

    std::string value() const { return str_; }

private:
    std::string str_;
};
