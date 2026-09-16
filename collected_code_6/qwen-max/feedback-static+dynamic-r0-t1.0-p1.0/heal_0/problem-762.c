#include <stdio.h>
#include <stdbool.h>

bool hasThirtyDays(int month) {
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return true;
    }
    return false;
}

int main() {
    int month;
    printf("Enter month number: ");
    if (scanf("%d", &month) != 1 || month < 1 || month > 12) {
        printf("Invalid input\n");
        return 1;
    }

    if (hasThirtyDays(month)) {
        printf("The month has 30 days.\n");
    } else {
        printf("The month does not have 30 days.\n");
    }

    return 0;
}