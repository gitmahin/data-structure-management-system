#include "base.h"

namespace base
{

    /**
     * Displays the application title formatted within a decorative border.
     * Uses the APP_TITLE constant defined in the base namespace.
     */
    void showAppTitle()
    {
        cout << "========================================" << endl;
        cout << "|   " << base::APP_TITLE << "   |" << endl;
        cout << "========================================" << endl
             << endl;
    }

    /**
     * Handles the application shutdown process.
     * Prints an exit message to the console before termination.
     */
    void exitApp()
    {
        cout << "Exiting..." << endl;
    };
}