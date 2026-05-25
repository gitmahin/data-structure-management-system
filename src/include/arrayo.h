#ifndef ARRAY_H
#define ARRAY_H

#include <vector>

#include "base.h"
#include "page.h"
#include "variant"

namespace arrayo
{

    class ArrayO : public IPage
    {
       public:
        base::VariantVectorDataType my_array;
        base::OptionSelectionDataType selected_data_type;
        void startMenu() override;
        void createArray();
        void traverseArray();
        void insertAt(string label, bool atBegin = true, bool atEnd = false, bool atIndex = false, int index = 0);
    };
}  // namespace arrayo

#endif