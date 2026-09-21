#include <stdio.h>
#include <string.h>

char* convert_date_format(const char* date_yyyymmdd) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(date_yyyymmdd) != 10 || date_yyyymmdd[4] != '-' || date_yyyymmdd[7] != '-') {
        return "";
    }
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    static char converted_date[11];
    converted_date[0] = date_yyyymmdd[8];
    converted_date[1] = date_yyyymmdd[9];
    converted_date[2] = '-';
    converted_date[3] = date_yyyymmdd[5];
    converted_date[4] = date_yyyymmdd[6];
    converted_date[5] = '-';
    converted_date[6] = date_yyyymmdd[0];
    converted_date[7] = date_yyyymmdd[1];
    converted_date[8] = date_yyyymmdd[2];
    converted_date[9] = date_yyyymmdd[3];
    converted_date[10] = '\0';
    return converted_date;
}

int main() {
    const char* date = "2023-10-05";
    char* converted_date = convert_date_format(date);
    if (*converted_date) {
        printf("%s\n", converted_date);
    } else {
        printf("Invalid date format.\n");
    }
    return 0;
}