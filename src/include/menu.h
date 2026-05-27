#ifndef BASE_MENU_H
#define BASE_MENU_H

#include <set>
#include <string>

#include "base.h"

namespace menu
{
    // Methods
    void getMenuSelection(char& selection_point, const std::set<char>& menu_options,
                          std::string menu_label, bool shouldExitOnInputI);
}  // namespace menu

#endif