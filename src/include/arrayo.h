#ifndef ARRAY_H
#define ARRAY_H

#include <vector>

#include "base.h"
#include "page.h"
#include "variant"

namespace arrayo
{
    // Constant values
    const std::set<base::OptionSelectionDataType> sub_menu_options = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'z'};
    using VariantVectorDataType =
        std::variant<std::vector<int>, std::vector<double>,
                     std::vector<std::string>, std::vector<char>>;

    class ArrayO : public IPage
    {
       public:
        VariantVectorDataType my_array;
        base::OptionSelectionDataType selected_data_type;
        void startMenu(bool saveAllData = false) override;
        void createArray();
        void traverseArray();
        void insertAt(std::string label, bool atBegin = true,
                      bool atEnd = false, bool atIndex = false, int index = 0);
        // atEnd is by default true as we have easy method pop_back() for vector
        // to delete last element.
        void deleteElement(bool atBegin = false, bool atEnd = true,
                           bool atIndex = false, int index = 0);
        int getArraySize();

       private:
        void validVectorCreateInput(int i);
        base::VariantSupportedDataType validVectorInsertInput();
    };

}  // namespace arrayo

#endif