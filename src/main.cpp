#include <sstream>
#include <type_traits>

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
        // On application start clear screen
        base::clearScreen();
        // reset selection option to null
        appHome->selection_point = '\0';
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

                            // Make string with element_count placeholder. (For
                            // demonstration purpose) As you can achive this via
                            // usual cout<<
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
                    /**
                     * Back to Main menu
                     *
                     * if user choose selected_operation = m
                     * it will break the selected_operation loop
                     * and after re-entering in selection_point loop
                     * it will check at first that before re-entering
                     * selection_point if selected_operation has selected m.
                     *
                     * NOTE: don't reset selected_operation before doing this
                     */
                    if (linkListOpr->selected_operation == 'm')
                    {
                        break;
                    }

                    // reset selection option
                    linkListOpr->selection_point = '\0';
                    linkListOpr->startMenu();

                    // resetting selected_operation menu selection
                    // so that it doesn't create infinite loop to stuck in
                    // startMenu();
                    linkListOpr->selected_operation = '\0';

                    switch (linkListOpr->selection_point)
                    {
                        case 'a':
                        {
                            // reset selected_operation to the null terminator
                            // before reopening
                            // linkListOpr->startMenu(). Otherwise, the previous
                            // 'z' selection remains stored and causes the menu
                            // to enter an infinite loop.
                            while (linkListOpr->selected_operation != 'z' &&
                                   linkListOpr->selected_operation != 'm')
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
                                            "Press any key to return to the "
                                            "Linked List Operations menu");

                                        break;
                                    }

                                    // Insert at begin
                                    case 'c':
                                    {
                                        base::hideTextOfScreen();
                                        std::cout << "Current Linked List State"
                                                  << std::endl;
                                        linkListOpr->traverseSingly();

                                        std::cout
                                            << std::endl
                                            << "Inserting Element At Begin."
                                            << std::endl;
                                        base::VariantSupportedDataType input =
                                            linkListOpr->createSinglyInput(0);
                                        linkListOpr->insertSinglyAtStart(input);
                                        std::cout
                                            << "Element inserted successfully."
                                            << std::endl;
                                        base::pauseProgram(1);
                                        break;
                                    }

                                    // Insert at end
                                    case 'd':
                                    {
                                        base::hideTextOfScreen();
                                        std::cout << "Current Linked List State"
                                                  << std::endl;
                                        linkListOpr->traverseSingly();

                                        std::cout << std::endl
                                                  << "Inserting Element At End."
                                                  << std::endl;
                                        base::VariantSupportedDataType input =
                                            linkListOpr->createSinglyInput(0);
                                        linkListOpr->insertSinglyAtEnd(input);
                                        std::cout
                                            << "Element inserted successfully."
                                            << std::endl;
                                        base::pauseProgram(1);
                                        break;
                                    }

                                    // Insert at index
                                    case 'e':
                                    {
                                        base::hideTextOfScreen();
                                        int elements_count =
                                            linkListOpr->getSinglyListSize();
                                        std::cout
                                            << "Current Linked List State: ["
                                            << elements_count << "] elements."
                                            << std::endl;
                                        linkListOpr->traverseSingly();

                                        std::cout
                                            << std::endl
                                            << "Inserting Element At Index."
                                            << std::endl;

                                        std::cout << "Enter index between 0 to "
                                                  << elements_count - 1 << ": ";
                                        int index = 0;
                                        base::getIntInput(index,
                                                          elements_count - 1);

                                        base::VariantSupportedDataType input =
                                            linkListOpr->createSinglyInput(0);
                                        linkListOpr->insertSinglyAtIndex(input,
                                                                         index);
                                        std::cout
                                            << "Element inserted successfully."
                                            << std::endl;
                                        base::pauseProgram(1);
                                        break;
                                    }

                                    // Delete element at begin
                                    case 'f':
                                    {
                                        base::hideTextOfScreen();
                                        linkListOpr->deleteSinglyAtStart();
                                        presskey::pressAnyKey(
                                            "Press any key to return to the "
                                            "Linked List Operations menu");

                                        break;
                                    }

                                    case 'g':
                                    {
                                        base::hideTextOfScreen();
                                        linkListOpr->deleteSinglyAtEnd();
                                        presskey::pressAnyKey(
                                            "Press any key to return to the "
                                            "Linked List Operations menu");
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