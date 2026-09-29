#include <stdio.h>
#include <string.h>

int checkDays(const char *month) {
    if(strcmp(month, "January") == 0 || strcmp(month, "March") == 0 || strcmp(month, "May") == 0 || strcmp(month, "July") == 0 || strcmp(month, "August") == 0 || strcmp(month, "October") == 0 || strcmp(month, "December") == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    char month[20] = "";
 
    printf("Enter month name: ");
    scanf("%19s", month);
    if(checkDays(month)) {
        printf("%s has 31 days.\n", month);
    }
    else {
        printf("%s does not have 31 days.\n", month);
    }
    return 0;
}