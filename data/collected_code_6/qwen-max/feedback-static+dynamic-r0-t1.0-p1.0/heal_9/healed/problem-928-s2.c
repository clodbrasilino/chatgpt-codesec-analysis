#include <stdio.h>
#include <string.h>

void convertDateFormat(char *date) {
    if (strnlen(date, 9) == 8) {
        char temp[9];
        strncpy(temp, date, 8);
        temp[8] = '\0';

        if (strnlen(date, 12) >= 11) {
            memmove(date, date + 8, 3);
            memmove(date + 3, date + 5, 3);

            if (strnlen(temp, 9) >= 2) {
                size_t len = strnlen(temp, 9);
                if (len <= 3) {
                    memcpy(date + 6, temp, 2);
                }
            }
            date[10] = '\0';
        }
    }
}

int main() {
    char date[] = "2023-04-01";
    convertDateFormat(date);
    printf("%s\n", date);
    return 0;
}