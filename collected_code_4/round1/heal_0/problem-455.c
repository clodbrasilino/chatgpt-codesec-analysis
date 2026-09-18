#include <stdio.h>

_Bool isMonthHave31Days(int month){
    if(month < 1 || month > 12)
        return 0;

    return month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12;
}

int main(){
    int month;
    printf("Enter the month number: ");
    scanf("%d", &month);

    if(isMonthHave31Days(month))
        printf("Month %d contains 31 days\n", month);
    else
        printf("Month %d does not contain 31 days\n", month);

    return 0;
}