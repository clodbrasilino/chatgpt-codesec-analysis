#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count_vowels(const char *str) {
    size_t count = 0;
    if (str == NULL) {
        return 0;
    }
    for (size_t i = 0; str[i] != '\0'; i++) {
        switch (str[i]) {
            case 'a': case 'e': case 'i': case 'o': case 'u':
            case 'A': case 'E': case 'I': case 'O': case 'U':
                count++;
                break;
            default:
                break;
        }
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t vowels = count_vowels(argv[1]);
    printf("%zu\n", vowels);

    return EXIT_SUCCESS;
}