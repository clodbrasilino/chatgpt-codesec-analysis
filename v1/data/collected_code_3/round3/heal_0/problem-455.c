#include <stdio.h>
#include <stdbool.h>

bool has31Days(int month) {
    if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        return true;
    } else {
        return false;
    }
}

int main() {
    int month;
    printf("Enter month number: ");
    scanf("%d", &month);
    if(has31Days(month)) {
        printf("Month %d has 31 days\n", month);
    } else {
        printf("Month %d does not have 31 days\n", month);
    }
    return 0;
}