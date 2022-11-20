#include "serial_container.hpp"
#include "one_way_list_container.hpp"

void test_serial_container()
{
	std::cout << "========Serial container testing========" << std::endl;

	SerialContainer<int> serial_container;

	for (int i = 0; i < 10; ++i)
	{
		serial_container.push_back(i);
	}

	std::cout << serial_container;
	std::cout << "Container size: " << serial_container.size() << std::endl;
	std::cout << "Container capacity: " << serial_container.capacity() << std::endl  << std::endl;

	std::cout << "Delete items with the number 3, 5, 7" << std::endl;
	serial_container.erase(3);
	serial_container.erase(5 - 1);
	serial_container.erase(7 - 2);

	std::cout << serial_container;
	std::cout << "Container size: " << serial_container.size() << std::endl;
	std::cout << "Container capacity: " << serial_container.capacity() << std::endl << std::endl;

	std::cout << "Adding 10 to the beginning of the container" << std::endl;
	serial_container.insert(0, 10);

	std::cout << serial_container;
	std::cout << "Container size: " << serial_container.size() << std::endl;
	std::cout << "Container capacity: " << serial_container.capacity() << std::endl << std::endl;

	std::cout << "Adding 20 to the center of the containerr" << std::endl;
	serial_container.insert(serial_container.size() / 2, 20);

	std::cout << serial_container;
	std::cout << "Container size: " << serial_container.size() << std::endl;
	std::cout << "Container capacity: " << serial_container.capacity() << std::endl << std::endl;

	std::cout << "Adding 30 to the finish of the container" << std::endl;
	serial_container.insert(serial_container.size(), 30);

	std::cout << serial_container;
	std::cout << "Container size: " << serial_container.size() << std::endl;
	std::cout << "Container capacity: " << serial_container.capacity() << std::endl << std::endl;
}

void test_OneWayList_container()
{
	std::cout << "========OneWayList container testing========" << std::endl;

	OneWayList<int> OneWayList_container;
	for (int i = 0; i < 10; ++i)
	{
		OneWayList_container.push_back(i);
	}
	std::cout << OneWayList_container;
	std::cout << "Container size: " << OneWayList_container.size() << std::endl
			  << std::endl;

	std::cout << "Delete items with the number 3, 5, 7" << std::endl;
	OneWayList_container.erase(2);
	OneWayList_container.erase(4 - 1);
	OneWayList_container.erase(6 - 2);
	// OneWayList_container.erase(0);

	std::cout << OneWayList_container;
	std::cout << "Container size: " << OneWayList_container.size() << std::endl
			  << std::endl;

	std::cout << "Adding 10 to the beginning of the container" << std::endl;
	OneWayList_container.insert(0, 10);

	std::cout << OneWayList_container;
	std::cout << "Container size: " << OneWayList_container.size() << std::endl
			  << std::endl;

	std::cout << "Adding 20 to the center of the containerr" << std::endl;
	OneWayList_container.insert(OneWayList_container.size() / 2, 20);

	std::cout << OneWayList_container;
	std::cout << "Container size: " << OneWayList_container.size() << std::endl
			  << std::endl;

	std::cout << "Adding 30 to the finish of the container" << std::endl;
	OneWayList_container.insert(OneWayList_container.size(), 30);

	std::cout << OneWayList_container;
	std::cout << "Container size: " << OneWayList_container.size() << std::endl
			  << std::endl;
}

int main()
{
	test_serial_container();
	test_OneWayList_container();
	return 0;
}