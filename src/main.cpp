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

    // Dont exit while user input is not [i]
    while (appHome->selection_point != 'i')
    {
        appHome->startMenu();

        switch (appHome->selection_point)
        {
            case 'a':

                arrayOpr = new ArrayO();

                // Dont exit while user input is not [i]
                while (arrayOpr->selection_point != 'i')
                {
                    arrayOpr->startMenu();

                    switch (arrayOpr->selection_point)
                    {
                        case 'a':

                            arrayOpr->createArray();
                            break;
                        case 'b':
                            base::hideTextOfScreen();
                            cout << "Displaying stored array elements:" << endl;
                            arrayOpr->traverseArray();
                            presskey::pressAnyKey(
                                "Press any key to return to Array operation "
                                "menu");
                            break;
                        case 'c':
                            base::hideTextOfScreen();
                            arrayOpr->insertAt(
                                "Inserting array at the beginning.", true);

                            break;
                        case 'd':
                            base::hideTextOfScreen();
                            arrayOpr->insertAt("Inserting array at end.", false,
                                               true);

                            break;
                            // TODO: Add stored array element count then show
                            // input to user. case 'e':
                            //     base::hideTextOfScreen();
                            //     arrayOpr->insertAt(
                            //         "Inserting array at any position.",
                            //         false, false, true);

                            //     break;

                        default:
                            // clear screen for new page after exiting this page
                            base::clearScreen();
                            break;
                    }
                }
                delete arrayOpr;
                break;

            // if selection_point is [i] just exit program
            default:
                break;
        }
    }
    return 0;
}