#include "base.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

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
    void showAppTitle(string sub_title)
    {
        cout << "\n========================================" << endl;
        cout << base::APP_TITLE << endl;
        if (sub_title != "")
        {
            cout << "[" << sub_title << "]" << endl;
        }
        cout << "========================================" << endl << endl;
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
        cout.flush();
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
            cin >> i_variable;

            if (cin.fail())
            {
                cin.clear();
                while (cin.get() != '\n');  // flush bad inputs
                cout << "Invalid input! Try again: ";
                continue;
            }

            if (i_variable < min || i_variable > max)
            {
                cin.clear();
                while (cin.get() != '\n');  // flush bad inputs
                cout << "Out of range! Must be between " << min << " and "
                     << max << ". Try again: ";
                continue;
            }

            while (cin.get() != '\n');
            break;
        }
    }

    /**
     * Handles the application shutdown process.
     * Prints an exit message to the console before termination.
     */
    void exitApp() { cout << "Exiting..." << endl; };
}  // namespace base