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
                               "Stack operations", false);
    }

    void Stack::createStackArray()
    {
        if (this->stackArray)
        {
            delete this->stackArray;
            this->stackArray = nullptr;
        }

        base::hideTextOfScreen();
        int stack_size = 1;
        std::cout << "Enter the number of elements for Stack: ";
        base::getIntInput(stack_size, 100, stack_size);

        base::hideTextOfScreen();
        base::showAvailableDataTypesMenu();

        this->selected_data_type = '\0';
        menu::getMenuSelection(this->selected_data_type,
                               base::data_type_options, "Data Types", false);
        base::hideTextOfScreen();
        std::cout << "Creating Stack Using Array." << std::endl;
        this->stackArray = new StackStructArray;

        switch (this->selected_data_type)
        {
            case 'a':
            {
                this->stackArray->data = new int[stack_size];
                break;
            }
            case 'b':
            {
                this->stackArray->data = new double[stack_size];
                break;
            }
            case 'c':
            {
                this->stackArray->data = new std::string[stack_size];
                break;
            }
            case 'd':
            {
                this->stackArray->data = new char[stack_size];
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
        this->stackArray->top = -1;

        for (int i = 0; i < stack_size; i++)
        {
            base::VariantSupportedDataType element;
            std::visit(
                [&](auto* arr)
                {
                    typename std::decay_t<decltype(arr[0])> data;
                    element = base::getVariantDataInput(data, i, true);
                },
                this->stackArray->data);
            this->pushArray(element);
        }
    }

    bool Stack::isFullStackArray()
    {
        if (this->stackArray->top == this->stackArray->size - 1)
        {
            return true;
        }
        return false;
    }

    bool Stack::isEmptyStackArray()
    {
        if (!this->stackArray) return true;

        if (this->stackArray->top == -1)
        {
            return true;
        }
        return false;
    }

    void Stack::pushArray(base::VariantSupportedDataType data)
    {
        if (this->isFullStackArray())
        {
            std::cout << "Stack Overflow!" << std::endl;
            return;
        }

        this->stackArray->top++;

        std::visit(
            [&](auto* arr)
            {
                // Extract the underlying type from the pointer array
                using T = std::remove_pointer_t<decltype(arr)>;
                // assign variant data to the top of the
                // stack
                arr[this->stackArray->top] = std::get<T>(data);
            },
            this->stackArray->data);
    }

    base::VariantSupportedDataType Stack::popArray()
    {
        base::VariantSupportedDataType element;

        std::visit([&](auto* arr) { element = arr[this->stackArray->top]; },
                   this->stackArray->data);

        this->stackArray->top--;
        return element;
    }

    base::VariantSupportedDataType Stack::topStackArray()
    {
        if (this->isEmptyStackArray())
        {
            std::cout << "There is no top in empty Stack" << std::endl;
            return -1;
        }

        base::VariantSupportedDataType element;

        std::visit([&](auto* arr) { element = arr[this->stackArray->top]; },
                   this->stackArray->data);

        return element;
    }

    base::VariantSupportedDataType Stack::bottomStackArray()
    {
        if (this->isEmptyStackArray())
        {
            std::cout << "There is no bottom in empty Stack" << std::endl;
            return -1;
        }

        base::VariantSupportedDataType element;

        std::visit([&](auto* arr) { element = arr[0]; },
                   this->stackArray->data);

        return element;
    }

    base::VariantSupportedDataType Stack::peekArray(int i)
    {
        int array_index = this->stackArray->top - i;
        base::VariantSupportedDataType element;

        std::visit([&](auto* arr) { element = arr[array_index]; },
                   this->stackArray->data);

        return element;
    }

    void Stack::displayStackArray()
    {
        if (!this->stackArray)
        {
            std::cout << "Stack not created yet!" << std::endl;
            return;
        }

        if (this->isEmptyStackArray())
        {
            std::cout << "Stack empty!" << std::endl;
        }

        for (int i = 0; i <= this->stackArray->top; i++)
        {
            std::visit([&](auto element) { std::cout << element << std::endl; },
                       this->peekArray(i));
        }
    }

    void Stack::deleteStackArray()
    {
        if (!this->stackArray)
        {
            return;
        }

        std::visit(
            [](auto* arr)
            {
                delete[] arr;
            },
            this->stackArray->data);
        delete this->stackArray;
        this->stackArray = nullptr;
    }

}  // namespace stck