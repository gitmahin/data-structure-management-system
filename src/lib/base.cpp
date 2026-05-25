#include "base.h"

namespace base
{

    /**
     * Displays the application title formatted within a decorative border.
     * Uses the APP_TITLE constant defined in the base namespace.
     */
    void showAppTitle(string sub_title)
    {
        cout << "========================================" << endl;
        cout << "|   " << base::APP_TITLE << "   |" << endl;
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
    }

    /**
     * Handles the application shutdown process.
     * Prints an exit message to the console before termination.
     */
    void exitApp() { cout << "Exiting..." << endl; };
}  // namespace base