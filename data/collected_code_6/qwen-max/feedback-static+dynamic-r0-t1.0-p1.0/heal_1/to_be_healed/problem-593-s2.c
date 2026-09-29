#include <stdio.h>
#include <string.h>

void remove_leading_zeroes(char *ip) {
    char *token, *context;
    token = strtok_r(ip, ".", &context);
    while (token) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(token) > 1 && *token == '0') {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            memmove(token, token + 1, strlen(token));
        }
        token = strtok_r(NULL, ".", &context);
    }
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip[16] = "192.168.01.01";
    remove_leading_zeroes(ip);
    printf("%s\n", ip);
    return 0;
}