#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool match_a_followed_by_zero_or_one_b(const char *str) {
    if (str == NULL || str[0] != 'a') {
        return false;
    }

    if (str[1] == 'b') {
        return str[2] == '\0';
    }

    return str[1] == '\0';
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    size_t len = strnlen(argv[1], 3);
    if (len == 3 && argv[1][2] != '\0') {
        fprintf(stderr, "Error: String length exceeds bounds\n");
        return 1;
    }

    bool result = match_a_followed_by_zero_or_one_b(argv[1]);
    printf("%d\n", result);

    return 0;
}