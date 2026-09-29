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

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    size_t max_len = 4096;
    size_t argv_len = strnlen(argv[1], max_len);

    if (argv_len == max_len && argv[1][max_len] != '\0') {
        fprintf(stderr, "Error: Input string exceeds maximum allowed length.\n");
        return 1;
    }

    bool result = match_a_three_b(argv[1], max_len);

    if (result) {
        printf("Match found.\n");
    } else {
        printf("No match found.\n");
    }

    return 0;
}