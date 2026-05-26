#include <sstream>

#include "arrayo.h"
#include "base.h"
#include "home.h"
#include "presskey.h"

using namespace home;
using namespace arrayo;

/**
 * In main function handle all menu switching logic
 * as menu option input is just returning after storing user choice in a
 * variable unless invalid input.
 */
int main()
{
    bool saveAllOperations = false;
    Home* appHome = new Home();
    ArrayO* arrayOpr;

    // Dont exit while user input is not [z]
    while (appHome->selection_point != 'z')
    {
        appHome->startMenu();

        switch (appHome->selection_point)
        {
            case 'a':

            {
                arrayOpr = new ArrayO();

                // Dont exit while user input is not [z]
                while (arrayOpr->selection_point != 'z')
                {
                    arrayOpr->startMenu();

                    switch (arrayOpr->selection_point)
                    {
                        case 'a':
                        {
                            arrayOpr->createArray();
                            break;
                        }
                        case 'b':
                        {
                            base::hideTextOfScreen();
                            // Display array elements
                            cout << "Displaying stored array elements:" << endl;
                            arrayOpr->traverseArray();
                            presskey::pressAnyKey(
                                "Press any key to return to Array Operations "
                                "menu");
                            break;
                        }
                        case 'c':
                        {
                            base::hideTextOfScreen();
                            // Display array elements
                            cout << "Current Array State:" << endl;
                            arrayOpr->traverseArray();

                            //  Perform insertion
                            arrayOpr->insertAt(
                                "Inserting element at the beginning.", true);

                            break;
                        }
                        case 'd':
                        {
                            base::hideTextOfScreen();
                            // Display array elements
                            cout << "Current Array State:" << endl;
                            arrayOpr->traverseArray();

                            //  Perform insertion
                            arrayOpr->insertAt("Inserting element at end.", false,
                                               true);

                            break;
                        }

                        case 'e':
                        {
                            base::hideTextOfScreen();
                            int arr_index;

                            // Get number of elements are in array
                            int element_count = arrayOpr->getArraySize();

                            // Make string with element_count placeholder
                            auto input_ask_text =
                                (ostringstream() << "Enter index between 0 to "
                                                 << element_count << ": ")
                                    .str();

                            // Display array elements
                            cout << "Current Array State: [" << element_count
                                 << "] elements." << endl;
                            arrayOpr->traverseArray();

                            // Get index input from user
                            cout << input_ask_text;
                            base::getIntInput(arr_index, element_count);

                            // Perform insertion
                            arrayOpr->insertAt(
                                "Inserting element at your specified index.",
                                false, false, true, arr_index);

                            break;
                        }

                        default:
                        {  // clear screen for new page after exiting this page
                            base::clearScreen();
                            break;
                        }
                    }
                }
                delete arrayOpr;
                break;
            }
            // if selection_point is [i] just exit program
            default:
            {
                break;
            }
        }
    }
    return 0;
}