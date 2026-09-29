#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool match_a_three_b(const char *str, size_t max_len) {
    if (str == NULL) {
        return false;
    }

    size_t len = strnlen(str, max_len);
    if (len < 4) {
        return false;
    }

    const char *end = str + len - 3;

    for (const char *p = str; p <= end; p++) {
        if (p[0] == 'a' && p[1] == 'b' && p[2] == 'b' && p[3] == 'b') {
            return true;
        }
    }

    return false;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    bool result = match_a_three_b(argv[1], 4096);

    if (result) {
        printf("Match found.\n");
    } else {
        printf("No match found.\n");
    }

    return 0;
}