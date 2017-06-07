#include <iostream>
#include "PreferencesGraph.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: executable filename1(with names) filename2(with preferences)\n";
        return 0;
    }
    PreferencesGraph graph(argv[1], argv[2]);
    std::cout << "What information do you need?\n" <<
              "1 - Who is the most sympathetic?\n" <<
              "2 - Who is the least sympathetic?\n" <<
              "3 - Who is unhappy?\n";
    char c;
    std::cin >> c;
    std::vector<std::string> to_print(0);
    switch (c) {
        case '1' :
            to_print = graph.get_cute();
            break;
        case '2' :
            to_print = graph.get_ugly();
            break;
        case '3' :
            to_print = graph.get_unhappy();
            break;
        default:
            std::cerr << "Unknown command\n";
            return 0;
    }
    if (to_print.size() > 0)
        for (auto i : to_print)
            std::cout << i << std::endl;
    else
        std::cout << "Nobody" << std::endl;
    return 0;
}