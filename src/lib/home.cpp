#include <set>
#include "home.h"
#include "menu.h"

namespace home
{

    set<char> main_menu_options = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};

    void Home::startMenu()
    {

        base::showAppTitle();
        cout << "========================================" << endl;
        cout << "|          Data Structure Menu         |" << endl;
        cout << "========================================" << endl;
        cout << "| a -> Array Operations                |" << endl;
        cout << "| b -> Linked List Operations          |" << endl;
        cout << "| c -> Stack Operations                |" << endl;
        cout << "| d -> Queue Operations                |" << endl;
        cout << "| e -> Searching Operations            |" << endl;
        cout << "| f -> Sorting Operations              |" << endl;
        cout << "| g -> Graph Operations                |" << endl;
        cout << "| h -> Tree Operations                 |" << endl;
        cout << "========================================" << endl;
        cout << "| i -> Exit                            |" << endl;
        cout << "========================================" << endl;
        cout << "Choose an option: ";

        menu::getMenuSelection(this->selection_point, main_menu_options, "Home Menu", true);
    };

} // namespace home
