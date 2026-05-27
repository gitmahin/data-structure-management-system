
#ifdef _WIN32
    #include <conio.h>
    #include <windows.h> // Keep windows.h at top
#else
    #include <termios.h>
    #include <unistd.h>
#endif

// #include <bitset> // for testing newt.c_lflag bits are on or off
#include <stdio.h>

#include <iostream>

#include "presskey.h"

char getCharInput()
{
    // clang-format off
    #ifdef _WIN32
        return _getch();  // platform specific
    #else
   
        /**
         * termios MAN: https://pubs.opengroup.org/onlinepubs/7908799/xsh/termios.h.html
         * Reference of this code: https://www.flipcode.com/archives/_kbhit_for_Linux.shtml
         * Learn Biwise operator:
         * https://en.cppreference.com/cpp/language/operator_arithmetic
         */

        termios oldt, newt; // create two terminal settings variables
        tcgetattr(STDIN_FILENO, &oldt); // store current terminal settings for
                                        // future restore (if settings modified)
        newt = oldt; // create new terminal with current terminal settings for
                     // start safe modification
       
        ///////////////////////////////////////////////////////////////////////
        // Logging bits are on or off                                        //
        //                                                                   //
        // Print full c_lflag                                                //
        // cout << "c_lflag bits: " << bitset<32>(newt.c_lflag) << endl;     //
        //                                                                   //
        // Check ICANON specifically                                         //
        // cout << "ICANON value: " << bitset<32>(ICANON) << endl;           //
        // cout << "ECHO value:   " << bitset<32>(ECHO)   << endl;           //
        ///////////////////////////////////////////////////////////////////////
             
        /**
         *  The c_lflag field of the argument structure is used to control various
         * terminal functions
         */
        newt.c_lflag &=
            ~(ICANON | ECHO);  // flip (toggle on/off by default those are on) every
                               // bits of ICANON(line buffering. wait for enter key)
                               // and ECHO(show typed chars on screen)
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // apply new settings to terminal

        char ch = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // restore old terminal settings after completing press
                                                  // any key operation.
        return ch;
   
    #endif
    // clang-format on
}

namespace presskey
{
    /**
     * Pauses the program and waits for the user to press any key.
     * Displays a custom or default message with an animated ellipsis.
     *
     * @param alert_text The message to display to the user.
     * @return Returns 1 upon key press.
     *
     * @code
     * presskey::pressAnyKey("Press any key to return to menu");
     * @endcode
     */
    int pressAnyKey(std::string alert_text)
    {
        if (alert_text != "")
            std::cout << alert_text;
        else
            std::cout << "Press any key to continue";

        while (true)
        {
            std::cout << "...";
            std::cout.flush();

            // clang-format off
            
            // Cross-platform program pausing
            #ifdef _WIN32
          
                Sleep(500);  // notice the capital -> S
            #else                   
       
                usleep(500000);
            #endif
            // clang-format on

            if (getCharInput()) break;
        }

        std::cout << std::endl;
        return 1;
    }
}  // namespace presskey