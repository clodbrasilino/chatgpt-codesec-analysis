#include <stdio.h>
#include <string.h>

void convertDateFormat(char *date) {
    char temp[9];
    strncpy(temp, date, 8);
    temp[8] = '\0';
    memmove(date, date + 8, 3);
    date[3] = '-';
    memmove(date + 4, date + 11, 3);
    date[7] = '-';
    strncpy(date + 8, temp, 4);
    date[12] = '\0';
}

int main() {
    char date[] = "2023-04-01";
    convertDateFormat(date);
    printf("%s\n", date);
    return 0;
}