#include <stdio.h>
#include <string.h>

void convertDateFormat(char *date) {
    size_t date_len = strnlen(date, 9);
    if (date_len == 8) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char temp[9];
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(temp, date, 8);
        temp[8] = '\0';

        if (strnlen(date, 12) >= 11) {
            memmove(date, date + 8, 3);
            memmove(date + 3, date + 5, 3);

            if (strnlen(temp, 9) >= 2) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(date + 6, temp, 2);
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