#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_vowels(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;
    while (*str != '\0') {
        char c = tolower((unsigned char)*str);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
        str++;
    }

    return count;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    int vowels = count_vowels(argv[1]);
    printf("%d\n", vowels);

    return 0;
}