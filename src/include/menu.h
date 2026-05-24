#ifndef BASE_MENU_H
#define BASE_MENU_H

#include "base.h"
#include <set>
#include <string>

namespace menu
{
    // Methods
    void getMenuSelection(char &selection_point, set<char> &menu_options, string menu_label, bool shouldExitOnInputI);
}

#endif