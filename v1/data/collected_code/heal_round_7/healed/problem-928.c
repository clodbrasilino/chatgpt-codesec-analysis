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
    memset(temp, 0, DATE_SIZE);

    date[DATE_SIZE - 1] = '\0';

    memcpy(temp, date + 8, 2);
    temp[2] = '-';

    memcpy(temp + 3, date + 5, 2);
    temp[5] = '-';

    memcpy(temp + 6, date, 4);
    temp[DATE_SIZE - 1] = '\0';

    memcpy(date, temp, DATE_SIZE);
    date[DATE_SIZE - 1] = '\0';
}

int main() {
    char date[DATE_SIZE];

    printf("Enter date in yyyy-mm-dd format: ");

    if(scanf(DATE_INPUT_FORMAT, date) != 1) {
        return 1;
    }

    date[DATE_SIZE - 1] = '\0';

    convertDateFormat(date);

    printf("Converted date: %s\n", date);

    return 0;
}