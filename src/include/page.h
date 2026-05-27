#ifndef PAGE_H
#define PAGE_H

/**
 * Interface for application pages.
 * 
 * Provides a common structure for different sections of the application,
 * ensuring they handle menu navigation and store user selections consistently.
 */
class IPage
{
   public:
    /**
     * Stores the user's current menu selection.
     */
    base::OptionSelectionDataType selection_point;

    /**
     * Displays the menu for the page and handles initial user interaction.
     */
    virtual void startMenu() = 0;
};

#endif