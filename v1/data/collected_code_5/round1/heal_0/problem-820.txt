#include <stdio.h>
#include <stdbool.h>

bool has28Days(int month) {
    if(month < 1 || month > 12) {
        return false;
    }
    return (month == 2);
}

int main() {
    int month;
    printf("Enter month number (1-12): ");
    scanf("%d", &month);

    if(has28Days(month)) {
        printf("This month can have 28 days.\n");
    } else {
        

        printf("This month cannot have 28 days.\n");
    }

    return 0;
}