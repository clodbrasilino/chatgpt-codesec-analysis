#include <stdio.h>
#include <string.h>

int checkMonth(char *month) {
    if (strcmp(month, "April") == 0 || strcmp(month, "June") == 0 || strcmp(month, "September") == 0 || strcmp(month, "November") == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char month[20];
    printf("Enter the month name: ");
    scanf("%s", month);
    if (checkMonth(month)) {
        printf("The month %s has 30 days.\n", month);
    } else {
        printf("The month %s does not have 30 days.\n", month);
    }
    return 0;
}