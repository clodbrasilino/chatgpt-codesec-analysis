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
    while (part && index < sizeof(temp) - 2) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(part) > 1 && part[0] == '0' && part[1] != '\0') {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(part);
            for (size_t i = 0; i < len; i++) {
                if (part[i] == '0' && i + 1 < len) {
                    continue;
                }
                size_t new_len = len - i;
                if (index + new_len < sizeof(temp) - 2) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(temp + index, part + i, new_len);
                    temp[index + new_len] = '\0';
                    index += new_len;
                    break;
                } else {
                    break;
                }
            }
        } else {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(part);
            if (index + len < sizeof(temp) - 2) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(temp + index, part, len);
                temp[index + len] = '\0';
                index += len;
            } else {
                break;
            }
        }
        part = strtok(NULL, ".");
        if (part && index < sizeof(temp) - 2) {
            temp[index++] = '.';
            temp[index] = '\0';
        }
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(temp) < strlen(ip)) {
        snprintf(ip, sizeof(temp), "%s", temp);
    } else {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(ip, temp, sizeof(temp) - 1);
        ip[sizeof(temp) - 1] = '\0';
    }
}

int main() {
    char ip[] = "192.168.001.001";
    remove_leading_zeroes(ip);
    printf("%s\n", ip);
    return 0;
}