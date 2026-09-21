#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

bool matches_pattern(const char *str, size_t max_len) {
    if (str == NULL) {
        return false;
    }

    size_t len = strnlen(str, max_len);

    if (len < 2 || len == max_len) {
        return false;
    }

    if (str[0] != 'a') {
        return false;
    }

    if (str[len - 1] != 'b') {
        return false;
    }

    for (size_t i = 1; i < len - 1; i++) {
        if (str[i] == '\0') {
            return false;
        }
    }

    return true;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char const * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    size_t max_len = 1024;
    
    if (strnlen(argv[1], max_len) >= max_len) {
        fprintf(stderr, "Error: Input string exceeds maximum allowed length\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s", argv[1]);

    if (matches_pattern(buffer, max_len)) {
        printf("Match\n");
    } else {
        printf("No Match\n");
    }

    return 0;
}