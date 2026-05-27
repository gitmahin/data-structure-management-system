#ifndef LINK_LIST_H
#define LINK_LIST_H

#include "base.h"
#include "page.h"

namespace lnkls
{

    const std::set<char> sub_menu_options = {'a', 'b', 'c', 'z'};
    const std::set<char> operation_options = {'a', 'b', 'c', 'd', 'e',
                                              'f', 'g', 'h', 'z'};

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

        struct Singly* singlyHead = new struct Singly;

        void startMenu() override;
        void startOperationsMenu();
        void createSinglyListElement();

        void insertSinglyAtStart(struct Singly*& head);
        void insertSinglyAtEnd(base::VariantSupportedDataType data);
        void insertSinglyAtIndex(struct Singly*& head,
                                 base::VariantSupportedDataType data,
                                 int index);
        void deleteSinglyAtStart(struct Singly*& head);
        void deleteSinglyAtEnd(struct Singly*& head);
        void deleteSinglyAtIndex(struct Singly*& head,
                                 base::VariantSupportedDataType data,
                                 int index);
        void traverseSingly();

       private:
        base::VariantSupportedDataType createSinglyInput(int i);
    };
}  // namespace lnkls

#endif