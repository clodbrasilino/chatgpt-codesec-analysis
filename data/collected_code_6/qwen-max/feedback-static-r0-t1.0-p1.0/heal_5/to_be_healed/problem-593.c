#include <stdio.h>
#include <string.h>

void remove_leading_zeroes(char *ip) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[16] = "";
    char *part;
    int index = 0;

    part = strtok(ip, ".");
    while (part != NULL && index < sizeof(temp) - 2) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(part) > 1 && part[0] == '0') {
            size_t len;
            /* Possible weaknesses found:
             *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            for (len = 0; part[len] == '0' && len < strlen(part) - 1; len++);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            len = strlen(part + len);
            if (index + len < sizeof(temp) - 2) {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(temp + index, part + len, len);
                temp[index + len + 1] = '\0';
                index += len;
            }
        } else {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(part);
            if (index + len < sizeof(temp) - 2) {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(temp + index, part, len);
                temp[index + len + 1] = '\0';
                index += len;
            }
        }
        part = strtok(NULL, ".");
        if (part != NULL && index < sizeof(temp) - 2) {
            temp[index++] = '.';
            temp[index] = '\0';
        }
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(temp) < strlen(ip)) {
        snprintf(ip, sizeof(temp), "%s", temp);
    }
}

int main() {
    char ip[] = "192.168.001.001";
    remove_leading_zeroes(ip);
    printf("%s\n", ip);
    return 0;
}