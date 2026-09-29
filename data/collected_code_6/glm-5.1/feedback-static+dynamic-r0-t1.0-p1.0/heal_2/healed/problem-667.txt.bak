#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_vowels(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        char c = tolower((unsigned char)str[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }

    return count;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    int vowels = count_vowels(argv[1]);
    printf("%d\n", vowels);

    return 0;
}