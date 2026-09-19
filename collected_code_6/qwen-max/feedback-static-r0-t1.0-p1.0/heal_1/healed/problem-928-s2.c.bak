#include <stdio.h>
#include <string.h>

void convertDateFormat(char *date) {
    char temp[3] = {0};
    strncpy(temp, date, 2);
    memmove(date, date + 5, 3);
    memmove(date + 3, date + 8, 3);
    memcpy(date + 6, temp, 2);
    date[10] = '\0';
}

int main() {
    char date[] = "2023-04-01";
    convertDateFormat(date);
    printf("%s\n", date);
    return 0;
}