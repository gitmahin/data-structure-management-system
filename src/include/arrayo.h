#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
#include "base.h"
#include "page.h"
#include "variant"

namespace arrayo
{

    using CustomArrayDataType = variant<vector<int>, vector<double>, vector<string>, vector<char>>;

    class ArrayO : public IPage
    {
    public:
        CustomArrayDataType my_array;
        base::OptionSelectionDataType selected_data_type;
        void startMenu() override;
        void createArray();
    };
}

#endif