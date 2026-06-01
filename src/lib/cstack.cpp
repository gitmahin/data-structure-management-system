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

    /**
     * Initializes a new stack using a dynamic array.
     *
     * Prompts the user to specify the stack capacity and the data type.
     * It handles memory allocation for the underlying array based on the
     * selected type (int, double, string, or char) and allows initial
     * elements to be pushed onto the stack.
     */
    void Stack::createStackArray()
    {
        if (this->stackArray)
        {
            delete this->stackArray;
            this->stackArray = nullptr;
        }

        base::hideTextOfScreen();
        int stack_size = 1;
        std::cout
            << "Specify the maximum number of elements the stack can hold: ";
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
        this->stackArray->size = stack_size;

        base::hideTextOfScreen();

        int number_of_elements_to_add = 0;
        this->showStackArrayStatus();
        std::cout << "Enter the number of elements to push onto the stack "
                     "(within the available space): ";
        base::getIntInput(number_of_elements_to_add, this->stackArray->size, 0);

        for (int i = 0; i < number_of_elements_to_add; i++)
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

    /**
     * Displays the current status of the stack array.
     *
     * Prints the number of elements currently stored in the stack and the
     * number of remaining available slots based on the stack's maximum
     * capacity.
     */
    void Stack::showStackArrayStatus()
    {
        if (!this->stackArray) return;

        int stack_taken_size = (this->stackArray->top + 1);
        int stack_available_slots =
            this->stackArray->size - (this->stackArray->top + 1);

        std::cout << "Stack Status: " << stack_taken_size
                  << " element(s) in use | " << stack_available_slots
                  << " slot(s) available" << std::endl;
    }

    /**
     * Checks if the stack array has reached its maximum capacity.
     *
     * @return True if the top index is equal to the size minus one,
     * indicating no more elements can be pushed; false otherwise.
     */
    bool Stack::isFullStackArray()
    {
        if (this->stackArray->top == this->stackArray->size - 1)
        {
            return true;
        }
        return false;
    }

    /**
     * Checks if the stack array is empty.
     *
     * @return True if the stack has not been initialized or if the top index
     * is -1, indicating no elements are present; false otherwise.
     */
    bool Stack::isEmptyStackArray()
    {
        if (!this->stackArray) return true;

        if (this->stackArray->top == -1)
        {
            return true;
        }
        return false;
    }

    /**
     * Pushes a new element onto the stack array.
     *
     * Increments the top index and assigns the provided data to the new top
     * position. Checks for stack overflow before insertion.
     * @param data           The variant containing the value to be pushed.
     * @param showSuccessLog If true, prints a success message to the console.
     */
    void Stack::pushArray(base::VariantSupportedDataType data,
                          bool showSuccessLog)
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
                // assign variant data to the top of the stack
                arr[this->stackArray->top] = std::get<T>(data);
            },
            this->stackArray->data);
        if (showSuccessLog)
        {
            std::cout << "Element pushed success." << std::endl;
        }
    }

    /**
     * Handles the input and execution of a single push operation for the stack
     * array.
     *
     * Uses std::visit to determine the underlying data type of the stack,
     * prompts the user for a matching value, and pushes it onto the stack
     * with a success log.
     */
    void Stack::handleSinglePushStackArray()
    {
        std::visit(
            [&](auto* arr)
            {
                typename std::decay_t<decltype(arr[0])> input;
                base::VariantSupportedDataType data =
                    base::getVariantDataInput(input);
                this->pushArray(data, true);
            },
            this->stackArray->data);
    }

    /**
     * Removes and returns the top element from the stack array.
     *
     * Retrieves the value at the current top index, decrements the top pointer,
     * and returns the value as a variant.
     * @return A variant containing the element removed from the top of the
     * stack.
     */
    base::VariantSupportedDataType Stack::popArray()
    {
        base::VariantSupportedDataType element;

        std::visit([&](auto* arr) { element = arr[this->stackArray->top]; },
                   this->stackArray->data);

        this->stackArray->top--;
        return element;
    }

    /**
     * Retrieves the top element of the stack array without removing it.
     *
     * Checks if the stack is empty before attempting to access the top index.
     * @return A variant containing the value at the top of the stack, or -1
     * if the stack is empty.
     */
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

    /**
     * Retrieves the bottom element of the stack array.
     *
     * Checks if the stack is empty before attempting to access the first index.
     * @return A variant containing the value at the bottom of the stack, or -1
     * if the stack is empty.
     */
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

    /**
     * Retrieves an element from the stack array at a specific offset from the
     * top.
     *
     * Calculates the target index by subtracting the provided offset from the
     * current top index.
     * @param i The offset from the top (0 for top, 1 for element below top,
     * etc.).
     * @return A variant containing the element at the calculated position.
     */
    base::VariantSupportedDataType Stack::peekStackArray(int i)
    {
        int array_index = this->stackArray->top - i;
        base::VariantSupportedDataType element;

        std::visit([&](auto* arr) { element = arr[array_index]; },
                   this->stackArray->data);

        return element;
    }

    /**
     * Displays all elements currently stored in the stack array.
     *
     * Iterates from the top of the stack down to the bottom, printing each
     * element's value. If the stack is not initialized or is empty, it
     * prints an appropriate message.
     */
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
                       this->peekStackArray(i));
        }
    }

    /**
     * Deletes the stack array and releases allocated memory.
     *
     * Uses std::visit to delete the dynamically allocated array of the
     * specific data type, then deletes the StackStructArray container
     * and sets the pointer to nullptr.
     */
    void Stack::deleteStackArray()
    {
        if (!this->stackArray)
        {
            return;
        }

        std::visit([](auto* arr) { delete[] arr; }, this->stackArray->data);
        delete this->stackArray;
        this->stackArray = nullptr;
    }

}  // namespace stck