#include <stdio.h>

void printSeason(int month, int day) {
    if(month < 3 || (month == 3 && day <= 20)) {
        printf("Winter\n");
    } else if(month < 6 || (month == 6 && day <= 20)) {
        printf("Spring\n");
    } else if(month < 9 || (month == 9 && day <= 22)) {
        printf("Summer\n");
    } else if(month < 12 || (month == 12 && day <= 20)) {
        printf("Autumn\n");
    } else {
        printf("Winter\n");
    }
}

int main() {
    int month, day;
    printf("Enter month and day: ");
    scanf("%d %d", &month, &day);
    printSeason(month, day);
    return 0;
}