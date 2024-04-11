#include <stdio.h>
#include <string.h>

void convertDateFormat(char* date, char* newDate) {
    char year[5], month[3], day[3];

    strncpy(year, &date[0], 4);
    year[4] = '\0';
    strncpy(month, &date[5], 2);
    month[2] = '\0';
    strncpy(day, &date[8], 2);
    day[2] = '\0';

    strcpy(newDate, day);
    strcat(newDate, "-");
    strcat(newDate, month);
    strcat(newDate, "-");
    strcat(newDate, year);
}

int main() {
    char date[] = "2022-09-29";
    char newDate[11];

    convertDateFormat(date, newDate);

    printf("Original date: %s\n", date);
    printf("Converted date: %s\n", newDate);

    return 0;
}