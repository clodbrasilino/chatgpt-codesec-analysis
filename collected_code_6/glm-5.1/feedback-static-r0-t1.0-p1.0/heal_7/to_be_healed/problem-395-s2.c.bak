#include <stdio.h>
#include <string.h>

#define MAX_CHAR 256

char find_first_non_repeated(const char *str) {
    size_t len = strlen(str);
    if (len == 0) return '\0';

    unsigned int counts[MAX_CHAR] = {0};

    for (size_t i = 0; i < len; ++i) {
        counts[(unsigned char)str[i]]++;
    }

    for (size_t i = 0; i < len; ++i) {
        if (counts[(unsigned char)str[i]] == 1) {
            return str[i];
        }
    }

    return '\0';
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char result = find_first_non_repeated(argv[1]);

    if (result == '\0') {
        printf("No non-repeated character found.\n");
    } else {
        printf("%c\n", result);
    }

    return 0;
}