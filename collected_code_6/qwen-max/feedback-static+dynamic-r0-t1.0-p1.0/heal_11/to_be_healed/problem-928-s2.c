#include <stdio.h>
#include <string.h>

void convertDateFormat(char *date) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  Assuming that condition 'strlen(date)==8' is not redundant
     */
    if (strlen(date) == 8) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char temp[9];
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(temp, date, 8);
        temp[8] = '\0';

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         *  Condition 'strlen(date)>=11' is always false
         *  Condition 'strlen(date)>=11' is always false [knownConditionTrueFalse]
         */
        if (strlen(date) >= 11) {
            memmove(date + 3, date + 5, 3);
            date[6] = date[0];
            date[7] = date[1];

            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            if (strlen(temp) >= 2) {
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                size_t len = strlen(temp);
                if (len <= 3) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(date + 6, temp, 2);
                }
            }
            date[8] = '-';
            date[9] = date[2];
            date[10] = date[3];
            date[11] = '\0';
        }
    }
}

int main() {
    char date[] = "2023-04-01";
    convertDateFormat(date);
    printf("%s\n", date);
    return 0;
}