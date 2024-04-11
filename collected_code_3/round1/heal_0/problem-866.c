#include <stdio.h>
#include <string.h>

int has31Days(char *month) {
    if (strcmp(month, "January") == 0 || strcmp(month, "March") == 0 || strcmp(month, "May") == 0 || strcmp(month, "July") == 0 || strcmp(month, "August") == 0 || strcmp(month, "October") == 0 || strcmp(month, "December") == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char month[10];
    printf("Enter the month: ");
    scanf("%s", month);
    if (has31Days(month)) {
        printf("The month %s has 31 days.\n", month);
    } else {
        printf("The month %s does not have 31 days.\n", month);
    }
    return 0;
}