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

    base::VariantSupportedDataType LinkList::createSinglyInput(int i, bool showIndex)
    {
        base::VariantSupportedDataType result;
        std::visit(
            [&](auto& element)
            {
                typename std::decay_t<decltype(element)> data;

                while (true)
                {
                    if(showIndex) {

                        std::cout << "Enter element ["
                        << base::type_name<decltype(data)>() << "][" << i
                        << "]: ";
                    }
                    else {
                         std::cout << "Enter element ["
                        << base::type_name<decltype(data)>() << "]";
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
        base::VariantSupportedDataType first_data = this->createSinglyInput(0, true);
        this->singlyHead->data = first_data;

        // Start index from one while head is created
        for (int i = 1; i < initial_elements_count; i++)
        {
            base::VariantSupportedDataType data = this->createSinglyInput(i, true);

            this->insertSinglyAtEnd(data);
        }
    }

    void LinkList::traverseSingly()
    {
        Singly* ptr = this->singlyHead;
        while (ptr != nullptr)
        {
            std::visit([](auto& element) { std::cout << element << std::endl; },
                       ptr->data);
            ptr = ptr->next;
        }
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
        while (i != index - 1)
        {
            ptr = ptr->next;
            i++;
        }
        newNode->next = ptr->next;
        ptr->next = newNode;
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

    void LinkList::deleteSinglyAtEnd()
    {
        Singly* p = this->singlyHead;
        Singly* q = this->singlyHead->next;

        while (q->next != nullptr)
        {
            p = p->next;
            q = q->next;
        }
        p->next = nullptr;
        delete q;
    }

}  // namespace lnkls