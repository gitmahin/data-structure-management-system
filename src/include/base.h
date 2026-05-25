/**
 * Base Setup
 *
 * This header provides a minimal base configuration
 * for C++ projects. It includes the standard I/O
 * library and brings the std namespace into scope,
 * so you can use cout, cin, etc. without the std::
 * prefix. Include this file at the top of any
 * translation unit that needs standard I/O.
 */

#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <variant>
#include <vector>

using namespace std;

namespace base
{
    // Universal alias for menu options selection variables data type
    using OptionSelectionDataType = char;
    const string APP_TITLE = "DATA STRUCTURE MANAGEMENT SYSTEM";

    // std::variant reference: https://en.cppreference.com/cpp/utility/variant
    using VariantSupportedDataType = variant<int, double, string, char>;

    // Methods
    void showAppTitle(string sub_title);
    void hideTextOfScreen();
    void clearScreen();
    void pauseProgram(int second);
    void getIntInput(int& i_variable);
    void exitApp();

}  // namespace base

#endif