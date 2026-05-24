#include "menu.h"

#include <set>
#include <string>

namespace menu
{
    /**
     * Handles validated menu input from the user.
     *
     * Displays available options and repeatedly prompts the user
     * until a valid selection is made. If the input is not found
     * in the provided option set, an error message is shown and
     * the user is asked to try again. Else the selection is stored in
     * selection_point and can be accessed via the object that
     * called this function.
     *
     * @param selection_point     Reference to store the valid user input
     * @param menu_options        Set of valid characters the user can choose
     * @param menu_label          Name of the menu shown in error messages
     * @param shouldExitOnInputI  If true, exits the program when 'i' is entered
     *                            If false, returns back to caller (main menu)
     * @code
     *   set<char> options = {'a', 'b', 'c', 'i'};
     *   char selection;
     *   getMenuSelection(selection, options, "Main Menu", true);
     *   cout << selection;   // access the stored selection
     * @endcode
     */
    void getMenuSelection(char &selection_point, set<char> &menu_options, string menu_label, bool shouldExitOnInputI)
    {

        // Track validity for each input
        bool isInvalidInput = false;
        string available_options = "";

        // here i is the index counter for set
        int i = 0;
        const int number_of_options = menu_options.size();
        for (char option : menu_options)
        {
            available_options += option;
            if (i < number_of_options - 1)
            {
                available_options += "/";
            }
            i++;
        }

        // ask user input until it gets invalid input
        while (true)
        {

            // Take user input
            cin >> selection_point;
            // Remove leftover new line char
            cin.ignore();

            // std::set reference: https://en.cppreference.com/cpp/container/set
            // if user choosen point is available in options; then its valid and break with success
            if (menu_options.count(selection_point))
            {
                isInvalidInput = false;
                if (selection_point == 'i')
                {
                    /**
                     * If developer willing to exit program on input i it will
                     * Otherwise it will send back to main menu
                     */
                    if (shouldExitOnInputI)
                    {
                        base::exitApp();
                    }
                }
            }
            else
            {
                isInvalidInput = true;
                cout << selection_point << " " << "Doesn't exists in " << menu_label << "! Try again!" << endl;
            }

            if (isInvalidInput)
            {
                cout << "You have to choose [" << available_options << "]: ";
                continue;
            }

            break;
        }

        return;
    }
}