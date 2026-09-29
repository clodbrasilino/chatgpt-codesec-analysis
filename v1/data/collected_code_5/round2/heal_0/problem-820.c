#include <stdio.h>
#include <stdbool.h>

bool check_month(int month);

int main() {
    int month;
    
    printf("Enter the month number: ");
    scanf("%d",&month);

    if(check_month(month)){
        printf("It has 28 days in a common year.\n");
    } else {
        printf("It does not have 28 days in a common year.\n");
    }

    return 0;
}

bool check_month(int month) {
    if(month < 1 || month > 12){
        printf("Invalid month number.\n");
        return false;
    } else {
        return (month == 2);
    }
}