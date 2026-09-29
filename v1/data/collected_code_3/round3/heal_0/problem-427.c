#include <stdio.h>
#include <string.h>

void convertDateFormat(char* date, char* newDate) {
    strncpy(newDate, &date[8], 2);
    strncpy(&newDate[2], "-", 1);
    strncpy(&newDate[3], &date[5], 2);
    strncpy(&newDate[5], "-", 1);
    strncpy(&newDate[6], &date[0], 4);
    newDate[10] = '\0';
}

int main() {
    char date[11] = "2022-12-31";
    char newDate[11];
    convertDateFormat(date, newDate);
    printf("Original date: %s\n", date);
    printf("Converted date: %s\n", newDate);
    return 0;
}