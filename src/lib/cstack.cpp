#include "cstack.h"

#include "menu.h"

namespace stck
{

    void Stack::startMenu(bool saveAllData)
    {
        std::cout << "========================================\n";
        std::cout << "|             Type of Stack            |\n";
        std::cout << "========================================\n";
        std::cout << "| a -> Using Array                     |\n";
        std::cout << "| b -> Using Linked List               |\n";
        std::cout << "========================================\n";
        std::cout << "| z -> Main Menu                       |\n";
        std::cout << "========================================\n";
        std::cout << "Choose Stack type: ";

        menu::getMenuSelection(this->selection_point, stck::sub_menu_options,
                               "Stack Type", false);
    }

    void Stack::startOperationsMenu()
    {
        std::cout << "========================================\n";
        std::cout << "|            Operations Menu           |\n";
        std::cout << "========================================\n";
        std::cout << "| a -> Create Stack                    |\n";
        std::cout << "| b -> Push                            |\n";
        std::cout << "| c -> Pop                             |\n";
        std::cout << "| d -> Top                             |\n";
        std::cout << "| e -> Display Stack                   |\n";
        std::cout << "========================================\n";
        std::cout << "| z -> Back                            |\n";
        std::cout << "| m -> Main Menu                       |\n";
        std::cout << "========================================\n";
        std::cout << "Choose an operation: ";

        menu::getMenuSelection(this->selected_operation,
                               stck::operations_menu_options,
                               "Linked List operations", false);
    }

    // TODO: properly complete this
    void Stack::createStackArray()
    {
        if (this->stackArray)
        {
            delete this->stackArray;
            this->stackArray = nullptr;
        }
        base::hideTextOfScreen();
        base::showAvailableDataTypesMenu();
        this->selected_data_type = '\0';
        menu::getMenuSelection(this->selected_data_type,
                               base::data_type_options, "Data Types", false);

        this->stackArray = new StackStructArray;

        switch (this->selected_data_type)
        {
            case 'a':
            {
                // TODO: fix these all bellow
                this->stackArray->data = new int();
                break;
            }
            case 'b':
            {
                this->stackArray->data = double();
                break;
            }
            case 'c':
            {
                this->stackArray->data = std::string();
                break;
            }
            case 'd':
            {
                this->stackArray->data = char();
                break;
            }

            case 'z':
            {
                delete this->stackArray;
                this->stackArray = nullptr;
                // back to Stack operations page
                base::clearScreen();
                return;
            }
            default:
                return;
        }

        base::hideTextOfScreen();
        int initial_elements_count = 1;
        std::cout << "Enter the number of elements to create in the linked "
                     "list: ";
        base::getIntInput(initial_elements_count, 100);
    }

    bool Stack::isFullArray()
    {
        if (this->stackArray->top == this->stackArray->size - 1)
        {
            return true;
        }
        return false;
    }

    bool Stack::isEmptyArray()
    {
        if (!this->stackArray->top)
        {
            return true;
        }
        return false;
    }

    void Stack::pushArray(base::VariantSupportedDataType data)
    {
        if (this->isFullArray())
        {
            std::cout << "Stack Overflow!" << std::endl;
            return;
        }

        this->stackArray->top++;
        this->stackArray->data[this->stackArray->top] = data;
    }

    base::VariantSupportedDataType Stack::popArray()
    {
        if (this->isEmptyArray())
        {
            std::cout << "Stack Empty! Cannot pop element!" << std::endl;
            return -1;
        }

        base::VariantSupportedDataType element =
            this->stackArray->data[this->stackArray->top];
        this->stackArray->top--;
        return element;
    }

    base::VariantSupportedDataType Stack::topStackArray()
    {
        if (this->isEmptyArray())
        {
            std::cout << "There is no top in empty Stack" << std::endl;
            return -1;
        }
        return this->stackArray->data[this->stackArray->top];
    }

    base::VariantSupportedDataType Stack::bottomStackArray()
    {
        if (this->isEmptyArray())
        {
            std::cout << "There is no bottom in empty Stack" << std::endl;
            return -1;
        }
        return this->stackArray->data[0];
    }

}  // namespace stck