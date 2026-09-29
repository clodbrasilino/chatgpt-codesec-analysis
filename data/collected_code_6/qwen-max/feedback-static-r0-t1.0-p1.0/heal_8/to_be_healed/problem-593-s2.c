#include <stdio.h>
#include <string.h>

void remove_leading_zeroes(char *ip, size_t ip_len) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char new_ip[128] = "";
    char *new_ip_ptr = new_ip;
    char *token, *context;

    token = strtok_r(ip, ".", &context);
    while (token) {
        size_t len = strnlen(token, 16);
        if (len > 1 && *token == '0') {
            memmove(token, token + 1, len - 1);
            *(token + len - 2) = '\0';
        }
        len = strnlen(token, 16);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(new_ip) + len + 1 < sizeof(new_ip)) {
            memmove(new_ip_ptr, token, len);
            new_ip_ptr += len;
            *new_ip_ptr++ = '.';
        }
        token = strtok_r(NULL, ".", &context);
    }
    if (new_ip_ptr > new_ip) {
        *(new_ip_ptr - 1) = '\0';
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(new_ip) < ip_len) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(ip, new_ip, ip_len - 1);
        ip[ip_len - 1] = '\0';
    } else {
        ip[0] = '\0';
    }
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip[46] = "192.168.01.01";
    remove_leading_zeroes(ip, sizeof(ip));
    printf("%s\n", ip);
    return 0;
}