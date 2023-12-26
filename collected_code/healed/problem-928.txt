#include <stdio.h>
#include <string.h>

#define DATE_SIZE 11
#define DATE_INPUT_FORMAT "%10s"

void convertDateFormat(char* date) {
    if (date == NULL) return;

    char temp[DATE_SIZE];

    if (strlen(date) + 1 > DATE_SIZE) return;

    strncpy(temp, date + 8, 2);
    temp[2] = '-';
    strncpy(temp + 3, date + 5, 2);
    temp[5] = '-';
    strncpy(temp + 6, date, 4);
    temp[10] = '\0';

    strncpy(date, temp, DATE_SIZE);
}

int main() {
    char date[DATE_SIZE];

    printf("Enter date in yyyy-mm-dd format: ");
    if(scanf(DATE_INPUT_FORMAT, date) !=1) return 1;

    convertDateFormat(date);
    printf("Converted date: %s\n", date);

    return 0;
}