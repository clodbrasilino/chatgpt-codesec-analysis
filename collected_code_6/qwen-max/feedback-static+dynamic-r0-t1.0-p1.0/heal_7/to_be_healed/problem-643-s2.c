#include <stdio.h>
#include <string.h>
#include <ctype.h>

int contains_z_in_middle(const char *word, size_t len) {
    for (int i = 1; i < len - 1; ++i) {
        if (word[i] == 'z' && isalpha((unsigned char)word[i-1]) && isalpha((unsigned char)word[i+1])) {
            return 1;
        }
    }
    return 0;
}

int main() {
    const char *test_words[] = {"amazing", "zebra", "lazy", "zipped", "pizzazz", "fizzled"};
    int num_words = sizeof(test_words) / sizeof(test_words[0]);

    for (int i = 0; i < num_words; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(test_words[i]);
        if (len > 2 && contains_z_in_middle(test_words[i], len)) {
            printf("%s: Found 'z' in the middle\n", test_words[i]);
        } else {
            printf("%s: No 'z' found in the middle\n", test_words[i]);
        }
    }

    return 0;
}