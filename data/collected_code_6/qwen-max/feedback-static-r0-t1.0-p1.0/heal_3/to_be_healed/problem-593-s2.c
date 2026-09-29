#include <stdio.h>
#include <string.h>

void remove_leading_zeroes(char *ip) {
    char *token, *context, *new_ip;
    new_ip = ip;
    token = strtok_r(ip, ".", &context);
    while (token) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(token);
        if (len > 1 && *token == '0') {
            memmove(token, token + 1, len - 1);
            *(token + len - 1) = '\0';
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        len = strlen(token);
        memmove(new_ip, token, len);
        new_ip += len;
        *new_ip++ = '.';
        token = strtok_r(NULL, ".", &context);
    }
    *(new_ip - 1) = '\0'; // Remove the last added dot
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