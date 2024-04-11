#include <stdio.h>
#include <string.h>

int has31Days(char *month) {
    char *monthsWith31Days[] = {"January", "March", "May", "July", "August", "October", "December"};
    int i;

    for(i = 0; i < 7; i++) {
        if(strcmp(month, monthsWith31Days[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char month[10];

    printf("Enter the month name: ");
    scanf("%s", month);

    if(has31Days(month)) {
        printf("%s has 31 days\n", month);
    } else {
        printf("%s does not have 31 days\n", month);
    }

    return 0;
}