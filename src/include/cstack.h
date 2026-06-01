#ifndef CSTACK_H
#define CSTACK_H

#include "base.h"
#include "linklist.h"
#include "page.h"

namespace stck
{
    // Its for only creating dynamic data of variant datatype in heap mem
    using VariantStackSupportedDataType =
        std::variant<int*, char*, double*, std::string*>;
    // selection_point(from IPage) is handled by sub_menu_options
    const std::set<base::OptionSelectionDataType> sub_menu_options = {'a', 'b',
                                                                      'z'};
    const std::set<base::OptionSelectionDataType> operations_menu_options = {
        'a', 'b', 'c', 'd', 'e', 'z', 'm'};

    struct StackStructArray
    {
        int size;
        int top;
        // make pointers variable as we have to create dynamic memory allocation
        // for each data type cannot use VariantSupportedDataType here as new
        // (keyword) will not work on this. we can request dynamic memory only
        // with pointers.
        VariantStackSupportedDataType data;
    };

    class Stack : public IPage
    {
       public:
        base::OptionSelectionDataType selected_data_type;
        base::OptionSelectionDataType selected_operation;

        StackStructArray* stackArray = nullptr;
        lnkls::Singly* stackLinkList = nullptr;

        // Base setup
        void startMenu(bool saveAllData = false) override;
        void startOperationsMenu();

        // ┌──────────────────────────────────────────────────────────┐
        // │                   Stack using Array                      │
        // └──────────────────────────────────────────────────────────┘
        bool isFullStackArray();
        bool isEmptyStackArray();

        // Return and accept normal variant data as it doesn't care with dynamic
        // memory or pointer. It just take input and give return value. no need
        // pointer here
        void pushArray(base::VariantSupportedDataType data,
                       bool showSuccessLog = false);
        base::VariantSupportedDataType popArray();
        base::VariantSupportedDataType topStackArray();
        base::VariantSupportedDataType bottomStackArray();
        void createStackArray();
        void displayStackArray();
        base::VariantSupportedDataType peekStackArray(int i);

        // Its for delete dynamic memory allocation after switch to another task
        void deleteStackArray();

        // Handling one time push onto the stack
        void handleSinglePushStackArray();
        void showStackArrayStatus();

        // ┌──────────────────────────────────────────────────────────┐
        // │                 Stack using Linked List                  │
        // └──────────────────────────────────────────────────────────┘
        bool isFullLnkls();
        bool isEmptyLnkls();
        void pushLnkls();
        void popLnkls();
    };

};  // namespace stck

#endif