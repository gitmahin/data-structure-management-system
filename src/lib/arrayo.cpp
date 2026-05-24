#include <set>
#include <vector>
#include "arrayo.h"
#include "menu.h"

namespace arrayo
{
    set<char> sub_menu_options = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'i'};
    set<char> array_data_type_options = {'a', 'b', 'c', 'd', 'i'};
    void ArrayO::startMenu()
    {
        cout << "========================================" << endl;
        cout << "|           Array Operations           |" << endl;
        cout << "========================================" << endl;
        cout << "| a -> Create Array                    |" << endl;
        cout << "| b -> Traverse Array                  |" << endl;
        cout << "| c -> Stack Operations                |" << endl;
        cout << "| d -> Insert at End                   |" << endl;
        cout << "| e -> Insert at Any Position          |" << endl;
        cout << "| f -> Delete from Beginning           |" << endl;
        cout << "| g -> Delete from Any Position        |" << endl;
        cout << "========================================" << endl;
        cout << "| i -> Main Menu                       |" << endl;
        cout << "========================================" << endl;
        cout << "Choose an array operation: ";

        menu::getMenuSelection(this->selection_point, sub_menu_options, "Array Operations", false);
    };

    void ArrayO::createArray()
    {
        cout << "========================================" << endl;
        cout << "|        Choose Array Data Type        |" << endl;
        cout << "========================================" << endl;
        cout << "| a -> int                             |" << endl;
        cout << "| b -> double                          |" << endl;
        cout << "| c -> string                          |" << endl;
        cout << "| d -> char                            |" << endl;
        cout << "========================================" << endl;
        cout << "| i -> Main Menu                       |" << endl;
        cout << "========================================" << endl;
        cout << "Select the array data type you want: ";

        menu::getMenuSelection(this->selected_data_type, array_data_type_options, "Array Data Types", false);

        switch (this->selected_data_type)
        {
        case 'a':
            my_array = vector<int>();
            break;
        case 'b':
            my_array = vector<double>();
            break;
        case 'c':
            my_array = vector<string>();
            break;
        case 'd':
            my_array = vector<char>();
        default:
            break;
        }

        // Take initial size of the array from user;

        int initial_array_size = 0;
        cout << "Enter initial size of array: ";
        cin >> initial_array_size;
        cin.ignore();

        /**
         * std::visit references
         *
         * redit reference: https://www.reddit.com/r/cpp_questions/comments/12ur4wv/comment/jh9850n/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button
         * cpp reference: https://en.cppreference.com/cpp/utility/variant/visit2
         */

        visit([&initial_array_size](auto &vec){
            vec.resize(initial_array_size);
        }, my_array);

        for (int i = 0; i < initial_array_size; i++)
        {

            visit(
                [i](auto &vec)
                {
                    // get type from vec[0];
                    auto value = vec[0];
                    cout << "Enter element [" << i << "]: ";
                    cin >> value;
                    vec[i] = value;
                },
                my_array);
        }

        visit([](auto &vec)
              {
            for(auto &element: vec) {
                cout<<"Element is: "<<element<<endl;
            } }, my_array);
        cout << "Elements are inserted. Now you can play with this elements."<<endl;
        return;
    }

}