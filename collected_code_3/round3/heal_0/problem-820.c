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
    printf("Enter a month number: ");
    scanf("%d", &month);
    if(isFebruary(month)) {
        printf("This month can have 28 days.\n");
    } else {
        printf("This month does not have 28 days.\n");
    }
    return 0;
}