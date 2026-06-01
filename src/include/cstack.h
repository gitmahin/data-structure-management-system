#ifndef CSTACK_H
#define CSTACK_H

#include "base.h"
#include "linklist.h"
#include "page.h"

namespace stck
{
    // selection_point(from IPage) is handled by sub_menu_options
    const std::set<base::OptionSelectionDataType> sub_menu_options = {'a', 'b', 'z'};
    const std::set<base::OptionSelectionDataType> operations_menu_options = {
        'a', 'b', 'c', 'd', 'e', 'z', 'm'};

    struct StackStructArray
    {
        int size;
        int top;
        base::VariantSupportedDataType* data;
    };

    class Stack : public IPage
    {
       public:
        base::OptionSelectionDataType selected_data_type;
        base::OptionSelectionDataType selected_operation;

        StackStructArray* stackArray =  nullptr;
        lnkls::Singly* stackLinkList =  nullptr;

        // Base setup
        void startMenu(bool saveAllData = false) override;
        void startOperationsMenu();

        // Stack using Array
        bool isFullArray();
        bool isEmptyArray();
        void pushArray(base::VariantSupportedDataType data);
        base::VariantSupportedDataType popArray();
        base::VariantSupportedDataType topStackArray();
        base::VariantSupportedDataType bottomStackArray();
        void createStackArray();

        // Stack using Linked List
        bool isFullLnkls();
        bool isEmptyLnkls();
        void pushLnkls();
        void popLnkls();
    };

};  // namespace stck

#endif