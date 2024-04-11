#include <stdio.h>
#include <string.h>

int hasThirtyDays(char *month) {
    if (strcmp(month, "April") == 0 || strcmp(month, "June") == 0 || strcmp(month, "September") == 0 || strcmp(month, "November") == 0) {
        return 1;
    }
    return 0;
}

int main() {
    char month[20];
    printf("Enter the month name: ");
    scanf("%s", month);
    if (hasThirtyDays(month)) {
        printf("%s has 30 days.\n", month);
    } else {
        printf("%s does not have 30 days.\n", month);
    }
    return 0;
}