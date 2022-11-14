#pragma once

#include <algorithm>
#include <iostream>

template <typename T>
class SerialContainer
{
public:
	SerialContainer() : data_ptr{nullptr}, total_number{0}, capacity{0}
	{
		std::cout << "Serial Container default constructor" << std::endl;
	}

	~SerialContainer()
	{
		if (data_ptr != nullptr)
		{
			delete[] data_ptr;
		}
	}
	int size() { return total_number; }

	void reserve(const unsigned int new_capacity)
	{

		T *new_data_ptr = new T[new_capacity]; //отводим место под новый массив

		if (data_ptr == nullptr)
		{ //если массив пустой
			data_ptr = new_data_ptr;
			capacity = new_capacity;
			return;
		}
		// for (unsigned int i = 0; i < data_ptr[i]; ++i)
		for (unsigned int i = 0; i < total_number; ++i)
		{ //если не пустой то переносим со старого в новый
			new_data_ptr[i] = data_ptr[i];
		}

		delete[] data_ptr; //удаляем старый

		data_ptr = new_data_ptr;
		capacity = new_capacity;
	}

	void push_back(const T &value)
	{
		++capacity;
		reserve(capacity);
		data_ptr[total_number] = value;
		++total_number;
	}

	void erase(const unsigned int num)
	{
		for (unsigned int i = num - 1; i < (total_number - 1); ++i)
		{
			data_ptr[i] = data_ptr[i + 1];
		}

		--total_number;
	}

	void insert(const unsigned int position, const int value)
	{
		std::cout << position <<' '<< value<<std::endl;
		++capacity;
		reserve(capacity);
		++total_number;
		for (unsigned int i = total_number - 1; i > position; --i)
		{ //проходим с конца и переносим до position включительно
			data_ptr[i] = data_ptr[i - 1];
		}
		data_ptr[position] = value;
	}

	T &operator[](const size_t &place)
	{
		return data_ptr[place];
	}

private:
	T *data_ptr; //массив указателей <Т> типа

	unsigned int total_number; //общая длинна
	unsigned int capacity;	   //емкость
};
