

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#include <type_traits>
#include "base.h"

namespace base
{

    /**
     * Displays the application title formatted within a decorative border.
     * Uses the APP_TITLE constant defined in the base namespace.
     *
     * @code
     *  base::showAppTitle("");
     *  base::showAppTitle("Array Operations");
     * @endcode
     */
    void showAppTitle(std::string sub_title)
    {
        std::cout << "///////////////////////////////////////////\n";
        std::cout << base::APP_TITLE << std::endl;
        if (sub_title != "")
        {
            std::cout << "[" << sub_title << "]" << std::endl;
        }
        std::cout << "///////////////////////////////////////////\n\n";
    }

    /**
     * Scroll and hides the terminal screen text and moves the cursor to the
     * home position. Uses ANSI escape codes: \033[2J to clear the screen and
     * \033[1;1H to reset the cursor position.
     *
     * Reference: https://stackoverflow.com/a/75486350/23577239
     *
     * @code
     *  base::hideTextOfScreen();
     * @endcode
     */
    void hideTextOfScreen()
    {
        printf(
            "\033[2J"      // scroll & hide the visible screen
            "\033[1;1H");  // move cursor home
    }

    /**
     * Clears the terminal screen.
     * Uses the system-specific command ("cls" for Windows, "clear" for POSIX)
     * to provide a clean interface.
     *
     * @code
     *  base::clearScreen();
     * @endcode
     */
    void clearScreen()
    {
        // clang-format off
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        // clang-format on
    };

    /**
     * Pauses the program execution for a specified number of seconds.
     * Uses platform-specific sleep functions (Sleep for Windows, usleep for
     * POSIX).
     * @param second The duration to pause in seconds.
     *
     * @code
     *  base::pauseProgram(2); // Pauses for 2 seconds
     * @endcode
     */
    void pauseProgram(int second)
    {
        std::cout.flush();
        // clang-format off
        #ifdef _WIN32
            Sleep(second * 1000);
        #else  
            usleep(second * 1000000);
        #endif
        // clang-format on
    };

    /**
     * Handles type-safe integer input from the user.
     * Repeatedly prompts the user until a valid integer is entered.
     * Includes validation to handle input failures and buffer clearing.
     * @param i_variable Reference to store the valid integer input.
     * @param max The maximum allowed value (inclusive).
     * @param min The minimum allowed value (inclusive).
     *
     * @code
     *  int size;
     *  cout << "Enter size: ";
     *  // Max 50 and min 0 by defualt
     *  base::getIntInput(size, 50);
     *  // Max 50 and min 2
     *  base::getIntInput(size, 50, 2);
     * @endcode
     */
    void getIntInput(int& i_variable, int max, int min)
    {
        while (true)
        {
            std::cin >> i_variable;

            if (std::cin.fail())
            {
                std::cin.clear();
                while (std::cin.get() != '\n');  // flush bad inputs
                std::cout << "Invalid input! Try again: ";
                continue;
            }

            if (i_variable < min || i_variable > max)
            {
                std::cin.clear();
                while (std::cin.get() != '\n');  // flush bad inputs
                std::cout << "Out of range! Must be between " << min << " and "
                          << max << ". Try again: ";
                continue;
            }

            while (std::cin.get() != '\n');
            break;
        }
    }

    /**
     * Prompts the user with a yes/no question and returns the result.
     *
     * Validates input to ensure only 'y' or 'n' (case-insensitive) are
     * accepted.
     *
     * @param default_value The value to return if logic requires a fallback.
     * @param question The string to display as the prompt.
     * @return 1 if the user chooses 'y', 0 if the user chooses 'n'.
     *
     * @code
     *  bool save = base::askUser(false, "Do you want to save");
     * @endcode
     */
    int askUser(int default_value, std::string question)
    {
        int result = default_value;
        char input;
        char lower_case_input;

        std::cout << question << " [y/n]: ";
        while (true)
        {
            std::cin >> input;

            lower_case_input = (char)tolower(input);

            if (std::cin.fail() ||
                (lower_case_input != 'y' && lower_case_input != 'n'))
            {
                std::cin.clear();
                while (std::cin.get() != '\n');  // flush bad inputs
                std::cout << "Invalid input! You have to choose [y/n]: ";
                continue;
            }

            while (std::cin.get() != '\n');
            break;
        }

        if (lower_case_input == 'y')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    /**
     * Displays a menu of supported data types for user selection.
     *
     * Shows options for int, double, string, and char, which correspond
     * to the types supported by VariantSupportedDataType.
     *
     * @code base::showAvailableDataTypesMenu(); @endcode
     */
    void showAvailableDataTypesMenu()
    {
        std::cout << "=====================================\n";
        std::cout << "|           Choose Data Type        |\n";
        std::cout << "=====================================\n";
        std::cout << "| a -> int                          |\n";
        std::cout << "| b -> double                       |\n";
        std::cout << "| c -> string                       |\n";
        std::cout << "| d -> char                         |\n";
        std::cout << "=====================================\n";
        std::cout << "| z -> Back                         |\n";
        std::cout << "=====================================\n";
        std::cout << "Select the data type you want: ";
    }

    /**
     * Displays a summary of an element deletion operation in the TUI.
     *
     * Shows the count of elements before and after deletion, as well as the
     * value and index of the deleted element.
     *
     * @param before_delete_element_count The size of the collection before
     * deletion.
     * @param deleted_element_index       The index where the element was
     * removed.
     * @param curr_element_count          The size of the collection after
     * deletion.
     * @param data                        A variant containing the value of the
     * deleted element.
     *
     * @code base::elementDeletionResultTUI(5, 2, 4, my_variant); @endcode
     */
    void elementDeletionResultTUI(int before_delete_element_count,
                                  int deleted_element_index,
                                  int curr_element_count,
                                  base::VariantSupportedDataType data)
    {
        std::cout << "Element deleted successfully." << std::endl;
        std::cout << std::endl << "Deletion Result" << std::endl;
        std::cout << "Previous Number of Elements: "
                  << before_delete_element_count << std::endl;
        std::cout << "Current Number of Elements: " << curr_element_count
                  << std::endl;

        std::visit(
            [&](auto& e)
            {
                std::cout << "Deleted Element: " << e
                          << " [Index: " << deleted_element_index << "]"
                          << std::endl;
            },
            data);
    }

    /**
     * Logs the value of a VariantSupportedDataType to the standard output.
     * Uses std::visit to handle the underlying type within the variant.
     *
     * @param data The variant containing the data to be logged.
     */
    void logVariantData(VariantSupportedDataType data)
    {
        std::visit([](auto element) { std::cout << element; }, data);
    };

    VariantSupportedDataType getVariantDataInput(VariantSupportedDataType data)
    {
        VariantSupportedDataType result;
        std::visit(
            [&result](auto val)
            {
                typename std::decay_t<decltype(val)> element;

                while (true)  // ← keep asking until valid input
                {
                    std::cout << "Enter element ["
                              << base::type_name<decltype(element)>() << "]: ";

                    // compare two types: if value type is string then use
                    // getline to take input

                    if constexpr (std::is_same_v<std::decay_t<decltype(val)>,
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
            data);

        return result;
    }

    /**
     * Handles the application shutdown process.
     * Prints an exit message to the console before termination.
     */
    void exitApp() { std::cout << "Exiting..." << std::endl; };
}  // namespace base