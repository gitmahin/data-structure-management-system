#include "arrayo.h"

#include <set>
#include <type_traits>
#include <vector>

#include "menu.h"
#include "presskey.h"

namespace arrayo
{

    // Constant values
    set<char> sub_menu_options = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'z'};
    set<char> array_data_type_options = {'a', 'b', 'c', 'd', 'z'};

    /**
     * Handles type-safe input for elements within a vector data.
     *
     * Uses std::visit and compile-time type checking (if constexpr) to
     * prompt the user for input based on the underlying vector data type.
     * Includes validation to handle input failures and buffer clearing.
     * @param data The variant containing a data of supported types.
     * @param i    The index of the element to be populated.
     *
     * @code
     *  for (int i = 0; i < initial_array_size; i++)
     *  {
     *    validVectorCreateInput(my_array, i);
     *  }
     * @endcode
     */
    void validVectorCreateInput(VariantVectorDataType& data, int i)
    {
        visit(
            [i](auto& element)
            {
                while (true)  // ← keep asking until valid input
                {
                    cout << "Enter element [" << i << "]: ";

                    // if value type is string then use getline to take
                    // input
                    if constexpr (is_same_v<decay_t<decltype(element[0])>,
                                            string>)
                    {
                        getline(cin, element[i]);
                        break;
                    }
                    else
                    {
                        cin >> element[i];

                        if (cin.fail())
                        {
                            cin.clear();
                            while (cin.get() != '\n');  // flush bad inputs
                            cout << "Invalid input! Try again." << endl;
                            continue;
                        }

                        while (cin.get() != '\n');
                        break;
                    }
                }
            },
            data);
    }

    /**
     * Handles type-safe input for a single element to be inserted into the
     * array.
     *
     * Determines the required data type based on the current state of the
     * VariantVectorDataType and prompts the user for a matching value.
     * @param data The variant containing the vector to determine the expected
     * type.
     * @return A variant containing the validated user input.
     *
     * @code
     *  base::VariantSupportedDataType usr_input;
     *  usr_input = validVectorInsertInput(my_array);
     * @endcode
     */
    base::VariantSupportedDataType validVectorInsertInput(
        VariantVectorDataType& data)
    {
        base::VariantSupportedDataType result;
        visit(
            [&result](auto& vec)
            {
                typename decay_t<decltype(vec)>::value_type element;
                while (true)  // ← keep asking until valid input
                {
                    cout << "Enter element: ";

                    // compare two types: if value type is string then use
                    // getline to take input

                    if constexpr (is_same_v<decay_t<decltype(vec[0])>, string>)
                    {
                        getline(cin, element);
                        break;
                    }
                    else
                    {
                        cin >> element;

                        if (cin.fail())
                        {
                            cin.clear();
                            while (cin.get() != '\n');  // flush bad inputs
                            cout << "Invalid input! Try again." << endl;
                            continue;
                        }

                        while (cin.get() != '\n');
                        break;
                    }
                }

                result = element;
            },
            data);

        return result;
    }

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
        cout << "| z -> Main Menu                       |" << endl;
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
        cout << "| z -> Array Operation Menu            |" << endl;
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
            case 'z':
                // back to array start page
                base::clearScreen();
                return;
            default:
                return;
        }

        // Take initial size of the array from user;

        int initial_array_size = 0;
        cout << "Enter initial size of array: ";
        // User can create initial array with max size 100
        base::getIntInput(initial_array_size, 100);

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
            validVectorCreateInput(this->my_array, i);
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

    /**
     * Iterates through the array and prints each element to the console.
     * Uses std::visit to handle the underlying vector type within the
     * VariantVectorDataType variant.
     */
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

    /**
     * Inserts an element into the array at a specified position.
     *
     * @param label   The text prompt to display to the user.
     * @param atBegin If true, inserts the element at the start of the array.
     * @param atEnd   If true, inserts the element at the end of the array.
     * @param atIndex If true, inserts the element at the specified index.
     * @param index   The target index for insertion (used only if atIndex is
     * true).
     *
     * @code
     *  arrayOpr->insertAt(
     *   "Inserting array at the beginning. (to abort "
     *   "operation type "
     *   "exit)",
     *   true);
     * @endcode
     */
    void ArrayO::insertAt(string label, bool atBegin, bool atEnd, bool atIndex,
                          int index)
    {
        base::VariantSupportedDataType i_element;

        cout << endl << label << endl;
        i_element = validVectorInsertInput(this->my_array);

        // string exit_word = get<string>(i_element);
        // if (exit_word == "exit")
        // {
        //     return;
        // }

        visit(
            // catch everything by reference
            [&](auto& vec)
            {
                /**
                 * Defined in header <type_traits>
                 * decay_t Reference:
                 * https://en.cppreference.com/cpp/types/decay
                 */
                using ArrayType = decay_t<decltype(vec)>::value_type;

                visit(
                    [&](auto& element)
                    {
                        // if input value matches with already stored vector
                        // data type then insert value
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

        cout << "Element inserted success.";
        base::pauseProgram(1);
    }

    /**
     * Retrieves the current number of elements in the array.
     * Uses std::visit to access the size of the underlying vector.
     *
     * @return The total number of elements in the array.
     *
     * @code
     *  int count = arrayOpr->getArraySize();
     *  cout << "Array has " << count << " elements." << endl;
     * @endcode
     */
    int ArrayO::getArraySize()
    {
        int size;
        visit([&size](auto& vec) { size = vec.size(); }, this->my_array);

        return size;
    }

    void ArrayO::deleteElement(bool atBegin, bool atEnd, bool atIndex,
                               int index)
    {
        visit(
            // catch everything by reference
            [&](auto& vec)
            {
                if (vec.empty())
                {
                    cout << "Cannot delete from an empty array!" << endl;
                    return;
                }

                if (atBegin)
                {
                    vec.erase(vec.begin());
                }

                if (atEnd)
                {
                    vec.pop_back();
                }

                if (atIndex)
                {
                    vec.erase(vec.begin() + index);
                }
            },
            this->my_array);

        cout << "Element deleted success.";
        base::pauseProgram(2);
    }

}  // namespace arrayo