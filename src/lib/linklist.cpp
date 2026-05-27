#include "linklist.h"
#include "menu.h"
#include "set"

namespace lnkls
{
    // Constant values
    std::set<char> sub_menu_options = {'a', 'b', 'c', 'd', 'e',
                                       'f', 'g', 'h', 'z'};

    void LinkList::startMenu()
    {
        // Clear home page for new page
        base::clearScreen();

        base::showAppTitle("Linked List Operations");

        std::cout << "========================================\n";
        std::cout << "|            Operations Menu           |\n";
        std::cout << "========================================\n";
        std::cout << "| a -> Create List                     |\n";
        std::cout << "| b -> Traverse List                   |\n";
        std::cout << "| c -> Insert at Beginning             |\n";
        std::cout << "| d -> Insert at End                   |\n";
        std::cout << "| e -> Insert at Any Position          |\n";
        std::cout << "| f -> Delete from Beginning           |\n";
        std::cout << "| g -> Delete from End                 |\n";
        std::cout << "| h -> Delete from Any Position        |\n";
        std::cout << "========================================\n";
        std::cout << "| z -> Main Menu                       |\n";
        std::cout << "========================================\n";
        std::cout << "Choose a linked list operation: ";

        menu::getMenuSelection(this->selection_point, sub_menu_options,
                               "Linked List Operations", false);
    }

}  // namespace linklist