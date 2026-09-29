#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool has28days(char *month) {
    if (!month) {
        return false;
    }
    if (strcmp(month, "February") == 0) {
        return true;
    }
    return false;
}

int main() {
    char month[50];
    printf("Enter the name of the month: ");
    scanf("%s", month);
    if(has28days(month)) {
        printf("%s usually has 28 days\n", month);
    } else {
        printf("%s does not have 28 days\n", month);
    }
    return 0;
}