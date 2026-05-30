#include "linklist.h"

#include <functional>
#include <sstream>
#include <string>
#include <type_traits>
#include <variant>

#include "menu.h"

namespace lnkls
{

    void LinkList::startMenu()
    {
        // Clear home page for new page
        base::clearScreen();

        base::showAppTitle("Linked List");

        std::cout << "========================================\n";
        std::cout << "|         Type of Linked List          |\n";
        std::cout << "========================================\n";
        std::cout << "| a -> Singly Linked List              |\n";
        std::cout << "| b -> Circular Linked List            |\n";
        std::cout << "| c -> Doubly Linked List              |\n";
        std::cout << "========================================\n";
        std::cout << "| z -> Main Menu                       |\n";
        std::cout << "========================================\n";
        std::cout << "Choose linked list type: ";

        menu::getMenuSelection(this->selection_point, lnkls::sub_menu_options,
                               "Linked List data type", false);
    }

    void LinkList::startOperationsMenu()
    {
        // Clear home page for new page
        base::clearScreen();

        base::showAppTitle("Linked List");

        std::cout << "========================================\n";
        std::cout << "|            Operations Menu           |\n";
        std::cout << "========================================\n";
        std::cout << "| a -> Create List                     |\n";
        std::cout << "| b -> Traverse List                   |\n";
        std::cout << "| c -> Insert at Beginning             |\n";
        std::cout << "| d -> Insert at End                   |\n";
        std::cout << "| e -> Insert at Any Position          |\n";
        std::cout << "| f -> Delete from Beginning           |\n";
        std::cout << "| g -> Delete from End                 |\n";
        std::cout << "| h -> Delete from Any Position        |\n";
        std::cout << "========================================\n";
        std::cout << "| z -> Back                            |\n";
        std::cout << "| m -> Main Menu                       |\n";
        std::cout << "========================================\n";
        std::cout << "Choose an operation: ";

        menu::getMenuSelection(this->selected_operation,
                               lnkls::operation_options,
                               "Linked List operations", false);
    }

    template <LinkedListNodeType T>
    base::VariantSupportedDataType LinkList::createLinkedListInput(
        T*& node, int i, bool showIndex)
    {
        if (!node) node = new T;
        base::VariantSupportedDataType result;

        std::visit(
            // here element is just for matching type
            [&](auto element)
            {
                typename std::decay_t<decltype(element)> data;

                while (true)
                {
                    if (showIndex)
                    {
                        std::cout << "Enter element ["
                                  << base::type_name<decltype(data)>() << "]["
                                  << i << "]: ";
                    }
                    else
                    {
                        std::cout << "Enter element ["
                                  << base::type_name<decltype(data)>() << "]: ";
                    }
                    if constexpr (std::is_same_v<
                                      std::decay_t<decltype(element)>,
                                      std::string>)
                    {
                        getline(std::cin, data);
                        break;
                    }
                    else
                    {
                        std::cin >> data;

                        if (std::cin.fail())
                        {
                            std::cin.clear();
                            // while (std::cin.get() != '\n');  //
                            // flush bad inputs
                            std::cout << "Invalid input! Try again."
                                      << std::endl;
                            continue;
                        }

                        // while (std::cin.get() != '\n');
                        break;
                    }
                };
                result = data;
            },
            // data is a std::variant
            node->data);

        return result;
    }


    

    // ************************************************************************
    // Singly Linked List
    // ************************************************************************

    /**
     * Initializes a new Singly Linked List by prompting the user for data type
     * and size.
     *
     * If a list already exists, it clears all existing nodes before starting.
     * The method guides the user through:
     * 1. Selecting a supported data type (int, double, string, char).
     * 2. Specifying the initial number of elements.
     * 3. Entering values for each node in the list.
     *
     * @code
     *  linkListOpr->createSinglyListElement();
     * @endcode
     *
     * @note Maximum initial size is capped at 100 elements via getIntInput.
     */
    void LinkList::createSinglyListElement()
    {
        if (this->singlyHead)

        {
            int element_count = this->getSinglyListSize();
            for (int i = 0; i < element_count; i++)
            {
                this->deleteSinglyAtEnd(false);
            }
        }

        this->singlyHead = new Singly;

        this->singlyHead->next = nullptr;

        int i = 0;

        base::hideTextOfScreen();
        base::showAvailableDataTypesMenu();
        this->selected_data_type = '\0';
        menu::getMenuSelection(this->selected_data_type,
                               base::data_type_options, "Data Types", false);

        switch (this->selected_data_type)
        {
            case 'a':
            {
                this->singlyHead->data = int();
                break;
            }
            case 'b':
            {
                this->singlyHead->data = double();
                break;
            }
            case 'c':
            {
                this->singlyHead->data = std::string();
                break;
            }
            case 'd':
            {
                this->singlyHead->data = char();
                break;
            }

            case 'z':
                // back to linked list operations page
                base::clearScreen();
                return;
            default:
                return;
        }

        base::hideTextOfScreen();
        int initial_elements_count = 1;
        std::cout
            << "Enter the number of elements to create in the linked list: ";
        base::getIntInput(initial_elements_count, 100);

        // Create head data with specific Singly struct type first
        base::VariantSupportedDataType first_data =
            this->createLinkedListInput(this->singlyHead, 0, true);
        this->singlyHead->data = first_data;

        // Start index from one while head is created
        for (int i = 1; i < initial_elements_count; i++)
        {
            base::VariantSupportedDataType data =
                this->createLinkedListInput(this->singlyHead, i, true);

            this->insertSinglyAtEnd(data);
        }
    }

