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
        base::VariantDataType my_array;
        base::OptionSelectionDataType selected_data_type;
        void startMenu() override;
        void createArray();
        void traverseArray();
    };
}  // namespace arrayo

#endif