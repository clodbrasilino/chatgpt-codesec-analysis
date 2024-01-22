#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DATE_SIZE 11
#define DATE_INPUT_FORMAT "%10s"

void convertDateFormat(char* date) {
    char temp[DATE_SIZE];

    if(!date || strlen(date) != DATE_SIZE - 1) {
        return;
    }

    // Ensuring the string is null-terminated before copying
    date[DATE_SIZE - 1] = '\0';

    // Copying the date in reversed format
    strncpy(temp, date + 8, 2);
    temp[2] = '-';
    strncpy(temp + 3, date + 5, 2);
    temp[5] = '-';
    strncpy(temp + 6, date, 4);
    temp[DATE_SIZE - 1] = '\0';

    // Copying back the reversed date 
    strncpy(date, temp, DATE_SIZE);
    date[DATE_SIZE - 1] = '\0';
}

int main() {
    char date[DATE_SIZE];

    printf("Enter date in yyyy-mm-dd format: ");

    if(scanf(DATE_INPUT_FORMAT, date) != 1) {
        return 1;
    }

    // Ensure the received input is null-terminated
    date[DATE_SIZE - 1] = '\0';

    convertDateFormat(date);

    printf("Converted date: %s\n", date);

    return 0;
}