    /**
     * Iterates through the Singly Linked List and prints each element's data.
     * Uses std::visit to handle the variant data type stored in each node.
     * Displays "Empty Elements" if the list head is null.
     */
    void LinkList::traverseSingly()
    {
        if (!this->singlyHead) std::cout << "Empty Elements" << std::endl;
        Singly* ptr = this->singlyHead;
        while (ptr != nullptr)
        {
            std::visit([](auto& element) { std::cout << element << std::endl; },
                       ptr->data);
            ptr = ptr->next;
        }
    }

    /**
     * Calculates the total number of nodes currently in the Singly Linked List.
     *
     * Iterates through the list starting from the head until the end is
     * reached.
     * @return The integer count of elements in the list.
     *
     * @code
     *  int size = linkListOpr->getSinglyListSize();
     * @endcode
     */
    int LinkList::getSinglyListSize()
    {
        int i = 0;
        Singly* ptr = this->singlyHead;
        while (ptr != nullptr)
        {
            ptr = ptr->next;
            i++;
        }

        return i;
    }

    /**
     * Inserts a new node at the beginning of the Singly Linked List.
     *
     * Creates a new node with the provided data and updates the head pointer.
     * @param data A variant containing the data to be stored in the new node.
     *
     * @code
     *  linkListOpr->insertSinglyAtStart(my_data);
     * @endcode
     */
    void LinkList::insertSinglyAtStart(base::VariantSupportedDataType data)
    {
        Singly* newNode = new Singly;
        newNode->data = data;
        newNode->next = this->singlyHead;
        this->singlyHead = newNode;
    }

    /**
     * Inserts a new node at a specific index in the Singly Linked List.
     *
     * If the index is 0, it calls insertSinglyAtStart. Otherwise, it traverses
     * to the specified position and links the new node.
     * @param data  A variant containing the data to be stored.
     * @param index The zero-based position where the node should be inserted.
     *
     * @code
     *  linkListOpr->insertSinglyAtIndex(my_data, 2);
     * @endcode
     */
    void LinkList::insertSinglyAtIndex(base::VariantSupportedDataType data,
                                       int index)
    {
        Singly* newNode = new Singly;
        newNode->data = data;

        Singly* ptr = this->singlyHead;

        int i = 0;

        // If index is not the head node
        if (index != 0)
        {
            while (i != index - 1)
            {
                ptr = ptr->next;
                i++;
            }
            newNode->next = ptr->next;
            ptr->next = newNode;
            return;
        }

        // if index is head node than run insert at start with given data
        // By this way it won't throw [Segmentation fault(core dumped)] error
        this->insertSinglyAtStart(data);
    }

    /**
     * Appends a new node to the end of the Singly Linked List.
     *
     * Traverses the list to find the last node and links the new node to it.
     * @param data A variant containing the data to be stored in the new node.
     *
     * @code
     *  base::VariantSupportedDataType my_data = 10;
     *  linkListOpr->insertSinglyAtEnd(my_data);
     * @endcode
     */
    void LinkList::insertSinglyAtEnd(base::VariantSupportedDataType data)
    {
        Singly* newNode = new Singly;
        newNode->data = data;
        newNode->next = nullptr;
        Singly* ptr = this->singlyHead;
        while (ptr->next != nullptr)
        {
            ptr = ptr->next;
        }
        ptr->next = newNode;
    }

    /**
     * Removes the first node (head) of the Singly Linked List.
     *
     * Updates the head pointer to the second node and frees the memory of the
     * old head. Displays the deletion result using
     * base::elementDeletionResultTUI.
     *
     * @code
     *  linkListOpr->deleteSinglyAtStart();
     * @endcode
     */
    void LinkList::deleteSinglyAtStart()
    {
        // Count element size before modify nodes
        int element_count = this->getSinglyListSize();

        // Modify nodes for proper deletion
        Singly* ptr = this->singlyHead;
        Singly* second_node = ptr->next;
        this->singlyHead = second_node;

        base::elementDeletionResultTUI(element_count, 0, element_count - 1,
                                       ptr->data);

        delete ptr;
    }

    /**
     * Removes the last node from the Singly Linked List.
     *
     * If the list has only one element, it calls deleteSinglyAtStart.
     * Otherwise, it traverses to the second-to-last node to update its next
     * pointer.
     * @param isVerboseMode If true, displays the deletion result via TUI.
     *
     * @code
     *  linkListOpr->deleteSinglyAtEnd();
     * @endcode
     */
    void LinkList::deleteSinglyAtEnd(bool isVerboseMode)
    {
        // Count element size before modify nodes
        int element_count = this->getSinglyListSize();

        if (element_count < 2)
        {
            this->deleteSinglyAtStart();
            return;
        }

        Singly* p = this->singlyHead;
        Singly* q = this->singlyHead->next;

        while (q->next != nullptr)
        {
            p = p->next;
            q = q->next;
        }
        p->next = nullptr;
        if (isVerboseMode)
        {
            base::elementDeletionResultTUI(element_count, element_count - 1,
                                           element_count - 1, q->data);
        }
        delete q;
    }

