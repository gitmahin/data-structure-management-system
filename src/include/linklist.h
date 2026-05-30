#ifndef LINK_LIST_H
#define LINK_LIST_H

#include <functional>
#include <string>
#include <type_traits>

#include "base.h"
#include "menu.h"
#include "page.h"

namespace lnkls
{

    // function types For createLinkedListElement
    typedef std::function<int(void)> tListSize;
    typedef std::function<void(bool)> tDeleteListElementAtEnd;
    typedef std::function<void(base::VariantSupportedDataType)>
        tInsertListElementAtEnd;

    const std::set<char> sub_menu_options = {'a', 'b', 'c', 'z'};
    const std::set<char> operation_options = {'a', 'b', 'c', 'd', 'e',
                                              'f', 'g', 'h', 'z', 'm'};

    struct Singly
    {
        base::VariantSupportedDataType data;
        struct Singly* next;
    };

    struct Circular
    {
        base::VariantSupportedDataType data;
        struct Circular* next;
    };

    template <typename T>
    concept LinkedListNodeType =
        std::is_same_v<T, Singly> || std::is_same_v<T, Circular>;

    class LinkList : public IPage
    {
       public:
        base::OptionSelectionDataType selected_data_type;
        base::OptionSelectionDataType selected_operation;

        Singly* singlyHead;
        Circular* circularHead;

        LinkList() : singlyHead(nullptr), circularHead(nullptr) {};

        // Base
        void startMenu() override;
        void startOperationsMenu();

        // Singly operations

        void insertSinglyAtStart(base::VariantSupportedDataType data);
        void insertSinglyAtEnd(base::VariantSupportedDataType data);
        void insertSinglyAtIndex(base::VariantSupportedDataType data,
                                 int index);
        void deleteSinglyAtStart();
        void deleteSinglyAtEnd(bool isVerboseMode = true);
        void deleteSinglyAtIndex(int index);
        void traverseSingly();
        int getSinglyListSize();

        // Circular operations
        void insertCircularAtStart(base::VariantSupportedDataType data);
        void insertCircularAtEnd(base::VariantSupportedDataType data);
        void insertCircularAtIndex(base::VariantSupportedDataType data,
                                   int index);
        void deleteCircularAtStart();
        void deleteCircularAtEnd(bool isVerboseMode = true);
        void deleteCircularAtIndex(int index);
        void traverseCircular();
        int getCircularListSize();

        // Here index i has no effect on real data. It just show index in
        // std::cout
        template <LinkedListNodeType T>
        base::VariantSupportedDataType createLinkedListInput(
            T*& node, int i, bool showIndex = false);

        template <LinkedListNodeType T>
        void createLinkedListElement(
            T*& node, tListSize listSize,
            tDeleteListElementAtEnd deleteListElementAtEnd,
            tInsertListElementAtEnd insertListElementAtEnd);
    };

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
                            while (std::cin.get() != '\n');  // flush bad inputs
                            std::cout << "Invalid input! Try again."
                                      << std::endl;
                            continue;
                        }

                        while (std::cin.get() != '\n');
                        break;
                    }
                };
                result = data;
            },
            // data is a std::variant
            node->data);

        return result;
    }

    template <LinkedListNodeType T>
    void LinkList::createLinkedListElement(
        T*& node, tListSize listSize,
        tDeleteListElementAtEnd deleteListElementAtEnd,
        tInsertListElementAtEnd insertListElementAtEnd)
    {
        if (node)

        {
            int element_count = listSize();
            for (int i = 0; i < element_count; i++)
            {
                deleteListElementAtEnd(false);
            }
        }

        node = new T;
        node->next = nullptr;

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
                node->data = int();
                break;
            }
            case 'b':
            {
                node->data = double();
                break;
            }
            case 'c':
            {
                node->data = std::string();
                break;
            }
            case 'd':
            {
                node->data = char();
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

        // Create head data with specific Singly struct type first
        base::VariantSupportedDataType first_data =
            this->createLinkedListInput(node, 0, true);
        node->data = first_data;

        // Start index from one while head is created
        for (int i = 1; i < initial_elements_count; i++)
        {
            base::VariantSupportedDataType data =
                this->createLinkedListInput(node, i, true);

            insertListElementAtEnd(data);
        }
    };
}  // namespace lnkls

#endif