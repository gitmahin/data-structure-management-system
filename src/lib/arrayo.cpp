#include "arrayo.h"

#include <bitset>
#include <set>
#include <sstream>
#include <type_traits>
#include <vector>

#include "menu.h"
#include "presskey.h"

namespace arrayo
{

  

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
    void ArrayO::validVectorCreateInput( int i)
    {
        std::visit(
            [i](auto& element)
            {
                while (true)  // ← keep asking until valid input
                {
                    std::cout << "Enter element [" << i << "]: ";

                    // if value type is string then use getline to take
                    // input
                    if constexpr (std::is_same_v<
                                      std::decay_t<decltype(element[0])>,
                                      std::string>)
                    {
                        getline(std::cin, element[i]);
                        break;
                    }
                    else
                    {
                        std::cin >> element[i];

                        if (std::cin.fail())
                        {
                            std::cin.clear();
                            while (std::cin.get() != '\n');  // flush bad inputs
                            std::cout << "Invalid input! Try again."
                                      << std::endl;
                            continue;
                        }

                        while (std::cin.get() != '\n');
                        break;
                    }
                }
            },
            this->my_array);
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
    base::VariantSupportedDataType ArrayO::validVectorInsertInput()
    {
        base::VariantSupportedDataType result;
        std::visit(
            [&result](auto& vec)
            {
                typename std::decay_t<decltype(vec)>::value_type element;
        
                while (true)  // ← keep asking until valid input
                {
                    std::cout << "Enter element ["<<base::type_name<decltype(element)>()<<"]: ";

                    // compare two types: if value type is string then use
                    // getline to take input

                    if constexpr (std::is_same_v<std::decay_t<decltype(vec[0])>,
                                                 std::string>)
                    {
                        getline(std::cin, element);
                        break;
                    }
                    else
                    {
                        std::cin >> element;

                        if (std::cin.fail())
                        {
                            std::cin.clear();
                            while (std::cin.get() != '\n');  // flush bad inputs
                            std::cout << "Invalid input! Try again."
                                      << std::endl;
                            continue;
                        }

                        while (std::cin.get() != '\n');
                        break;
                    }
                }

                result = element;
            },
            this->my_array);

        return result;
    }

    void ArrayO::startMenu()
    {
        // Clear home page for new page this
        base::clearScreen();
        base::showAppTitle("Array Operations");
        std::cout << "========================================\n";
        std::cout << "|            Operations Menu           |\n";
        std::cout << "========================================\n";
        std::cout << "| a -> Create Array                    |\n";
        std::cout << "| b -> Traverse Array                  |\n";
        std::cout << "| c -> Insert at Beginning             |\n";
        std::cout << "| d -> Insert at End                   |\n";
        std::cout << "| e -> Insert at Any Position          |\n";
        std::cout << "| f -> Delete from Beginning           |\n";
        std::cout << "| g -> Delete from End                 |\n";
        std::cout << "| h -> Delete from Any Position        |\n";
        std::cout << "========================================\n";
        std::cout << "| z -> Main Menu                       |\n";
        std::cout << "========================================\n";
        std::cout << "Choose an array operation: ";

        menu::getMenuSelection(this->selection_point, arrayo::sub_menu_options,
                               "Array Operations", false);
    };

    void ArrayO::createArray()
    {
        base::hideTextOfScreen();
        base::showAvailableDataTypesMenu();

        menu::getMenuSelection(this->selected_data_type,
                               base::data_type_options, "Array Data Types",
                               false);

        base::hideTextOfScreen();

        switch (this->selected_data_type)
        {
            case 'a':
                std::cout
                    << "Creating Dynamic Array: Selected data type [int]\n";
                this->my_array = std::vector<int>();
                break;
            case 'b':
                std::cout
                    << "Creating Dynamic Array: Selected data type [double]\n";
                this->my_array = std::vector<double>();
                break;
            case 'c':
                std::cout
                    << "Creating Dynamic Array: Selected data type [string]\n";
                this->my_array = std::vector<std::string>();
                break;
            case 'd':
                std::cout
                    << "Creating Dynamic Array: Selected data type [char]\n";
                this->my_array = std::vector<char>();
            case 'z':
                // back to array start page
                base::clearScreen();
                return;
            default:
                return;
        }

        // Take initial size of the array from user;

        int initial_array_size = 0;
        std::cout << "Enter initial size of array: ";
        // User can create initial array with max size 100
        base::getIntInput(initial_array_size, 100);

        /**
         * std::visit references
         *
         * redit reference:
         * https://www.reddit.com/r/cpp_questions/comments/12ur4wv/comment/jh9850n/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button
         * cpp reference: https://en.cppreference.com/cpp/utility/variant/visit2
         */

        std::visit([&initial_array_size](auto& vec)
                   { vec.resize(initial_array_size); }, this->my_array);

        for (int i = 0; i < initial_array_size; i++)
        {
            validVectorCreateInput( i);
        }

        std::visit(
            [](auto& vec)
            {
                for (auto& element : vec)
                {
                    std::cout << "Element is: " << element << std::endl;
                }
            },
            this->my_array);
        std::cout
            << "Elements are inserted. Now you can play with this elements."
            << std::endl;

        return;
    }

    /**
     * Iterates through the array and prints each element to the console.
     * Uses std::visit to handle the underlying vector type within the
     * VariantVectorDataType variant.
     */
    void ArrayO::traverseArray()
    {
        std::visit(
            [](auto& vec)
            {
                for (auto& element : vec)
                {
                    std::cout << element << std::endl;
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
    void ArrayO::insertAt(std::string label, bool atBegin, bool atEnd,
                          bool atIndex, int index)
    {
        base::VariantSupportedDataType i_element;

        std::cout << std::endl << label << std::endl;
        i_element = validVectorInsertInput();

        // string exit_word = get<string>(i_element);
        // if (exit_word == "exit")
        // {
        //     return;
        // }

        std::visit(
            // catch everything by reference
            [&](auto& vec)
            {
                /**
                 * Defined in header <type_traits>
                 * decay_t Reference:
                 * https://en.cppreference.com/cpp/types/decay
                 */
                using ArrayType = typename std::decay_t<decltype(vec)>::value_type;

                std::visit(
                    [&](auto& element)
                    {
                        // if input value matches with already stored vector
                        // data type then insert value
                        if constexpr (std::is_same_v<
                                          std::decay_t<decltype(element)>,
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

        std::cout << "Element inserted successfully.";
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
        std::visit([&size](auto& vec) { size = vec.size(); }, this->my_array);

        return size;
    }

    /**
     * Deletes an element from the array at a specified position.
     *
     * Removes an element based on the provided flags (beginning, end, or
     * index). Displays the deleted element and the updated array size.
     *
     * @param atBegin If true, deletes the first element.
     * @param atEnd   If true, deletes the last element.
     * @param atIndex If true, deletes the element at the specified index.
     * @param index   The target index for deletion (used only if atIndex is
     * true).
     *
     * @code
     *  arrayOpr->deleteElement(true); // Delete from beginning
     *  arrayOpr->deleteElement(false, false, true, 2); // Delete at index 2
     * @endcode
     */
    void ArrayO::deleteElement(bool atBegin, bool atEnd, bool atIndex,
                               int index)
    {
        base::VariantSupportedDataType deleted_element;
        int before_delete_element_count = this->getArraySize();
        int deleted_element_index = 0;
        bool isInvalidRequest = false;

        std::visit(
            // catch everything by reference
            [&](auto& vec)
            {
                if (vec.empty())
                {
                    std::cout << "Cannot delete from an empty array!"
                              << std::endl;
                    base::pauseProgram(1);
                    isInvalidRequest = true;
                }
                else
                {
                    if (atBegin)
                    {
                        deleted_element = vec[0];
                        deleted_element_index = 0;
                        vec.erase(vec.begin());
                    }

                    if (atEnd)
                    {
                        int last_index = vec.size() - 1;
                        deleted_element = vec.at(last_index);
                        deleted_element_index = last_index;
                        vec.pop_back();
                    }

                    if (atIndex)
                    {
                        deleted_element = vec[index];
                        deleted_element_index = index;
                        vec.erase(vec.begin() + index);
                    }
                }
            },
            this->my_array);
        // if there is empty array return
        if (isInvalidRequest) return;

        std::cout << "Element deleted successfully." << std::endl;
        std::cout << std::endl << "Deletion Result" << std::endl;
        std::cout << "Previous Number of Elements: "
                  << before_delete_element_count << std::endl;
        std::cout << "Current Number of Elements: " << this->getArraySize()
                  << std::endl;

        std::visit(
            [&](auto& e)
            {
                std::cout << "Deleted Element: " << e
                          << " [Index: " << deleted_element_index << "]"
                          << std::endl;
            },
            deleted_element);

        presskey::pressAnyKey(
            "Press any key to return to the Array Operations menu.");
    };

}  // namespace arrayo