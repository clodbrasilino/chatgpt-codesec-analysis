#include <stdio.h>
#include <stdbool.h>

bool has31Days(int month) {
    if(month < 1 || month > 12) {
        printf("Error: Invalid month number. It should be between 1 and 12.\n");
        return false;
    }

    if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 
       || month == 10 || month == 12){
        return true;
    }

    return false;
}

int main() {
    int month;
    printf("Enter the month number: ");
    scanf("%d", &month);

    if(has31Days(month)){
        printf("Month %d contains 31 days\n", month);
    } else {
        if(month >= 1 && month <= 12){
            printf("Month %d does not contain 31 days\n", month);
        }
    }

    return 0;
}