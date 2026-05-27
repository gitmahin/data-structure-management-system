#ifndef LINK_LIST_H
#define LINK_LIST_H

#include "base.h"
#include "page.h"

namespace lnkls
{
    class LinkList : public IPage
    {
       public:
        void startMenu() override;
    };
}  // namespace lnkls

#endif