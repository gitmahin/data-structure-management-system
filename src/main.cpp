#include <functional>
#include <sstream>
#include <type_traits>

#include "arrayo.h"
#include "base.h"
#include "cstack.h"
#include "home.h"
#include "linklist.h"
#include "presskey.h"

using namespace home;
using namespace arrayo;
using namespace lnkls;
using namespace stck;

/**
 * In main function handle all menu switching logic
 * as menu option input is just returning after storing user choice in a
 * variable unless invalid input.
 */
int main()
{
    base::clearScreen();
    bool saveAllOperations = false;

    // You can ask user on application start
    // saveAllOperations =
    //     base::askUser(saveAllOperations, "Do you want to save all tasks
    //     data");

    Home* appHome = new Home();
    ArrayO* arrayOpr = nullptr;
    LinkList* linkListOpr = nullptr;
    Stack* cStack = nullptr;

    // Dont exit while user input is not [z]
    while (appHome->selection_point != 'z')
    {
        // On application start clear screen
        base::clearScreen();
        // reset selection option to null
        appHome->selection_point = '\0';
        appHome->startMenu(saveAllOperations);

        switch (appHome->selection_point)
        {
                // Made this box from ChatGPT :). It looks beautiful, doesn't
                // it?
                // ┌──────────────────────────────────────────────────────────┐
                // │                          ARRAY                           │
                // └──────────────────────────────────────────────────────────┘

            case 'a':

            {
                if (!arrayOpr)
                {
                    arrayOpr = new ArrayO();
                }

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
                            presskey::pressAnyKey("Press any key to back");
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

                            if (element_count < 1)
                            {
                                std::cout
                                    << "Cannot insert into an empty array."
                                    << std::endl;
                                presskey::pressAnyKey("Press any key to back");
                                break;
                            }

                            // Make string with element_count placeholder. (For
                            // demonstration purpose) As you can achive this via
                            // usual cout<<
                            auto input_ask_text =
                                (std::ostringstream()
                                 << "Enter position between 1 to "
                                 << element_count << ": ")
                                    .str();

                            // Display array elements
                            std::cout << "Current Array State: ["
                                      << element_count << "] elements."
                                      << std::endl;
                            arrayOpr->traverseArray();

                            // Get index input from user
                            std::cout << input_ask_text;
                            base::getIntInput(arr_index, element_count, 1);

                            // Perform insertion
                            arrayOpr->insertAt(
                                "Inserting element at your specified position.",
                                false, false, true, arr_index - 1);

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
                                presskey::pressAnyKey("Press any key to back");
                                break;
                            }

                            // Make string with element_count placeholder
                            auto input_ask_text =
                                (std::ostringstream()
                                 << "Enter position between 1 to "
                                 << element_count << ": ")
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
                            base::getIntInput(arr_index, element_count, 1);
                            arrayOpr->deleteElement(false, false, true,
                                                    arr_index - 1);

                            break;
                        }

                        default:
                        {  // clear screen for new page after exiting this page
                            base::clearScreen();

                            break;
                        }
                    }
                }
                arrayOpr->selection_point = '\0';

                if (!saveAllOperations)
                {
                    delete arrayOpr;
                    arrayOpr = nullptr;
                }
                break;
            }

                // ┌──────────────────────────────────────────────────────────┐
                // │                       LINKED LIST                        │
                // └──────────────────────────────────────────────────────────┘

            case 'b':
            {
                if (!linkListOpr)
                {
                    linkListOpr = new LinkList();
                }

                /**
                 * If selection_point != z, Show "Types of Linked List" Menu
                 * if selected z break while loop, Reset all selections under
                 * "Linked List" and exit to Application Menu else Enter to the
                 * "Operations Menu" -> startOperationsMenu() if press m, exit
                 * from "Operations Menu" Menu, It will then check if m was
                 * pressed, if then exit from "Types of Linked List" Mwnu clear
                 * all selections under "Linked List" and back to Application
                 * Menu
                 */

                // Don't exit while user input is not [z]
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

                    // Set selection_point
                    base::clearScreen();
                    base::showAppTitle("Linked List");
                    linkListOpr->startMenu();

                    // resetting selected_operation menu selection
                    // so that it doesn't create infinite loop to stuck in
                    // startMenu();
                    linkListOpr->selected_operation = '\0';

                    switch (linkListOpr->selection_point)
                    {
                        // Singly Linked List Management
                        case 'a':
                        {
                            // Reset selections while Singly, Circular and
                            // Doubly is using this same selections
                            linkListOpr->selected_operation = '\0';

                            // reset selected_operation to the null terminator
                            // before reopening
                            // linkListOpr->startMenu(). Otherwise, the previous
                            // 'z' selection remains stored and causes the menu
                            // to enter an infinite loop.
                            while (linkListOpr->selected_operation != 'z' &&
                                   linkListOpr->selected_operation != 'm')
                            {
                                // Set selected_operation
                                base::clearScreen();
                                base::showAppTitle("Linked List / Singly");
                                linkListOpr->startOperationsMenu();

                                switch (linkListOpr->selected_operation)
                                {
                                    // Start Singly Linked List creation
                                    case 'a':
                                    {
                                        // std::placeholder Reference:
                                        // https://en.cppreference.com/cpp/utility/functional/placeholders
                                        linkListOpr->createLinkedListElement(
                                            linkListOpr->singlyHead,
                                            std::bind(
                                                &LinkList::getSinglyListSize,
                                                linkListOpr),
                                            std::bind(
                                                &LinkList::deleteSinglyAtEnd,
                                                linkListOpr,
                                                std::placeholders::_1),
                                            std::bind(
                                                &LinkList::insertSinglyAtEnd,
                                                linkListOpr,
                                                std::placeholders::_1)

                                        );
                                        break;
                                    }
                                    // Traverse Singly Linked List
                                    case 'b':
                                    {
                                        base::hideTextOfScreen();

                                        int element_count =
                                            linkListOpr->getSinglyListSize();

                                        if (!element_count)
                                        {
                                            std::cout
                                                << "No list elements to show!"
                                                << std::endl;
                                        }
                                        else
                                        {
                                            // Display list elements
                                            std::cout << "Displaying stored "
                                                         "Singly Linked "
                                                         "List elements:"
                                                      << std::endl;
                                            linkListOpr->traverseSingly();
                                        }
                                        presskey::pressAnyKey(
                                            "Press any key to back");

                                        break;
                                    }

                                    // Insert at begin [Singly Linked List]
                                    case 'c':
                                    {
                                        base::hideTextOfScreen();

                                        if (!linkListOpr->singlyHead)
                                        {
                                            std::cout
                                                << "Cannot perform insertion "
                                                   "on empty Linked List!"
                                                << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }

                                        std::cout << "Current Linked List State"
                                                  << std::endl;
                                        linkListOpr->traverseSingly();

                                        std::cout
                                            << std::endl
                                            << "Inserting Element At Begin."
                                            << std::endl;
                                        base::VariantSupportedDataType input =
                                            linkListOpr->createLinkedListInput(
                                                linkListOpr->singlyHead, 0);
                                        linkListOpr->insertSinglyAtStart(input);
                                        std::cout
                                            << "Element inserted successfully."
                                            << std::endl;
                                        base::pauseProgram(1);
                                        break;
                                    }

                                    // Insert at end [Singly Linked List]
                                    case 'd':
                                    {
                                        base::hideTextOfScreen();

                                        if (!linkListOpr->singlyHead)
                                        {
                                            std::cout
                                                << "Cannot perform insertion "
                                                   "on empty Linked List!"
                                                << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }

                                        std::cout << "Current Linked List State"
                                                  << std::endl;
                                        linkListOpr->traverseSingly();

                                        std::cout << std::endl
                                                  << "Inserting Element At End."
                                                  << std::endl;
                                        base::VariantSupportedDataType input =
                                            linkListOpr->createLinkedListInput(
                                                linkListOpr->singlyHead, 0);
                                        linkListOpr->insertSinglyAtEnd(input);
                                        std::cout
                                            << "Element inserted successfully."
                                            << std::endl;
                                        base::pauseProgram(1);
                                        break;
                                    }

                                    // Insert at index [Singly Linked List]
                                    case 'e':
                                    {
                                        base::hideTextOfScreen();
                                        if (!linkListOpr->singlyHead)
                                        {
                                            std::cout
                                                << "Cannot perform insertion "
                                                   "on empty Linked List!"
                                                << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }
                                        int elements_count =
                                            linkListOpr->getSinglyListSize();

                                        std::cout
                                            << "Current Linked List State: ["
                                            << elements_count << "] elements."
                                            << std::endl;
                                        linkListOpr->traverseSingly();

                                        std::cout
                                            << std::endl
                                            << "Inserting element by position."
                                            << std::endl;

                                        std::cout
                                            << "Enter position between 1 to "
                                            << elements_count << ": ";
                                        int index = 0;
                                        base::getIntInput(index, elements_count,
                                                          1);

                                        base::VariantSupportedDataType input =
                                            linkListOpr->createLinkedListInput(
                                                linkListOpr->singlyHead, 0);
                                        linkListOpr->insertSinglyAtIndex(
                                            input, index - 1);
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
                                        if (!linkListOpr->singlyHead)
                                        {
                                            std::cout << "Cannot delete from "
                                                         "empty Linked List!"
                                                      << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }
                                        linkListOpr->deleteSinglyAtStart();
                                        presskey::pressAnyKey(
                                            "Press any key to back");

                                        break;
                                    }

                                    // Delete element at end
                                    case 'g':
                                    {
                                        base::hideTextOfScreen();
                                        if (!linkListOpr->singlyHead)
                                        {
                                            std::cout << "Cannot delete from "
                                                         "empty Linked List!"
                                                      << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }
                                        linkListOpr->deleteSinglyAtEnd();
                                        presskey::pressAnyKey(
                                            "Press any key to back");
                                        break;
                                    }

                                    // Delete element by index
                                    case 'h':
                                    {
                                        base::hideTextOfScreen();

                                        if (!linkListOpr->singlyHead)
                                        {
                                            std::cout << "Cannot delete from "
                                                         "empty Linked List!"
                                                      << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }
                                        std::cout << "!!!!!! Performing "
                                                     "Deletion !!!!!!"
                                                  << std::endl;
                                        int elements_count =
                                            linkListOpr->getSinglyListSize();
                                        std::cout
                                            << "Current Linked List State: ["
                                            << elements_count << "] elements."
                                            << std::endl;
                                        linkListOpr->traverseSingly();

                                        std::cout
                                            << "Enter position between 1 to "
                                            << elements_count << ": ";
                                        int index = 0;
                                        base::getIntInput(index, elements_count,
                                                          1);
                                        linkListOpr->deleteSinglyAtIndex(index -
                                                                         1);
                                        presskey::pressAnyKey(
                                            "Press any key to back");

                                        break;
                                    }

                                    default:
                                        break;
                                }
                            }

                            if (!saveAllOperations)
                            {
                                linkListOpr->clearAll(
                                    std::bind(&LinkList::getSinglyListSize,
                                              linkListOpr),
                                    std::bind(&LinkList::deleteSinglyAtEnd,
                                              linkListOpr,
                                              std::placeholders::_1));
                            }
                            break;
                        }

                        // Circular Linked List Management
                        case 'b':
                        {
                            // Reset selections while Singly, Circular and
                            // Doubly is using this same selections
                            linkListOpr->selected_operation = '\0';

                            while (linkListOpr->selected_operation != 'z' &&
                                   linkListOpr->selected_operation != 'm')
                            {
                                // Set selected_operation
                                base::clearScreen();
                                base::showAppTitle("Linked List / Circular");
                                linkListOpr->startOperationsMenu();
                                switch (linkListOpr->selected_operation)
                                {
                                    // Start Circular Linked List creation
                                    case 'a':
                                    {
                                        // std::placeholder Reference:
                                        // https://en.cppreference.com/cpp/utility/functional/placeholders
                                        linkListOpr->createLinkedListElement(
                                            linkListOpr->circularHead,
                                            std::bind(
                                                &LinkList::getCircularListSize,
                                                linkListOpr),
                                            std::bind(
                                                &LinkList::deleteCircularAtEnd,
                                                linkListOpr,
                                                std::placeholders::_1),
                                            std::bind(
                                                &LinkList::insertCircularAtEnd,
                                                linkListOpr,
                                                std::placeholders::_1)

                                        );
                                        break;
                                    }
                                    // Traverse Circular Linked List
                                    case 'b':
                                    {
                                        base::hideTextOfScreen();

                                        int element_count =
                                            linkListOpr->getCircularListSize();

                                        if (!element_count)
                                        {
                                            std::cout << "No list elements to "
                                                         "show!"
                                                      << std::endl;
                                        }
                                        else
                                        {
                                            // Display list elements
                                            std::cout << "Displaying stored "
                                                         "Circular Linked "
                                                         "List elements:"
                                                      << std::endl;
                                            linkListOpr->traverseCircular();
                                        }
                                        presskey::pressAnyKey(
                                            "Press any key to back");

                                        break;
                                    }

                                    // Insert at begin [Circular Linked
                                    // List]
                                    case 'c':
                                    {
                                        base::hideTextOfScreen();

                                        if (!linkListOpr->circularHead)
                                        {
                                            std::cout << "Cannot perform "
                                                         "insertion "
                                                         "on empty Linked List!"
                                                      << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }

                                        std::cout << "Current Linked List "
                                                     "State"
                                                  << std::endl;
                                        linkListOpr->traverseCircular();

                                        std::cout << std::endl
                                                  << "Inserting Element At "
                                                     "Begin."
                                                  << std::endl;
                                        base::VariantSupportedDataType input =
                                            linkListOpr->createLinkedListInput(
                                                linkListOpr->circularHead, 0);
                                        linkListOpr->insertCircularAtStart(
                                            input);
                                        std::cout << "Element inserted "
                                                     "successfully."
                                                  << std::endl;
                                        base::pauseProgram(1);
                                        break;
                                    }

                                    // Insert at end [Circular Linked List]
                                    case 'd':
                                    {
                                        base::hideTextOfScreen();

                                        if (!linkListOpr->circularHead)
                                        {
                                            std::cout << "Cannot perform "
                                                         "insertion "
                                                         "on empty Linked List!"
                                                      << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }

                                        std::cout << "Current Linked List "
                                                     "State"
                                                  << std::endl;
                                        linkListOpr->traverseCircular();

                                        std::cout << std::endl
                                                  << "Inserting Element "
                                                     "At End."
                                                  << std::endl;
                                        base::VariantSupportedDataType input =
                                            linkListOpr->createLinkedListInput(
                                                linkListOpr->circularHead, 0);
                                        linkListOpr->insertCircularAtEnd(input);
                                        std::cout << "Element inserted "
                                                     "successfully."
                                                  << std::endl;
                                        base::pauseProgram(1);
                                        break;
                                    }

                                    // Insert at index [Circular Linked
                                    // List]
                                    case 'e':
                                    {
                                        base::hideTextOfScreen();
                                        if (!linkListOpr->circularHead)
                                        {
                                            std::cout << "Cannot perform "
                                                         "insertion "
                                                         "on empty Linked List!"
                                                      << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }
                                        int elements_count =
                                            linkListOpr->getCircularListSize();

                                        std::cout << "Current Linked List "

                                                     "State: ["
                                                  << elements_count
                                                  << "] "
                                                     "elements."
                                                  << std::endl;
                                        linkListOpr->traverseCircular();

                                        std::cout
                                            << std::endl
                                            << "Inserting element by position."

                                            << std::endl;

                                        std::cout << "Enter position between "
                                                     "1 to "
                                                  << elements_count << ": ";
                                        int index = 0;
                                        base::getIntInput(index, elements_count,
                                                          1);

                                        base::VariantSupportedDataType input =
                                            linkListOpr->createLinkedListInput(
                                                linkListOpr->circularHead, 0);
                                        linkListOpr->insertCircularAtIndex(
                                            input, index - 1);
                                        std::cout << "Element inserted "
                                                     "successfully."
                                                  << std::endl;
                                        base::pauseProgram(1);
                                        break;
                                    }

                                    // Delete element at begin [Circular
                                    // Linked List]
                                    case 'f':
                                    {
                                        base::hideTextOfScreen();
                                        if (!linkListOpr->circularHead)
                                        {
                                            std::cout << "Cannot delete from "
                                                         "empty Linked List!"
                                                      << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }
                                        linkListOpr->deleteCircularAtStart();
                                        presskey::pressAnyKey(
                                            "Press any key to back");

                                        break;
                                    }

                                    // Delete element at end [Circular
                                    // Linked List]
                                    case 'g':
                                    {
                                        base::hideTextOfScreen();
                                        if (!linkListOpr->circularHead)
                                        {
                                            std::cout << "Cannot delete from "
                                                         "empty Linked List!"
                                                      << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }
                                        linkListOpr->deleteCircularAtEnd();
                                        presskey::pressAnyKey(
                                            "Press any key to back");
                                        break;
                                    }

                                    // Delete element by index [Circular Linked
                                    // List]
                                    case 'h':
                                    {
                                        base::hideTextOfScreen();

                                        if (!linkListOpr->circularHead)
                                        {
                                            std::cout << "Cannot delete from "
                                                         "empty Linked List!"
                                                      << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }
                                        std::cout << "!!!!!! Performing "
                                                     "Deletion !!!!!!"
                                                  << std::endl;
                                        int elements_count =
                                            linkListOpr->getCircularListSize();
                                        std::cout
                                            << "Current Linked List State: ["
                                            << elements_count << "] elements."
                                            << std::endl;
                                        linkListOpr->traverseCircular();

                                        std::cout
                                            << "Enter position between 1 to "
                                            << elements_count << ": ";
                                        int index = 0;
                                        base::getIntInput(index, elements_count,
                                                          1);
                                        linkListOpr->deleteCircularAtIndex(
                                            index - 1);
                                        presskey::pressAnyKey(
                                            "Press any key to back");

                                        break;
                                    }

                                    default:
                                        break;
                                }
                            }

                            if (!saveAllOperations)
                            {
                                linkListOpr->clearAll(
                                    std::bind(&LinkList::getCircularListSize,
                                              linkListOpr),
                                    std::bind(&LinkList::deleteCircularAtEnd,
                                              linkListOpr,
                                              std::placeholders::_1));
                            }
                            break;
                        }

                        // Doubly Linked List
                        case 'c':
                        {
                            // Reset selections while Singly, Circular and
                            // Doubly is using this same selections
                            linkListOpr->selected_operation = '\0';

                            while (linkListOpr->selected_operation != 'z' &&
                                   linkListOpr->selected_operation != 'm')
                            {
                                // Set selected_operation
                                base::clearScreen();
                                base::showAppTitle("Linked List / Doubly");
                                linkListOpr->startOperationsMenu();
                                switch (linkListOpr->selected_operation)
                                {
                                    // Start Circular Linked List creation
                                    case 'a':
                                    {
                                        // std::placeholder Reference:
                                        // https://en.cppreference.com/cpp/utility/functional/placeholders
                                        linkListOpr->createLinkedListElement(
                                            linkListOpr->doublyHead,
                                            std::bind(
                                                &LinkList::getDoublyListSize,
                                                linkListOpr),
                                            std::bind(
                                                &LinkList::deleteDoublyAtEnd,
                                                linkListOpr,
                                                std::placeholders::_1),
                                            std::bind(
                                                &LinkList::insertDoublyAtEnd,
                                                linkListOpr,
                                                std::placeholders::_1)

                                        );
                                        break;
                                    }
                                    // Traverse Doubly Linked List
                                    case 'b':
                                    {
                                        base::hideTextOfScreen();

                                        int element_count =
                                            linkListOpr->getDoublyListSize();

                                        if (!element_count)
                                        {
                                            std::cout << "No list elements to "
                                                         "show!"
                                                      << std::endl;
                                        }
                                        else
                                        {
                                            // Display list elements
                                            std::cout << "Displaying stored "
                                                         "Doubly Linked "
                                                         "List elements:"
                                                      << std::endl;
                                            linkListOpr->traverseDoubly();
                                        }
                                        presskey::pressAnyKey(
                                            "Press any key to back");

                                        break;
                                    }

                                    // Insert at begin [Doubly Linked
                                    // List]
                                    case 'c':
                                    {
                                        base::hideTextOfScreen();

                                        if (!linkListOpr->doublyHead)
                                        {
                                            std::cout << "Cannot perform "
                                                         "insertion "
                                                         "on empty Linked List!"
                                                      << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }

                                        std::cout << "Current Linked List "
                                                     "State"
                                                  << std::endl;
                                        linkListOpr->traverseDoubly();

                                        std::cout << std::endl
                                                  << "Inserting Element At "
                                                     "Begin."
                                                  << std::endl;
                                        base::VariantSupportedDataType input =
                                            linkListOpr->createLinkedListInput(
                                                linkListOpr->doublyHead, 0);
                                        linkListOpr->insertDoublyAtStart(input);
                                        std::cout << "Element inserted "
                                                     "successfully."
                                                  << std::endl;
                                        base::pauseProgram(1);
                                        break;
                                    }

                                    // Insert at end [Doubly Linked List]
                                    case 'd':
                                    {
                                        base::hideTextOfScreen();

                                        if (!linkListOpr->doublyHead)
                                        {
                                            std::cout << "Cannot perform "
                                                         "insertion "
                                                         "on empty Linked List!"
                                                      << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }

                                        std::cout << "Current Linked List "

                                                     "State"
                                                  << std::endl;
                                        linkListOpr->traverseDoubly();

                                        std::cout << std::endl
                                                  << "Inserting Element "

                                                     "At End."
                                                  << std::endl;
                                        base::VariantSupportedDataType input =
                                            linkListOpr->createLinkedListInput(
                                                linkListOpr->doublyHead, 0);
                                        linkListOpr->insertDoublyAtEnd(input);
                                        std::cout << "Element inserted "
                                                     "successfully."
                                                  << std::endl;
                                        base::pauseProgram(1);
                                        break;
                                    }

                                    // Insert at index [Doubly Linked
                                    // List]
                                    case 'e':
                                    {
                                        base::hideTextOfScreen();
                                        if (!linkListOpr->doublyHead)
                                        {
                                            std::cout << "Cannot perform "
                                                         "insertion "
                                                         "on empty Linked List!"
                                                      << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }
                                        int elements_count =
                                            linkListOpr->getDoublyListSize();

                                        std::cout << "Current Linked List "

                                                     "State: ["
                                                  << elements_count
                                                  << "] "
                                                     "elements."
                                                  << std::endl;
                                        linkListOpr->traverseDoubly();

                                        std::cout
                                            << std::endl
                                            << "Inserting element by position."

                                            << std::endl;

                                        std::cout << "Enter position between "
                                                     "1 to "
                                                  << elements_count << ": ";
                                        int index = 0;
                                        base::getIntInput(index, elements_count,
                                                          1);

                                        base::VariantSupportedDataType input =
                                            linkListOpr->createLinkedListInput(
                                                linkListOpr->doublyHead, 0);
                                        linkListOpr->insertDoublyAtIndex(
                                            input, index - 1);
                                        std::cout << "Element inserted "
                                                     "successfully."
                                                  << std::endl;
                                        base::pauseProgram(1);
                                        break;
                                    }

                                    // Delete element at begin [Doubly
                                    // Linked List]
                                    case 'f':
                                    {
                                        base::hideTextOfScreen();
                                        if (!linkListOpr->doublyHead)
                                        {
                                            std::cout << "Cannot delete from "
                                                         "empty Linked List!"
                                                      << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }
                                        linkListOpr->deleteDoublyAtStart();
                                        presskey::pressAnyKey(
                                            "Press any key to back");

                                        break;
                                    }

                                    // Delete element at end [Doubly
                                    // Linked List]
                                    case 'g':
                                    {
                                        base::hideTextOfScreen();
                                        if (!linkListOpr->doublyHead)
                                        {
                                            std::cout << "Cannot delete from "
                                                         "empty Linked List!"
                                                      << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }
                                        linkListOpr->deleteDoublyAtEnd();
                                        presskey::pressAnyKey(
                                            "Press any key to back");
                                        break;
                                    }

                                    // Delete element by index [Doubly Linked
                                    // List]
                                    case 'h':
                                    {
                                        base::hideTextOfScreen();

                                        if (!linkListOpr->doublyHead)
                                        {
                                            std::cout << "Cannot delete from "
                                                         "empty Linked List!"
                                                      << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }
                                        std::cout << "!!!!!! Performing "
                                                     "Deletion !!!!!!"
                                                  << std::endl;
                                        int elements_count =
                                            linkListOpr->getDoublyListSize();
                                        std::cout
                                            << "Current Linked List State: ["
                                            << elements_count << "] elements."
                                            << std::endl;
                                        linkListOpr->traverseDoubly();

                                        std::cout
                                            << "Enter position between 1 to "
                                            << elements_count << ": ";
                                        int index = 0;
                                        base::getIntInput(index, elements_count,
                                                          1);
                                        linkListOpr->deleteDoublyAtIndex(index -
                                                                         1);
                                        presskey::pressAnyKey(
                                            "Press any key to back");

                                        break;
                                    }

                                    default:
                                        break;
                                }
                            }

                            if (!saveAllOperations)
                            {
                                linkListOpr->clearAll(
                                    std::bind(&LinkList::getDoublyListSize,
                                              linkListOpr),
                                    std::bind(&LinkList::deleteDoublyAtEnd,
                                              linkListOpr,
                                              std::placeholders::_1));
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

                linkListOpr->selection_point = '\0';
                linkListOpr->selected_operation = '\0';
                if (!saveAllOperations)
                {
                    delete linkListOpr;
                    // Set to nullptr otherwise if(!linkListOpr) will false and
                    // instance of new LinkList() will not create if not create
                    // it will throw Segfault error
                    linkListOpr = nullptr;
                }
                break;
            }

                // ┌──────────────────────────────────────────────────────────┐
                // │                          Stack                           │
                // └──────────────────────────────────────────────────────────┘
            case 'c':
            {
                if (!cStack)
                {
                    cStack = new Stack();
                }

                while (cStack->selection_point != 'z')
                {
                    if (cStack->selected_operation == 'm')
                    {
                        break;
                    }

                    base::clearScreen();
                    base::showAppTitle("Stack");
                    cStack->startMenu();

                    cStack->selected_operation = '\0';

                    switch (cStack->selection_point)
                    {
                        case 'a':
                        {
                            // Reset selected_operation while case a and b is
                            // using this same variable for selecting any
                            // operation
                            cStack->selected_operation = '\0';

                            while (cStack->selected_operation != 'z' &&
                                   cStack->selected_operation != 'm')
                            {
                                cStack->selected_operation = '\0';
                                base::clearScreen();
                                base::showAppTitle("Stack / Using Array");
                                cStack->startOperationsMenu();

                                switch (cStack->selected_operation)
                                {
                                    case 'a':
                                    {
                                        cStack->createStackArray();
                                        break;
                                    }
                                    case 'b':
                                    {
                                        base::hideTextOfScreen();

                                        if (!cStack->stackArray)
                                        {
                                            std::cout
                                                << "Stack not created yet! "
                                                   "Cannot push element!"
                                                << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }

                                        cStack->showStackArrayStatus();

                                        cStack->displayStackArray();

                                        if ((cStack->stackArray->size -
                                             (cStack->stackArray->top + 1)) ==
                                            0)
                                        {
                                            std::cout
                                                << "\nStack is full. Pop "
                                                   "elements before pushing."
                                                << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }

                                        std::cout
                                            << "\nPushing element to the Stack."
                                            << std::endl;
                                        cStack->handleSinglePushStackArray();
                                        base::pauseProgram(1);
                                        break;
                                    }
                                    case 'c':
                                    {
                                        base::hideTextOfScreen();

                                        if (cStack->isEmptyStackArray())
                                        {
                                            std::cout << "Stack Empty! Cannot "
                                                         "pop element!"
                                                      << std::endl;
                                            presskey::pressAnyKey(
                                                "Press any key to back");
                                            break;
                                        }

                                        base::VariantSupportedDataType popped =
                                            cStack->popArray();
                                        std::cout << "Popped [";
                                        base::logVariantData(popped);
                                        std::cout << "] from the Stack."
                                                  << std::endl;
                                        presskey::pressAnyKey(
                                            "Press any key to back");
                                        break;
                                    }
                                    case 'd':
                                    {
                                        break;
                                    }
                                    case 'e':
                                    {
                                        base::hideTextOfScreen();
                                        std::cout << "Displaying Stack"
                                                  << std::endl;
                                        cStack->displayStackArray();
                                        presskey::pressAnyKey(
                                            "Press any key to back");

                                        break;
                                    }

                                    default:
                                        break;
                                }
                            }

                            if (!saveAllOperations)
                            {
                                cStack->deleteStackArray();
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

                cStack->selection_point = '\0';
                cStack->selected_operation = '\0';

                if (!saveAllOperations)
                {
                    delete cStack;
                    // Set to nullptr otherwise if(!cStack) will false and
                    // instance of new cStack() will not create if not create
                    // it will throw Segfault error
                    cStack = nullptr;
                }
                break;
            }

            case 's':
            {
                saveAllOperations = true;
                break;
            }

            case 'u':
            {
                delete arrayOpr;
                delete linkListOpr;
                delete cStack;

                arrayOpr = nullptr;
                linkListOpr = nullptr;
                cStack = nullptr;

                // Reset
                saveAllOperations = false;
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