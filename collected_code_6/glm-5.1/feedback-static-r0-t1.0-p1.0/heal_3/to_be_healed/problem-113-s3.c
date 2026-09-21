#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

int is_integer(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t i = 0;

    if (str[i] == '+' || str[i] == '-') {
        i++;
    }

    if (str[i] == '\0') {
        return 0;
    }

    while (str[i] != '\0') {
        if (!isdigit((unsigned char)str[i])) {
            return 0;
        }
        i++;
    }

    return 1;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    if (is_integer(argv[1])) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}