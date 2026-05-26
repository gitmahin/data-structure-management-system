#include "home.h"

#include <set>

#include "menu.h"

namespace home
{

    std::set<char> main_menu_options = {'a', 'b', 'c', 'd', 'e',
                                        'f', 'g', 'h', 'z'};

    void Home::startMenu()
    {
        base::showAppTitle("");
        std::cout << "========================================\n";
        std::cout << "|          Data Structure Menu         |\n";
        std::cout << "========================================\n";
        std::cout << "| a -> Array Operations                |\n";
        std::cout << "| b -> Linked List Operations          |\n";
        std::cout << "| c -> Stack Operations                |\n";
        std::cout << "| d -> Queue Operations                |\n";
        std::cout << "| e -> Searching Operations            |\n";
        std::cout << "| f -> Sorting Operations              |\n";
        std::cout << "| g -> Graph Operations                |\n";
        std::cout << "| h -> Tree Operations                 |\n";
        std::cout << "========================================\n";
        std::cout << "| z -> Exit                            |\n";
        std::cout << "========================================\n";
        std::cout << "Choose an option: ";

        menu::getMenuSelection(this->selection_point, main_menu_options,
                               "Home Menu", true);
    };

}  // namespace home
