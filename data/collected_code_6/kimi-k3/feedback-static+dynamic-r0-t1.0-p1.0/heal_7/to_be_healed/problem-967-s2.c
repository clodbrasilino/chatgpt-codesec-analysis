#include <stdio.h>
#include <string.h>
#include <ctype.h>

int contains_all_vowels(const char *str, size_t max_len) {
    int vowel_flags[5] = {0};
    size_t i;
    size_t len = 0;

    if (str == NULL || max_len == 0) {
        return 0;
    }

    while (len < max_len && str[len] != '\0') {
        len++;
    }

    for (i = 0; i < len; i++) {
        char ch = tolower((unsigned char)str[i]);
        switch (ch) {
            case 'a':
                vowel_flags[0] = 1;
                break;
            case 'e':
                vowel_flags[1] = 1;
                break;
            case 'i':
                vowel_flags[2] = 1;
                break;
            case 'o':
                vowel_flags[3] = 1;
                break;
            case 'u':
                vowel_flags[4] = 1;
                break;
            default:
                break;
        }
    }

    for (i = 0; i < 5; i++) {
        if (vowel_flags[i] == 0) {
            return 0;
        }
    }

    return 1;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    int result;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = contains_all_vowels(buffer, sizeof(buffer));

    if (result == 1) {
        printf("The string contains all vowels.\n");
    } else {
        printf("The string does not contain all vowels.\n");
    }

    return 0;
}