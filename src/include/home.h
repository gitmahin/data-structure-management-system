#ifndef HOME_H
#define HOME_H
#include "base.h"
#include "page.h"

namespace home
{

    class Home : public IPage
    {
    public:
        void startMenu() override ;
    };

}

#endif