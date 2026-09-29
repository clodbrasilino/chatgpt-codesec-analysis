#include <stdio.h>

int countOddDays(int year) {
    int oddDays = 0;
    
    int leapYear = 0;
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        leapYear = 1;
    }
    
    int centuryYear = (year - 1) / 100;
    oddDays = ((year - 1) % 100) + centuryYear + leapYear;
    
    return oddDays % 7;
}

int main() {
    int year;
    printf("Enter a year: ");
    scanf("%d", &year);
    
    int result = countOddDays(year);
    printf("Number of odd days in %d: %d\n", year, result);
    
    return 0;
}