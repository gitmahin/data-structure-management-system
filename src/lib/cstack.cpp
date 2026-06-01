#include "cstack.h"

namespace stck
{
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
        }

        base::VariantSupportedDataType element =
            this->stackArray->data[this->stackArray->top];
        this->stackArray->top--;
        return element;
    }

}  // namespace stck