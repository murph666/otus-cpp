#pragma once

#include <algorithm>
#include <iostream>

template <typename T>
class SerialContainer
{
public:
	struct Iterator
	{
		Iterator(): iter_ptr{nullptr}{}
		explicit Iterator(T* new_iter_ptr) : iter_ptr{ new_iter_ptr } {}

		T* operator++(){
			iter_ptr = iter_ptr + 1;
			return iter_ptr;

		}
		T& operator*(){
			return *iter_ptr;
		}

		bool operator==(const Iterator& another){
			return (iter_ptr == another.iter_ptr);
		}

		bool operator!=(const Iterator& another){
			return !(iter_ptr == another.iter_ptr);
		}
	private:
	T* iter_ptr;
	};
	

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

	void reserve()
	{

		T *new_data_ptr = new T[capacity]; //отводим место под новый массив

		if (data_ptr == nullptr)
		{ //если массив пустой
			data_ptr = new_data_ptr;

			return;
		}
		// for (unsigned int i = 0; i < data_ptr[i]; ++i)
		for (unsigned int i = 0; i < total_number; ++i)
		{ //если не пустой то переносим со старого в новый
			new_data_ptr[i] = data_ptr[i];
		}

		delete[] data_ptr; //удаляем старый

		data_ptr = new_data_ptr;
	}

	void push_back(const T &value)
	{
		++capacity;
		reserve();
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
		++capacity;
		reserve();
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

	Iterator begin() const{
		return Iterator(&data_ptr[0]);
	}

	Iterator last_valid() const{
		return Iterator(&data_ptr[total_number - 1]);
	}

	Iterator end() const{
		return Iterator(&data_ptr[total_number]);
	}


private:
	T *data_ptr; //массив указателей <Т> типа

	unsigned int total_number; //общая длинна
	unsigned int capacity;	   //емкость
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const SerialContainer<T>& container){
	for(auto iter = container.begin(); iter != container.end(); ++iter)
	{
		os << *iter;
		if (iter != container.last_valid()) {os << ", ";}
		else {os << std::endl;}
	} 
	return os;
}
