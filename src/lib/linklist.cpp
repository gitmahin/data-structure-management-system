#include "linklist.h"

#include <functional>
#include <sstream>
#include <string>
#include <type_traits>
#include <variant>

#include "menu.h"

namespace lnkls
{

    /**
     * Displays the menu for selecting the type of Linked List to manage.
     *
     * Provides options for Singly, Circular, and Doubly Linked Lists.
     * Updates the selection_point based on user input.
     *
     * @param saveAllData A boolean flag indicating if data persistence is
     * active (inherited from IPage, used for UI consistency).
     */
    void LinkList::startMenu(bool saveAllData)
    {
        // Clear home page for new page

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

    /**
     * Displays the operations menu for the currently selected Linked List type.
     *
     * Includes standard operations like creation, traversal, insertion, and
     * deletion. Updates the selected_operation member variable.
     */
    void LinkList::startOperationsMenu()
    {
        // Clear home page for new page

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

    // ************************************************************************
    // Singly Linked List
    // ************************************************************************

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
        if (!this->singlyHead) return 0;
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
        // If index is not the head node
        if (index != 0)
        {
            Singly* newNode = new Singly;
            newNode->data = data;

            Singly* ptr = this->singlyHead;

            int i = 0;
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

        // If index is not the head node
        if (index != 0)
        {
            Singly* p = this->singlyHead;
            Singly* q = this->singlyHead->next;

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

    /**
     * Iterates through the Circular Linked List and prints each element's data.
     * Uses std::visit to handle the variant data type stored in each node.
     * Displays "Empty List" if the list head is null.
     */
    void LinkList::traverseCircular()
    {
        if (!this->circularHead) std::cout << "Empty List" << std::endl;
        Circular* ptr = this->circularHead;

        do
        {
            std::visit([](auto& element) { std::cout << element << std::endl; },
                       ptr->data);
            ptr = ptr->next;
        } while (ptr != this->circularHead);
    }

    /**
     * Calculates the total number of nodes currently in the Circular Linked
     * List.
     *
     * Iterates through the list starting from the head and loops until it
     * returns to the head node.
     * @return The integer count of elements in the list.
     *
     * @code
     *  int size = linkListOpr->getCircularListSize();
     * @endcode
     */
    int LinkList::getCircularListSize()
    {
        int i = 0;
        if (!this->circularHead) return 0;
        Circular* ptr = this->circularHead;
        do
        {
            ptr = ptr->next;
            i++;
        } while (ptr != this->circularHead);

        return i;
    }

    /**
     * Inserts a new node at the beginning of the Circular Linked List.
     *
     * Creates a new node, finds the last node to maintain the circular link,
     * and updates the head pointer.
     * @param data A variant containing the data to be stored in the new node.
     *
     * @code
     *  linkListOpr->insertCircularAtStart(my_data);
     * @endcode
     */
    void LinkList::insertCircularAtStart(base::VariantSupportedDataType data)
    {
        Circular* newNode = new Circular;
        Circular* oldHead = this->circularHead;
        newNode->data = data;

        Circular* ptr = this->circularHead;
        do
        {
            ptr = ptr->next;
        } while (ptr->next != this->circularHead);

        ptr->next = newNode;
        newNode->next = oldHead;
        this->circularHead = newNode;
    }

    /**
     * Inserts a new node at a specific index in the Circular Linked List.
     *
     * If the index is 0, it calls insertCircularAtStart to handle head and tail
     * updates. Otherwise, it traverses to the specified position and links the
     * new node.
     * @param data  A variant containing the data to be stored.
     * @param index The zero-based position where the node should be inserted.
     *
     * @code
     *  linkListOpr->insertCircularAtIndex(my_data, 2);
     * @endcode
     */
    void LinkList::insertCircularAtIndex(base::VariantSupportedDataType data,
                                         int index)
    {
        if (index != 0)
        {
            Circular* newNode = new Circular;
            Circular* ptr = this->circularHead;
            newNode->data = data;

            // You can use while here. I just used this loop and feeling Lazy to
            // delete, copy, write and .....
            for (int i = 0; i < index - 1; i++)
            {
                ptr = ptr->next;
            }

            newNode->next = ptr->next;
            ptr->next = newNode;

            return;
        }

        this->insertCircularAtStart(data);
    }

    /**
     * Appends a new node to the end of the Circular Linked List.
     *
     * Traverses the list to find the current last node and updates its next
     * pointer to the new node, while the new node points back to the head.
     * @param data A variant containing the data to be stored in the new node.
     *
     * @code
     *  linkListOpr->insertCircularAtEnd(my_data);
     * @endcode
     */
    void LinkList::insertCircularAtEnd(base::VariantSupportedDataType data)
    {
        Circular* newNode = new Circular;

        newNode->data = data;

        Circular* ptr = this->circularHead;

        if (ptr->next != nullptr)
        {
            do
            {
                ptr = ptr->next;
            } while (ptr->next != this->circularHead);
        }

        ptr->next = newNode;
        newNode->next = this->circularHead;
    }

    /**
     * Removes the first node (head) of the Circular Linked List.
     *
     * Updates the tail's next pointer to the second node and frees the memory
     * of the old head. Displays the deletion result using
     * base::elementDeletionResultTUI.
     *
     * @code linkListOpr->deleteCircularAtStart(); @endcode
     */
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

    /**
     * Removes a node at a specific index from the Circular Linked List.
     *
     * If the index is 0, it calls deleteCircularAtStart. Otherwise, it
     * traverses to the node at the specified index, unlinks it, and frees its
     * memory. Displays the deletion result using
     * base::elementDeletionResultTUI.
     *
     * @param index The zero-based position of the node to be deleted.
     * @code linkListOpr->deleteCircularAtIndex(2); @endcode
     */
    void LinkList::deleteCircularAtIndex(int index)
    {
        // Count element size before modify nodes
        int element_count = this->getCircularListSize();

        if (index != 0)
        {
            Circular* p = this->circularHead;
            Circular* q = this->circularHead->next;

            for (int i = 0; i < index - 1; i++)
            {
                p = p->next;
                q = q->next;
            }

            p->next = q->next;

            base::elementDeletionResultTUI(element_count, element_count - 1,
                                           element_count - 1, q->data);

            delete q;

            // Return this function. Otherwise it will run deletion for begin
            // element.
            return;
        }

        this->deleteCircularAtStart();
    }

    /**
     * Removes the last node from the Circular Linked List.
     *
     * Traverses the list to find the second-to-last node, updates its next
     * pointer to point back to the head, and frees the memory of the last node.
     * @param isVerboseMode If true, displays the deletion result via TUI.
     *
     * @code
     *  linkListOpr->deleteCircularAtEnd();
     * @endcode
     */
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

    // *********************************************************************
    // Doubly Linked List
    // *********************************************************************
    void LinkList::insertDoublyAtStart(base::VariantSupportedDataType data)
    {
        if (!this->doublyHead) return;
        Doubly* newNode = new Doubly;
        Doubly* oldHead = this->doublyHead;

        // Set data
        newNode->data = data;

        // Set links
        newNode->next = oldHead;
        oldHead->prev = newNode;
        newNode->prev = nullptr;

        // Make new node as doubly head
        this->doublyHead = newNode;
    }

    void LinkList::insertDoublyAtEnd(base::VariantSupportedDataType data)
    {
        if (!this->doublyHead) return;
        Doubly* newNode = new Doubly;
        Doubly* ptr = this->doublyHead;
        // Set data;
        newNode->data = data;

        // reach to the last node
        while (ptr->next != nullptr)
        {
            ptr = ptr->next;
        }

        // Set links
        newNode->next = nullptr;
        newNode->prev = ptr;
        ptr->next = newNode;
    }

    void LinkList::insertDoublyAtIndex(base::VariantSupportedDataType data,
                                       int index)
    {
        if (!this->doublyHead) return;
        if (index != 0)
        {
            Doubly* newNode = new Doubly;
            Doubly* ptr = this->doublyHead;

            // Set data
            newNode->data = data;

            // reach to index - 1
            for (int i = 0; i < index; i++)
            {
                ptr = ptr->next;
            }

            newNode->next = ptr;

            // set links in between of ptr old prev node and newNode
            ptr->prev->next = newNode;
            newNode->prev = ptr->prev;

            // set link with new ptr prev node;
            ptr->prev = newNode;
            return;
        }

        this->insertDoublyAtStart(data);
    }

    void LinkList::deleteDoublyAtStart()
    {
        if (!this->doublyHead) return;
        int element_count = this->getDoublyListSize();

        Doubly* oldHeadToDelete = this->doublyHead;
        Doubly* nextNode;

        if (this->doublyHead->next != nullptr)
        {
            nextNode = this->doublyHead->next;
            nextNode->prev = nullptr;
        }

        base::elementDeletionResultTUI(element_count, 0, element_count - 1,
                                       oldHeadToDelete->data);

        if (oldHeadToDelete->next == nullptr &&
            oldHeadToDelete->prev == nullptr)
        {
            delete oldHeadToDelete;
            this->doublyHead = nullptr;
        }
        else
        {
            delete oldHeadToDelete;
            this->doublyHead = nextNode;
        }
    }

    void LinkList::deleteDoublyAtEnd(bool isVerboseMode)
    {
        if (!this->doublyHead) return;
        int element_count = this->getDoublyListSize();
        Doubly* ptr = this->doublyHead;

        while (ptr->next != nullptr)
        {
            ptr = ptr->next;
        }

        if (isVerboseMode)
        {
            base::elementDeletionResultTUI(element_count, element_count - 1,
                                           element_count - 1, ptr->data);
        }

        if (ptr == this->doublyHead)
        {
            delete ptr;
            this->doublyHead = nullptr;
            return;
        }

        ptr->prev->next = nullptr;

        delete ptr;
    }

    // TODO: Find bug:
    // When there is one element
    // selecting 0 index for deletion shows segment fault error.
    void LinkList::deleteDoublyAtIndex(int index)
    {
        if (!this->doublyHead) return;
        if (index != 0)
        {
            int element_count = this->getDoublyListSize();
            Doubly* ptr = this->doublyHead;

            // reach to index - 1
            for (int i = 0; i < index; i++)
            {
                ptr = ptr->next;
            }

            ptr->prev->next = ptr->next;
            if (ptr->next != nullptr)
            {
                ptr->next->prev = ptr->prev;
            }

            base::elementDeletionResultTUI(element_count, element_count - 1,
                                           element_count - 1, ptr->data);

            delete ptr;
            return;
        }

        this->deleteDoublyAtStart();
    }

    void LinkList::traverseDoubly()
    {
        if (!this->doublyHead) return;
        Doubly* ptr = this->doublyHead;
        while (ptr != nullptr)
        {
            std::visit([](auto& element) { std::cout << element << std::endl; },
                       ptr->data);
            ptr = ptr->next;
        }
    }

    int LinkList::getDoublyListSize()
    {
        if (!this->doublyHead) return 0;
        int i = 0;
        Doubly* ptr = this->doublyHead;
        while (ptr != nullptr)
        {
            ptr = ptr->next;
            i++;
        }

        return i;
    }

}  // namespace lnkls