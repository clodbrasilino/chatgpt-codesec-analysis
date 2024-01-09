#include <stdio.h>
#include <string.h>

void convertDateFormat(char* date) {
    char temp[11];
    strncpy(temp, date, 2); // Extract day
    temp[2] = '-';
    strncpy(temp + 3, date + 5, 2); // Extract month
    temp[5] = '-';
    strncpy(temp + 6, date + 0, 4); // Extract year
    temp[10] = '\0';

    strcpy(date, temp); // Copy back to original string
}

int main() {
    char date[11] = "yyyy-mm-dd";
    printf("Enter date in yyyy-mm-dd format: ");
    scanf("%s", date);

    convertDateFormat(date);
    printf("Converted date: %s\n", date);

    return 0;
}