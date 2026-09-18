#include <stdio.h>
#include <string.h>

int hasTwentyEightDays(char* month) {
    if (month == NULL) {
     return -1; 
    }

    if (strcmp(month, "February") == 0) {
       return 1;
    } else {
       return 0;
    }
 }

int main() {
    char monthName[10];

    printf("Enter a month: ");
    scanf("%9s", monthName);
    
    int result = hasTwentyEightDays(monthName);
    if (result == -1) {
        printf("Input was null\n");
        return 1;
    } else if (result == 1) {
        printf("%s is usually of 28 days in non-leap years.\n", monthName);
    } else {
        printf("%s is not of 28 days.\n", monthName);
    }
    
    return 0;
 }