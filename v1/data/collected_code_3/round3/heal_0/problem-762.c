#include <stdio.h>
#include <stdbool.h>

bool isThirtyDays(int month) {
    if(month == 4 || month == 6 || month == 9 || month == 11) {
        return true;
    } else {
        return false;
    }
}

int main() {
    int month;
    printf("Enter month number: ");
    scanf("%d", &month);
    if(isThirtyDays(month)) {
        printf("The month contains 30 days.\n");
    } else {
        printf("The month does not contain 30 days.\n");
    }
    return 0;
}