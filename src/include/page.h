#ifndef PAGE_H
#define PAGE_H

class IPage
{
public:
    base::OptionSelectionDataType selection_point;
    virtual void startMenu() = 0;
};

#endif