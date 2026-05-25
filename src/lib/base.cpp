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
     */
    void getIntInput(int& i_variable)
    {
        while(true)
        {
            cin >> i_variable;

            if (cin.fail())
            {
                cin.clear();
                while (cin.get() != '\n');  // flush bad inputs
                cout << "Invalid input! Try again: ";
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