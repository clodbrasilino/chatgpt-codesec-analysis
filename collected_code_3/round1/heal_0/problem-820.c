#include <stdio.h>
#include <stdbool.h>

bool isFebruary(int month) {
    if(month == 2) {
        return true;
    } else {
        return false;
    }
}

int main() {
    int month;
    printf("Enter month number: ");
    scanf("%d", &month);
    if(isFebruary(month)) {
        printf("This month can have 28 days.\n");
    } else {
        printf("This month cannot have 28 days.\n");
    }
    return 0;
}