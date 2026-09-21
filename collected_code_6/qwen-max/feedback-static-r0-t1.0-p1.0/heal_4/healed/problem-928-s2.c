#include <stdio.h>
#include <string.h>

void convertDateFormat(char *date) {
    char temp[11];
    if (strlen(date) >= 10) {
        snprintf(temp, sizeof(temp), "%s", date);
        memmove(date + 3, date + 8, 3);
        date[3] = '-';
        memmove(date + 7, date + 11, 3);
        date[7] = '-';
        strncpy(date + 8, temp, 4);
        date[12] = '\0';
    }
}

int main() {
    char date[] = "2023-04-01";
    convertDateFormat(date);
    printf("%s\n", date);
    return 0;
}