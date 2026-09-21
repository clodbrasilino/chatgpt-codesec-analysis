#include <stdio.h>
#include <string.h>

void convertDateFormat(char *date, size_t len) {
    if (len < 10) return;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[11];
    snprintf(temp, sizeof(temp), "%.*s", (int)len, date);
    memmove(date + 3, date + 8, 3);
    date[3] = '-';
    memmove(date + 7, date + 11, 3);
    date[7] = '-';
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(date + 8, temp, 4);
    date[12] = '\0';
}

int main() {
    char date[] = "2023-04-01";
    convertDateFormat(date, sizeof(date) - 1);
    printf("%s\n", date);
    return 0;
}