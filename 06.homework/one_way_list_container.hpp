#pragma once

#include <iostream>

// Базовый узел - элемент
template <class T>
struct Node
{
    Node() : next{nullptr} {}
    explicit Node(const T &value) : next{nullptr}, data{value} {}

    T data;     // данные
    Node *next; // следующий элемент
};

template <typename T>
class OneWayList
{
public:
    struct Iterator
    {
        Iterator() : iter_node{nullptr} {}
        explicit Iterator(Node<T> *new_iter_ptr) : iter_node{new_iter_ptr} {}

        Node<T> *operator++()
        {
            iter_node = iter_node->next;
            return iter_node;
        }
        T &operator*()
        {
            return iter_node->data;
        }

        bool operator==(const Iterator &another)
        {
            return (iter_node == another.iter_node);
        }

        bool operator!=(const Iterator &another)
        {
            return !(iter_node == another.iter_node);
        }

    private:
        Node<T> *iter_node;
    };

    OneWayList() : begin_node{nullptr}, end_node{nullptr}, total_number{0}
    {
        std::cout << "OneWayList Container default constructor" << std::endl;
    }

    // ~OneWayList()
    // {
    //     if (total_number != 0)
    //     {
    //         begin_node = nullptr;
    //         end_node = nullptr;
    //         total_number = 0;
    //     }
    // }

    int size() { return total_number; }

    void push_back(const T &value)
    {
        //Создаем новую ноду
        Node<T> *new_value = new Node<T>;
        new_value->data = value;
        new_value->next = nullptr;
        //Если пустой -> новая нода будет начальной
        if (total_number == 0)
        {
            begin_node = end_node = new_value;
            total_number++;
        }
        //Если нет, то новая нода становится последней
        else
        {
            end_node->next = new_value;
            end_node = new_value;
            total_number++;
        }
    }

    Node<T> *move(const unsigned int position)
    {
        if (total_number > 0)
        {
            Node<T> *temp_node = begin_node;
            for (unsigned int i = 0; i < position; i++)
            {
                temp_node = temp_node->next;
            }
            return temp_node;
        }
        return nullptr;
    }

    void erase(const unsigned int position)
    {
        if (position != 0)
        {
            Node<T> *del_node = move(position);
            Node<T> *prev_del_node = move(position - 1);

            prev_del_node->next = del_node->next;
            delete del_node;
        }
        else
        {
            Node<T> *del_node = begin_node;
            begin_node = del_node->next;
            delete del_node;
        }
        total_number--;
    }

    void insert(const unsigned int position, const T &value)
    {
        if (position == total_number)
        {
            push_back(value);
        }
        else if (position == 0)
        {
            Node<T> *new_node = new Node<T>;
            new_node->data = value;
            new_node->next = begin_node;
            begin_node = new_node;
            total_number++;
        }
        
        else
        {
            Node<T> *new_node = new Node<T>;
            Node<T> *insert_node = move(position - 1);

            new_node->data = value;
            new_node->next = insert_node->next;

            insert_node->next = new_node;
            total_number++;
        }
    }

    T &operator[](const unsigned int place)
    {
        Node<T> *temp_node = move(place);
        return temp_node->data;
    }

    Iterator begin() const
    {
        return Iterator(begin_node);
    }

    Iterator last_valid() const
    {
        if (end_node != nullptr)
        {
            return Iterator(end_node);
        }
        else
        {
            return Iterator(nullptr);
        }
    }

    Iterator end() const
    {
        if (end_node != nullptr)
        {
            return Iterator(end_node->next);
        }
        else
        {
            return Iterator(nullptr);
        }
    }

private:
    Node<T> *begin_node;       // указатель на начало списка
    Node<T> *end_node;         // указатель на конец списка
    unsigned int total_number; // количество элементов в списке
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const OneWayList<T> &container)
{
    for (auto iter = container.begin(); iter != container.end(); ++iter)
    {
        os << *iter;
        if (iter != container.last_valid())
        {
            os << ", ";
        }
        else
        {
            os << std::endl;
        }
    }
    return os;
}
