#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_vowels(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;
    const char *p = str;
    while (*p != '\0') {
        char c = tolower((unsigned char)*p);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
        p++;
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
        return 1;
    }

    int vowels = count_vowels(argv[1]);
    printf("%d\n", vowels);

    return 0;
}