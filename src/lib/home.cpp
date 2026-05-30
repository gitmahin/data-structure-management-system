#include "home.h"

#include <set>

#include "menu.h"

namespace home
{

    std::set<char> main_menu_options = {'a', 'b', 'c', 'd', 'e', 'f',
                                        'g', 'h', 's', 'u', 'z'};

    /**
     * Displays the main application menu and handles top-level navigation.
     *
     * This function renders the primary interface for selecting different data
     * structure operations. It also provides options to toggle data persistence
     * (saving/unsaving) and to exit the application.
     *
     * @param saveAllData A boolean flag indicating if the UI should show the
     *                    option to "unsave" (true) or "save" (false) data.
     */
    void Home::startMenu(bool saveAllData)
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

        if (saveAllData)
        {
            std::cout << "| u -> Delete all data and unsave      |\n";
        }
        else
        {
            std::cout << "| s -> Save all data                   |\n";
        }
        std::cout << "| z -> Exit                            |\n";
        std::cout << "========================================\n";
        std::cout << "Choose an option: ";

        menu::getMenuSelection(this->selection_point, main_menu_options,
                               "Home Menu", true);
    };

}  // namespace home
