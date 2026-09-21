#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_leading_zeroes(char *ip) {
    size_t len = strnlen(ip, 16);
    char *ip_copy = malloc(len + 1);
    if (ip_copy == NULL) return;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(ip_copy, ip, len + 1);

    char *token, *context = NULL;
    token = strtok_r(ip_copy, ".", &context);
    while (token) {
        size_t token_len = strnlen(token, 4);
        if (token_len > 1 && *token == '0') {
            memmove(token, token + 1, token_len - 1);
            token[token_len - 1] = '\0';
        }
        token = strtok_r(NULL, ".", &context);
    }

    snprintf(ip, 16, "%s", ip_copy);
    free(ip_copy);
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