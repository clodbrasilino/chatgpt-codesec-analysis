#include <stdio.h>
#include <string.h>

int isMonthWith31Days(char *monthName) {
    char *monthsWith31Days[] = {"January", "March", "May", "July", "August", "October", "December"};
    int i;
    for(i=0; i<7; i++) {
        if(strcmp(monthName, monthsWith31Days[i])==0)
            return 1;
    }
    return 0;
}

int main() {
    char month[10];
    printf("Enter month name: ");
    scanf("%s", month);

    if(isMonthWith31Days(month)) {
        printf("%s contains 31 days.\n", month);
    } else {
        printf("%s does not contain 31 days.\n", month);
    }

    return 0;
}
