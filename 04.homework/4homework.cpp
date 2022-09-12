#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>


std::string commands[] = {"-max", "-table", "-level"};
int size = sizeof(commands) / sizeof(*commands);

std::vector<std::string> read_from_file(char *filename)
{
    std::ifstream input;
    input.open(filename);
    std::vector<std::string> vec;
    std::string line;
    if (input)
    {
        while (std::getline(input, line))
        {
            vec.push_back(line);
        }
        input.close();
    }
    return (vec);
}

void game(int random_value, std::fstream &filename)
{
    int attempts = 0;
    int prediction;
    std::string Username;
    std::vector<std::string> vec_fileline;
    std::cout << "Hi! Enter your name, please:" << std::endl;
    std::cin >> Username;
    while (true)
    {
        std::cout << "Enter your guess: ";
        std::cin >> prediction;
        attempts++;

        if (prediction < random_value)
        {
            std::cout << "greater than " << prediction << std::endl;
        }
        else if (prediction > random_value)
        {
            std::cout << "less than " << prediction << std::endl;
        }
        else
        {

            std::cout << "you win! attempts: " << attempts << std::endl;

            filename << Username << ": " << attempts << std::endl;
            filename.close();
            break;

        }
    }

    std::cout << std::endl
              << "High scores table:" << std::endl;
    vec_fileline = read_from_file((char *)"scoreboard.csv");

    for (uint i = 0; i < vec_fileline.size(); i++)
    {
        std::cout << vec_fileline.at(i) << std::endl;
    }
}

int main(int argc, char *argv[])
{
    int command = 0;
    std::srand(std::time(nullptr));
    const int max_value = 100;
    const int random_value = std::rand() % max_value;

    std::fstream filename("scoreboard.csv", std::fstream::in | std::fstream::out | std::fstream::app);
    if (!filename)
    {
        std::cout << "open file error!" << std::endl;
        return 1;
    }

    if (argc == 1)
    {
        game(random_value, filename);
    }
    else
    {
        if (argc < 4 && argv[1][0] == '-')
        {
            //Если встретили команду
            bool f_line_found = false;
            for (int i = 0; i < size; i++)
                if (argv[1] == commands[i] || argv[1][1] == commands[i][1])
                {
                    // если строка найдена,
                    command = i + 1;
                    f_line_found = true;
                    std::cout << "Номер команды: " << command << std::endl;
                    break; // то выйти из цикла
                }
            if (!f_line_found)
            {
                std::cout << "Не верная команда. Список доступных команд:" << std::endl;
                for (int i = 0; i < size; ++i)
                {
                    std::cout << commands[i] << "/" << commands[i].substr(0, 2) << std::endl;
                }
            }
        }
        else
        {
            std::cout << "bad command" << std::endl;
        }
    }
    std::map<std::string, int> scoreboard;
    std::vector<std::string> table;
    std::string name;
    int score, user_max_value, user_random_value, level;

    switch (command)
    {
    case 1:
        /* -max */
        user_max_value = std::stoi(argv[2]);
        user_random_value = std::rand() % user_max_value;
        game(user_random_value, filename);

        break;
    case 2:
        /* -table */
        table = read_from_file((char *)"scoreboard.csv");
        for (uint i = 0; i < table.size(); i++)
        {
            name = table.at(i).substr(0, table.at(i).find(":"));
            score = std::stoi(table.at(i).substr(table.at(i).find(":") + 1, table.at(i).length()));

            if (!(bool *)scoreboard.count(name))
            {
                scoreboard.insert(std::pair<std::string, int>(name, score));
            }
            else
            {
                if (scoreboard.at(name) > score)
                {
                    scoreboard.at(name) = score;
                }
            }
        }
        for (const auto &v : scoreboard)
            std::cout << "(" << v.first << ", " << v.second << ") " << std::endl;

        break;
    case 3:
        /* -level */
        level = std::stoi(argv[2]);
        if (level == 1)
            user_max_value = 10;
        else if (level == 2)
            user_max_value = 50;
        else
            user_max_value = 100;
        user_random_value = std::rand() % user_max_value;
        game(user_random_value, filename);
        break;

    default:
        break;
    }

    return 0;
}