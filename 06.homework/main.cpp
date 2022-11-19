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
	std::cout << serial_container;


	std::cout << "Container size: " << serial_container.size() << std::endl
			  << std::endl;
	std::cout << "Delete items with the number 3, 5, 7" << std::endl;

	serial_container.erase(3);
	serial_container.erase(5 - 1);
	serial_container.erase(7 - 2);

	std::cout << serial_container;

	std::cout << "Container size: " << serial_container.size() << std::endl
			  << std::endl;

	std::cout << "Adding 10 to the beginning of the container" << std::endl;

	serial_container.insert(0, 10);

	std::cout << serial_container;

	std::cout << "Container size: " << serial_container.size() << std::endl
			  << std::endl;

	std::cout << "Adding 20 to the center of the containerr" << std::endl;

	serial_container.insert(serial_container.size() / 2, 20);

	std::cout << serial_container;

	std::cout << "Container size: " << serial_container.size() << std::endl
			  << std::endl;

	std::cout << "Adding 30 to the finish of the container" << std::endl;

	serial_container.insert(serial_container.size(), 30);

	std::cout << serial_container;

	std::cout << "Container size: " << serial_container.size() << std::endl
			  << std::endl;
}

int main()
{
	test_serial_container();
	return 0;
}