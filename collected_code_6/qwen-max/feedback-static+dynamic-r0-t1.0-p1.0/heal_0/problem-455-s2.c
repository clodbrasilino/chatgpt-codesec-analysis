#include <stdbool.h>
#include <stdio.h>

bool has31Days(int month) {
    return month == 1 || month == 3 || month == 5 || month == 7 ||
           month == 8 || month == 10 || month == 12;
}

int main() {
    int month;
    printf("Enter a month number (1-12): ");
    if (scanf("%d", &month) != 1 || month < 1 || month > 12) {
        printf("Invalid input. Please enter a valid month number (1-12).\n");
        return 1;
    }

    if (has31Days(month)) {
        printf("The month has 31 days.\n");
    } else {
        printf("The month does not have 31 days.\n");
    }

    return 0;
}