    /**
     * Removes a node at a specific index from the Singly Linked List.
     *
     * If the index is 0, it calls deleteSinglyAtStart. Otherwise, it traverses
     * to the node at the specified index, unlinks it, and frees its memory.
     * Displays the deletion result using base::elementDeletionResultTUI.
     *
     * @param index Get index and identify if its 0 or not.
     *
     * @code
     *  linkListOpr->deleteSinglyAtIndex(2);
     * @endcode
     */
    void LinkList::deleteSinglyAtIndex(int index)
    {
        // Count element size before modify nodes
        int element_count = this->getSinglyListSize();

        Singly* p = this->singlyHead;
        Singly* q = this->singlyHead->next;

        // If index is not the head node
        if (index != 0)
        {
            for (int i = 0; i < index - 1; i++)
            {
                p = p->next;
                q = q->next;
            }

            p->next = q->next;

            base::elementDeletionResultTUI(element_count, index,
                                           element_count - 1, q->data);

            delete q;
            // Return this function. Otherwise it will run deletion for begin
            // element.
            return;
        }

        // if head node then run delete at start
        // By this way it won't throw [Segmentation fault(core dumped)] error
        this->deleteSinglyAtStart();
    }

    // ************************************************************************
    // Circular Linked List
    // ************************************************************************

    void LinkList::createCircularListElement()
    {
        if (this->circularHead)

        {
            int element_count = this->getCircularListSize();
            for (int i = 0; i < element_count; i++)
            {
                this->deleteSinglyAtEnd(false);
            }
        }

        this->circularHead = new Circular;

        this->circularHead->next = nullptr;

        int i = 0;

        base::hideTextOfScreen();
        base::showAvailableDataTypesMenu();
        this->selected_data_type = '\0';
        menu::getMenuSelection(this->selected_data_type,
                               base::data_type_options, "Data Types", false);

        switch (this->selected_data_type)
        {
            case 'a':
            {
                this->circularHead->data = int();
                break;
            }
            case 'b':
            {
                this->circularHead->data = double();
                break;
            }
            case 'c':
            {
                this->circularHead->data = std::string();
                break;
            }
            case 'd':
            {
                this->circularHead->data = char();
                break;
            }

            case 'z':
                // back to linked list operations page
                base::clearScreen();
                return;
            default:
                return;
        }

        base::hideTextOfScreen();
        int initial_elements_count = 1;
        std::cout << "Enter the number of elements to create in the linked "
                     "list: ";
        base::getIntInput(initial_elements_count, 100);

        // Create head data first
        base::VariantSupportedDataType first_data =
            this->createLinkedListInput(this->circularHead, 0, true);
        this->circularHead->data = first_data;

        // Start index from one while head is created
        for (int i = 1; i < initial_elements_count; i++)
        {
            base::VariantSupportedDataType data =
                this->createLinkedListInput(this->circularHead, i, true);

            this->insertCircularAtEnd(data);
        }
    }

    int LinkList::getCircularListSize()
    {
        int i = 0;
        Circular* ptr = this->circularHead;
        do
        {
            ptr = ptr->next;
            i++;
        } while (ptr != this->circularHead);

        return i;
    }

    void LinkList::insertCircularAtEnd(base::VariantSupportedDataType data)
    {
        Circular* newNode = new Circular;

        newNode->data = data;

        Circular* ptr = this->circularHead;
        do
        {
            ptr = ptr->next;
        } while (ptr->next != this->circularHead);

        ptr->next = newNode;
        newNode->next = this->circularHead;
    }

    // down testing
    void LinkList::deleteCircularAtStart()
    {
        // Count element size before modify nodes
        int element_count = this->getCircularListSize();

        Circular* headToDelete = this->circularHead;
        Circular* secondNode = headToDelete->next;
        Circular* ptr = this->circularHead;

        do
        {
            ptr = ptr->next;
        } while (ptr->next != this->circularHead);

        ptr->next = secondNode;
        this->circularHead = secondNode;

        base::elementDeletionResultTUI(element_count, 0, element_count - 1,
                                       headToDelete->data);
        delete headToDelete;
    }

    void LinkList::deleteCircularAtEnd(bool isVerboseMode)
    {
        // Count element size before modify nodes
        int element_count = this->getCircularListSize();

        Circular* p = this->circularHead;
        Circular* q = this->circularHead->next;
        do
        {
            p = p->next;
            q = q->next;
        } while (q->next != this->circularHead);

        p->next = this->circularHead;

        if (isVerboseMode)
        {
            base::elementDeletionResultTUI(element_count, element_count - 1,
                                           element_count - 1, q->data);
        }

        delete q;
    }

}  // namespace lnkls