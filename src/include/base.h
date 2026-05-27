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
#include <type_traits>
#include <typeinfo>
#ifndef _MSC_VER
    #include <cxxabi.h>
#endif
#include <cstdlib>
#include <memory>
#include <string>

namespace base
{

    /**
     * Returns a human-readable string representing the type T.
     * 
     * This function uses platform-specific demangling (via abi::__cxa_demangle 
     * on non-MSVC compilers) to provide a clear name for the type, including 
     * qualifiers like const, volatile, and references.
     * 
     * @tparam T The type to get the name of.
     * @return A string containing the demangled name of type T.
     */
    template <class T>
    std::string type_name()
    {
        typedef typename std::remove_reference<T>::type TR;
        std::unique_ptr<char, void (*)(void*)> own(
#ifndef _MSC_VER
            abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr),
#else
            nullptr,
#endif
            std::free);
        std::string r = own != nullptr ? own.get() : typeid(TR).name();
        if (std::is_const<TR>::value) r += " const";
        if (std::is_volatile<TR>::value) r += " volatile";
        if (std::is_lvalue_reference<T>::value)
            r += "&";
        else if (std::is_rvalue_reference<T>::value)
            r += "&&";
        return r;
    };

    // Universal alias for menu options selection variables data type
    using OptionSelectionDataType = char;
    const std::string APP_TITLE = "DATA STRUCTURE MANAGEMENT SYSTEM";

    // std::variant reference: https://en.cppreference.com/cpp/utility/variant
    using VariantSupportedDataType =
        std::variant<int, double, std::string, char>;

    // Methods
    void showAppTitle(std::string sub_title);
    void hideTextOfScreen();
    void clearScreen();
    void pauseProgram(int second);
    void getIntInput(int& i_variable, int max = 1, int min = 0);
    void exitApp();

}  // namespace base

#endif