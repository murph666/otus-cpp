#include "serial_container.hpp"

void test_serial_container()
{
	std::cout << "Serial container testing\n"
			  << std::endl;
	//создание объекта контейнера для хранения объектов типа int
	SerialContainer<int> serial_container;

	for (int i = 0; i < 10; ++i)
	{
		serial_container.push_back(i);
	}

	int *ptr = &serial_container[0];
	for (int i = 0; i < 10; ++i)
	{
		std::cout << *(ptr + i);
		if (i != 9)
		{
			std::cout << ", ";
		}
		else
		{
			std::cout << std::endl;
		}
	}

	std::cout << "Container size: " << serial_container.size() << std::endl
			  << std::endl;
	std::cout << "Delete items with the number 3, 5, 7" << std::endl;

	// serial_container.erase(3);
	// serial_container.erase(5 - 1);
	// serial_container.erase(7 - 2);

	for (int i = 0; i < serial_container.size(); ++i)
	{
		std::cout << *(ptr + i);
		if (i != serial_container.size() - 1)
		{
			std::cout << ", ";
		}
		else
		{
			std::cout << std::endl;
		}
	}
	std::cout << "Container size: " << serial_container.size() << std::endl
			  << std::endl;

	std::cout << "Insert 10 at 0 position" << std::endl;

	serial_container.insert(0, 10);

	for (int i = 0; i < serial_container.size(); ++i)
	{
		std::cout << *(ptr + i);
		if (i != serial_container.size() - 1)
		{
			std::cout << ", ";
		}
		else
		{
			std::cout << std::endl;
		}
	}
	std::cout << "Container size: " << serial_container.size() << std::endl
			  << std::endl;
}

int main()
{
	test_serial_container();
	return 0;
}