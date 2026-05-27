#include <sstream>

#include "arrayo.h"
#include "base.h"
#include "home.h"
#include "linklist.h"
#include "presskey.h"

using namespace home;
using namespace arrayo;
using namespace lnkls;

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
    LinkList* linkListOpr;

    // Dont exit while user input is not [z]
    while (appHome->selection_point != 'z')
    {
        appHome->startMenu();

        switch (appHome->selection_point)
        {
            // Array Operations
            case 'a':

            {
                arrayOpr = new ArrayO();

                // Dont exit while user input is not [z]
                while (arrayOpr->selection_point != 'z')
                {
                    arrayOpr->startMenu();

                    switch (arrayOpr->selection_point)
                    {
                            // Show Array Operations Menu

                        case 'a':
                        {
                            arrayOpr->createArray();
                            break;
                        }

                            // Traverse stored array elements

                        case 'b':
                        {
                            base::hideTextOfScreen();
                            // Display array elements
                            std::cout << "Displaying stored array elements:"
                                      << std::endl;
                            arrayOpr->traverseArray();
                            presskey::pressAnyKey(
                                "Press any key to return to Array Operations "
                                "menu");
                            break;
                        }

                        // Insert element at begin
                        case 'c':
                        {
                            base::hideTextOfScreen();
                            // Display array elements
                            std::cout << "Current Array State:" << std::endl;
                            arrayOpr->traverseArray();

                            //  Perform insertion
                            arrayOpr->insertAt(
                                "Inserting element at the beginning.", true);

                            break;
                        }

                        // Insert element at end
                        case 'd':
                        {
                            base::hideTextOfScreen();
                            // Display array elements
                            std::cout << "Current Array State:" << std::endl;
                            arrayOpr->traverseArray();

                            //  Perform insertion
                            arrayOpr->insertAt("Inserting element at end.",
                                               false, true);

                            break;
                        }
                        // Insert element at specific index
                        case 'e':
                        {
                            base::hideTextOfScreen();
                            int arr_index;

                            // Get number of elements are in array
                            int element_count = arrayOpr->getArraySize();

                            // Make string with element_count placeholder
                            auto input_ask_text =
                                (std::ostringstream()
                                 << "Enter index between 0 to "
                                 << element_count - 1 << ": ")
                                    .str();

                            // Display array elements
                            std::cout << "Current Array State: ["
                                      << element_count << "] elements."
                                      << std::endl;
                            arrayOpr->traverseArray();

                            // Get index input from user
                            std::cout << input_ask_text;
                            base::getIntInput(arr_index, element_count - 1);

                            // Perform insertion
                            arrayOpr->insertAt(
                                "Inserting element at your specified index.",
                                false, false, true, arr_index);

                            break;
                        }

                        // Delete element from array beginning
                        case 'f':
                        {
                            base::hideTextOfScreen();
                            // Delete from begin
                            arrayOpr->deleteElement(true, false);
                            break;
                        }

                        // Delete element from array end
                        case 'g':
                        {
                            base::hideTextOfScreen();
                            // Delete from end
                            arrayOpr->deleteElement(false);
                            break;
                        }

                        // Delete element at specific index
                        case 'h':
                        {
                            base::hideTextOfScreen();

                            int arr_index;

                            // Get number of elements are in array
                            int element_count = arrayOpr->getArraySize();

                            if (!element_count)
                            {
                                std::cout
                                    << "Cannot perform deletion on empty array!"
                                    << std::endl;
                                base::pauseProgram(2);
                                break;
                            }

                            // Make string with element_count placeholder
                            auto input_ask_text =
                                (std::ostringstream()
                                 << "Enter index between 0 to "
                                 << element_count - 1 << ": ")
                                    .str();

                            // Showing operation title
                            std::cout << "!!!!!! Performing Deletion !!!!!!"
                                      << std::endl;
                            // Display array elements
                            std::cout << "Current Array State: ["
                                      << element_count << "] elements."
                                      << std::endl;
                            arrayOpr->traverseArray();

                            // Get index input from user
                            std::cout << input_ask_text;
                            base::getIntInput(arr_index, element_count - 1);
                            arrayOpr->deleteElement(false, false, true,
                                                    arr_index);

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

            // Linked List Operations
            case 'b':
            {
                linkListOpr = new LinkList();
                // Dont exit while user input is not [z]
                while (linkListOpr->selection_point != 'z')
                {
                    linkListOpr->startMenu();

                    switch (linkListOpr->selection_point)
                    {
                        case 'a':
                        {
                            while (linkListOpr->selected_operation != 'z')
                            {
                                linkListOpr->startOperationsMenu();

                                switch (linkListOpr->selected_operation)
                                {
                                    case 'a':
                                    {
                                        linkListOpr->createSinglyListElement();
                                        break;
                                    }
                                    case 'b':
                                    {
                                        base::hideTextOfScreen();
                                        // Display array elements
                                        std::cout << "Displaying stored Linked "
                                                     "List elements:"
                                                  << std::endl;
                                        linkListOpr->traverseSingly();
                                        presskey::pressAnyKey(
                                            "Press any key to return to "
                                            "Operations Menu ");

                                        break;
                                    }

                                    default:
                                        break;
                                }
                            }
                            break;
                        }

                        default:
                        {  // clear screen for new page after exiting this page
                            base::clearScreen();

                            break;
                        }
                    }
                }
                delete linkListOpr;
                break;
            }
            default:
            {
                break;
            }
        }
    }
    return 0;
}