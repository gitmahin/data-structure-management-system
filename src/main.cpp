#include "base.h"
#include "home.h"
#include "arrayo.h"

using namespace home;
using namespace arrayo;

int main()
{
    Home *appHome = new Home();

    ArrayO *arrayOpr;

    // if(appHome->selection_point == 'a') {
    //     delete appHome;
    //     arrayOpr = new ArrayO;
    //     arrayOpr->startMenu();
    //     if(arrayOpr->selection_point == 'i') {
    //         delete arrayOpr;
    //         appHome = new Home();

    //     }

    // }

    while (appHome->selection_point != 'i')
    {
        appHome->startMenu();
        cout << "here" << appHome->selection_point << endl;

        switch (appHome->selection_point)
        {
        case 'a':
            arrayOpr = new ArrayO();
            
            while(arrayOpr->selection_point != 'i') {
                arrayOpr->startMenu();
                
                if(arrayOpr->selection_point == 'a') {
                    arrayOpr->createArray();
                }
                
            }
            delete arrayOpr;
            break;

        default:
            cout << "NOTHING" << endl;
            break;
        }
    }
    return 0;
}