// OTUS C++ basic course homework.
// ASTNode

#pragma once

#include <cctype>
#include <iostream>
#include <string>

class ASTNode {
  public:
    // Конструктор листа (узел без дочерних узлов)
    explicit ASTNode(const std::string &repr);
    // Конструктор узла (с одним или двумя дочерними узлами)
    ASTNode(const std::string &repr, ASTNode *lhs, ASTNode *rhs);

    //Ключевое слово delete используется в случаях, когда нужно запретить автоматическое
    //приведение типов в конструкторах и методах класса.

    //При использовании конструктора с указателем на ASTNode - бан
    ASTNode(const ASTNode &other) = delete;
    //При ............................................
    ASTNode &operator=(const ASTNode &other) = delete;

    //~(тильда) Это деструктор. Функция гарантированно вызывается, когда объект выходит из области видимости
    ~ASTNode();
    // Представления имени узла в виде строки
    std::string repr() const { return repr_; }
    // Печать всего дерева в текстовом виде
    void print(std::ostream &out) const;

  private:
    void inner_print(std::ostream &out, size_t indent) const;

    std::string repr_;
    ASTNode *lhs_;
    ASTNode *rhs_;
};
