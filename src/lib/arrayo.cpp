#include "arrayo.h"

#include <set>
#include <vector>

#include "menu.h"
#include "presskey.h"

namespace arrayo
{

    // Constant values
    set<char> sub_menu_options = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'i'};
    set<char> array_data_type_options = {'a', 'b', 'c', 'd', 'i'};

    void ArrayO::startMenu()
    {
        // Clear home page for new page this
        base::clearScreen();
        base::showAppTitle("Array Operations");
        cout << "========================================" << endl;
        cout << "|            Operations Menu           |" << endl;
        cout << "========================================" << endl;
        cout << "| a -> Create Array                    |" << endl;
        cout << "| b -> Traverse Array                  |" << endl;
        cout << "| c -> Insert at Beginning             |" << endl;
        cout << "| d -> Insert at End                   |" << endl;
        cout << "| e -> Insert at Any Position          |" << endl;
        cout << "| f -> Delete from Beginning           |" << endl;
        cout << "| g -> Delete from End                 |" << endl;
        cout << "| h -> Delete from Any Position        |" << endl;
        cout << "========================================" << endl;
        cout << "| i -> Main Menu                       |" << endl;
        cout << "========================================" << endl;
        cout << "Choose an array operation: ";

        menu::getMenuSelection(this->selection_point, sub_menu_options,
                               "Array Operations", false);
    };

    void ArrayO::createArray()
    {
        base::hideTextOfScreen();
        cout << "========================================" << endl;
        cout << "|        Choose Array Data Type        |" << endl;
        cout << "========================================" << endl;
        cout << "| a -> int                             |" << endl;
        cout << "| b -> double                          |" << endl;
        cout << "| c -> string                          |" << endl;
        cout << "| d -> char                            |" << endl;
        cout << "========================================" << endl;
        cout << "| i -> Array Operation Menu            |" << endl;
        cout << "========================================" << endl;
        cout << "Select the array data type you want: ";

        menu::getMenuSelection(this->selected_data_type,
                               array_data_type_options, "Array Data Types",
                               false);

        base::hideTextOfScreen();

        switch (this->selected_data_type)
        {
            case 'a':
                cout << "Creating Dynamic Array: Selected data type [int]"
                     << endl;
                this->my_array = vector<int>();
                break;
            case 'b':
                cout << "Creating Dynamic Array: Selected data type [double]"
                     << endl;
                this->my_array = vector<double>();
                break;
            case 'c':
                cout << "Creating Dynamic Array: Selected data type [string]"
                     << endl;
                this->my_array = vector<string>();
                break;
            case 'd':
                cout << "Creating Dynamic Array: Selected data type [char]"
                     << endl;
                this->my_array = vector<char>();
            case 'i':
                // back to array start page
                base::clearScreen();
                return;
            default:
                return;
        }

        // Take initial size of the array from user;

        int initial_array_size = 0;
        cout << "Enter initial size of array: ";
        cin >> initial_array_size;
        cin.ignore();

        /**
         * std::visit references
         *
         * redit reference:
         * https://www.reddit.com/r/cpp_questions/comments/12ur4wv/comment/jh9850n/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button
         * cpp reference: https://en.cppreference.com/cpp/utility/variant/visit2
         */

        visit([&initial_array_size](auto& vec)
              { vec.resize(initial_array_size); }, this->my_array);

        for (int i = 0; i < initial_array_size; i++)
        {
            base::validVariantInputItr(this->my_array, i);
        }

        visit(
            [](auto& vec)
            {
                for (auto& element : vec)
                {
                    cout << "Element is: " << element << endl;
                }
            },
            this->my_array);
        cout << "Elements are inserted. Now you can play with this elements."
             << endl;

        return;
    }

    void ArrayO::traverseArray()
    {
        visit(
            [](auto& vec)
            {
                for (auto& element : vec)
                {
                    cout << element << endl;
                }
            },
            this->my_array);
    }

    void ArrayO::insertAt(string label, bool atBegin, bool atEnd, bool atIndex,
                          int index)
    {
        base::VariantSingleDataType i_element;
        cout << "Your created array is: " << endl;
        this->traverseArray();

        cout << endl << label << endl;
        i_element = base::validVariantInput(this->my_array);

        string exit_word = get<string>(i_element);
        if (exit_word == "exit")
        {
            return;
        }

        visit(
            // catch everything by reference
            [&](auto& vec)
            {
                using ArrayType = decay_t<decltype(vec)>::value_type;

                visit(
                    [&](auto& element)
                    {
                        // if input value matches with supported types then
                        // insert value
                        if constexpr (is_same_v<decay_t<decltype(element)>,
                                                ArrayType>)
                        {
                            if (atBegin)
                            {
                                vec.insert(vec.begin(), element);
                            }

                            if (atEnd)
                            {
                                vec.insert(vec.end(), element);
                            }

                            if (atIndex)
                            {
                                vec.insert(vec.begin() + index, element);
                            }
                        }
                    },
                    i_element);
            },
            this->my_array);

        cout << "Element inserted success";
        base::pauseProgram(2);
    }

}  // namespace arrayo