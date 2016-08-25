#include "custom.h"
#include <iostream>

Date::Date()
{
    this->day = monday;
    this->dayStr = "Mon";
    this->month = january;
    this->monthStr = "Jan";
    this->year = 1742;
    this->monthDay = 31;
}

std::string Date::update(bool &monthTick, bool &yearTick)
{
    if(static_cast<int>(this->day) < 6)
    {
        this->day = static_cast<Day>(static_cast<int>(this->day)+1);
    }
    else
    {
        this->day = static_cast<Day>(0);
    }

    this->monthDay++;

    if(this->month == static_cast<Month>(0) || this->month == static_cast<Month>(2) || this->month == static_cast<Month>(4) || this->month == static_cast<Month>(6) || this->month == static_cast<Month>(7) || this->month == static_cast<Month>(9) || this->month == static_cast<Month>(11))
    {
        if(this->monthDay > 31)
        {
            monthDay = 1;
            if(static_cast<int>(this->month) < 10)
            {
                this->month = static_cast<Month>(this->month+1);
            }
            else
            {
                this->month = static_cast<Month>(0);
                this->year++;
                yearTick = true;
            }

            monthTick = true;
        }
    }

    if(this->month == static_cast<Month>(3) || this->month == static_cast<Month>(5) || this->month == static_cast<Month>(8) || this->month == static_cast<Month>(10))
    {
        if(this->monthDay > 30)
        {
            monthDay = 1;
            if(static_cast<int>(this->month) < 11)
            {
                this->month = static_cast<Month>(this->month+1);
            }
            else
            {
                this->month = static_cast<Month>(0);
                this->year++;
            }

            monthTick = true;
        }
    }

    if(this->month == static_cast<Month>(1))
    {
        if(this->monthDay > 28)
        {
            monthDay = 1;
            if(this->month < 11)
            {
                this->month = static_cast<Month>(this->month+1);
            }
            else
            {
                this->month = static_cast<Month>(0);
                this->year++;
            }

            monthTick = true;
        }
    }

    switch (static_cast<int>(this->day))
    {
        case 0:
            this->dayStr = "Mon";
            break;

        case 1:
            this->dayStr = "Tue";
            break;

        case 2:
            this->dayStr = "Wed";
            break;

        case 3:
            this->dayStr = "Thu";
            break;

        case 4:
            this->dayStr = "Fri";
            break;

        case 5:
            this->dayStr = "Sat";
            break;

        case 6:
            this->dayStr = "Sun";
            break;

        default:
            this->dayStr = "IDFK THE DAYS OF THE WEEK!";
            break;

    }

        switch (this->month)
    {
        case 0:
            this->monthStr = "Jan";
            break;

        case 1:
            this->monthStr = "Feb";
            break;

        case 2:
            this->monthStr = "Mar";
            break;

        case 3:
            this->monthStr = "Apr";
            break;

        case 4:
            this->monthStr = "May";
            break;

        case 5:
            this->monthStr = "Jun";
            break;

        case 6:
            this->monthStr = "Jul";
            break;

        case 7:
            this->monthStr = "Aug";
            break;

        case 8:
            this->monthStr = "Sep";
            break;

        case 9:
            this->monthStr = "Oct";
            break;

        case 10:
            this->monthStr = "Nov";
            break;

        case 11:
            this->monthStr = "Dec";
            break;

        default:
            this->monthStr = "IDFK THE MONTHS!";
            break;

    }

    return std::string(this->dayStr) + std::string("\t") + std::to_string(this->monthDay) + std::string("\t") + std::string(this->monthStr) + std::string("\t") + std::to_string(this->year);
}
