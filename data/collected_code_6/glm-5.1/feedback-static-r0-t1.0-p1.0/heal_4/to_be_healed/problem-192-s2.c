#include <stdio.h>
#include <string.h>
#include <ctype.h>

int check_string(const char *str, size_t maxlen) {
    if (str == NULL) {
        return 0;
    }

    int has_letter = 0;
    int has_number = 0;
    const char *end = str + maxlen;

    for (const char *p = str; *p != '\0' && p < end; p++) {
        if (isalpha((unsigned char)*p)) {
            has_letter = 1;
        } else if (isdigit((unsigned char)*p)) {
            has_number = 1;
        }

        if (has_letter && has_number) {
            return 1;
        }
    }

    return 0;
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

    int result = check_string(argv[1], 4096);

    if (result) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}