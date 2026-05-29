#ifndef LINK_LIST_H
#define LINK_LIST_H

#include "base.h"
#include "page.h"

namespace lnkls
{

    const std::set<char> sub_menu_options = {'a', 'b', 'c', 'z'};
    const std::set<char> operation_options = {'a', 'b', 'c', 'd', 'e',
                                              'f', 'g', 'h', 'z', 'm'};

    class LinkList : public IPage
    {
       public:
        base::OptionSelectionDataType selected_data_type;
        base::OptionSelectionDataType selected_operation;
        struct Singly
        {
            base::VariantSupportedDataType data;
            struct Singly* next;
        };

        struct Singly* singlyHead;

        void startMenu() override;
        void startOperationsMenu();

        // Singly operations
        void createSinglyListElement();
        void insertSinglyAtStart(base::VariantSupportedDataType data);
        void insertSinglyAtEnd(base::VariantSupportedDataType data);
        void insertSinglyAtIndex(base::VariantSupportedDataType data,
                                 int index);
        void deleteSinglyAtStart();
        void deleteSinglyAtEnd(bool isVerboseMode = true);
        void deleteSinglyAtIndex(int index);
        void traverseSingly();
        int getSinglyListSize();

        // Here index i has no effect on real data. It just show index in std::cout
        base::VariantSupportedDataType createSinglyInput(
            int i, bool showIndex = false);
    };
}  // namespace lnkls

#endif