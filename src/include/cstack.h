#ifndef CSTACK_H
#define CSTACK_H

#include "base.h";
#include "linklist.h"

namespace stck
{

    struct StackStructArray
    {
        int size;
        int top;
        base::VariantSupportedDataType* data;
    };

    class Stack
    {
        StackStructArray* stackArray;
        lnkls::Singly* stackLinkList;

        bool isFullArray();
        bool isEmptyArray();
        void pushArray(base::VariantSupportedDataType data);
        base::VariantSupportedDataType popArray();

        bool isFullLnkls();
        bool isEmptyLnkls();
        void pushLnkls();
        void popLnkls();
    };

};  // namespace stck

#endif