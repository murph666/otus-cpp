// OTUS C++ Basic course homework skeleton.
// Lexer interface

#pragma once

#include <istream>
#include <string>
#include <iostream>

class Lexer {
  public:
    enum class Token {
        Number,
        Operator,
        End,
        Lbrace,
        Rbrace,
        Name,
    };
    // ***nonconverting constructors***
    //Aвтоматическое конвертирование не будет выполняться
    //Допустимыми являются только конструкции следующего вида: Lexer lexer(std::cin)
    explicit Lexer(std::istream &in);

    //Ключевое слово delete используется в случаях, когда нужно запретить автоматическое
    //приведение типов в конструкторах и методах класса.

    //При использовании конструктора с указателем на lexer - бан
    Lexer(const Lexer &other) = delete;
    //При ......................................................
    Lexer &operator=(const Lexer &other) = delete;

    Token next_token();

    //методы класса
    int get_number() const { return number_; }
    std::string get_operator() const { return operator_; }
    std::string get_name() const { return name_; }

  protected:
    bool isbrace(char ch) const;

    bool isoperator(char ch) const;

  private:
    //Состояние лексера
    enum class State {
        Empty,          //пусто
        ReadNumber,     //прочитано число
        ReadName,       //прочитана переменная
        End,
    };
    char next_char();
    bool end() const;

    State state_;
    std::string name_;
    int number_;
    std::string operator_;
    char ch_;
    std::istream &in_;
};
//Создаем "пустой" лексер и сразу читаем символ
inline Lexer::Lexer(std::istream &in): state_(State::Empty), number_(0), in_(in) {

    next_char();
}
//Возвращает следущий символ в потоке
inline char Lexer::next_char() {
//    std::cout<<"qwe";
    in_.get(ch_);
    return ch_;
}


//Анализ строк
inline bool Lexer::end() const { return in_.eof() || ch_ == '\n'; } // Конец потока?

inline bool Lexer::isbrace(char ch) const { return ch == '(' || ch == ')'; } //Символ == скобка?

inline bool Lexer::isoperator(char ch) const { // Символ == математический оператор?
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}
