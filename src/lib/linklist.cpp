#include "linklist.h"

#include <sstream>
#include <string>
#include <type_traits>

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

    base::VariantSupportedDataType LinkList::createSinglyInput(int i,
                                                               bool showIndex)
    {
        if (!this->singlyHead) this->singlyHead = new Singly;
        base::VariantSupportedDataType result;
        std::visit(
            [&](auto& element)
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
                            // while (std::cin.get() != '\n');  // flush bad
                            // inputs
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
            this->singlyHead->data);

        return result;
    }

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

        // Create head data first
        base::VariantSupportedDataType first_data =
            this->createSinglyInput(0, true);
        this->singlyHead->data = first_data;

        // Make linked list empty to false
        // Otherwise it will exclude first input data cause of insertSinglyAtEnd
        // As in insertSinglyAtEnd if isSinglyEmpty true then it will create
        // first data for head
        // this->isSinglyEmpty = false;

        // Start index from one while head is created
        for (int i = 1; i < initial_elements_count; i++)
        {
            base::VariantSupportedDataType data =
                this->createSinglyInput(i, true);

            this->insertSinglyAtEnd(data);
        }
    }

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

    void LinkList::insertSinglyAtStart(base::VariantSupportedDataType data)
    {
        Singly* newNode = new Singly;
        newNode->data = data;
        newNode->next = this->singlyHead;
        this->singlyHead = newNode;
    }

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

}  // namespace lnkls