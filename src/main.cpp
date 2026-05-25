#include "arrayo.h"
#include "base.h"
#include "home.h"

using namespace home;
using namespace arrayo;

/**
 * In main function handle all menu switching logic
 * as menu option input is just returning after storing user choice in a
 * variable unless invalid input.
 */
int main()
{
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

                            arrayOpr->traverseArray();
                            break;

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