#include <stdbool.h>

bool is_leap(int year) {
    if(year % 4 != 0) 
        return false;
    else if(year % 100 != 0) 
        return true;
    else if(year % 400 != 0) 
        return false;
    else 
        return true;
}

bool validate_gregorian_date(int day, int month, int year) {
    if(year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    if(month == 2) {
        if(is_leap(year)) {
            if(day > 29)
                return false;
        } else {
            if(day > 28) 
                return false;
        }
    }

    if(month == 4 || month == 6 || month == 9 || month == 11) {
        if(day > 30)
            return false;
    }  

    return true;
}

int main()
{
    int day, month, year;
    bool valid_date;

    /* Mocked date to be validated */
    day = 17;
    month = 12;
    year = 2021;

    valid_date = validate_gregorian_date(day, month, year);

    return valid_date ? 0 : 1;
}