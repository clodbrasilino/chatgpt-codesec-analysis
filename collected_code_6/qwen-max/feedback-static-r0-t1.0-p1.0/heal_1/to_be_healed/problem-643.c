#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool contains_z_not_start_end(const char *word) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(word);
    if (len < 3) return false;
    for (size_t i = 1; i < len - 1; ++i) {
        if (word[i] == 'z' && isalpha(word[i-1]) && isalpha(word[i+1])) {
            return true;
        }
    }
    return false;
}

int main(void) {
    const char *test_words[] = {"zebra", "lazy", "zany", "pizzazz", "amaze", "fizz"};
    for (size_t i = 0; i < sizeof(test_words) / sizeof(test_words[0]); ++i) {
        if (contains_z_not_start_end(test_words[i])) {
            printf("%s: true\n", test_words[i]);
        } else {
            printf("%s: false\n", test_words[i]);
        }
    }
    return 0;
}