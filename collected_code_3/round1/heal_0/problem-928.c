#include <stdio.h>
#include <string.h>

void convertDate(char* date, char* newDate) {
    strncpy(newDate, &date[8], 2);
    strncpy(&newDate[2], &date[4], 4);
    strncpy(&newDate[6], &date[0], 4);
    newDate[10] = '\0';
}

int main() {
    char date[11] = "2022-12-31";
    char newDate[11];
    convertDate(date, newDate);
    printf("Original Date: %s\n", date);
    printf("Converted Date: %s\n", newDate);
    return 0;
}