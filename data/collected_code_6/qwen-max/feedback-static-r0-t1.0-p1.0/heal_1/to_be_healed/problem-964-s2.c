#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_length_even(const char *word) {
    if (word == NULL) {
        return false;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(word);
    return (len % 2) == 0;
}

int main() {
    const char *test_word1 = "even";
    const char *test_word2 = "odd";
    
    printf("%s: %s\n", test_word1, is_length_even(test_word1) ? "Even" : "Odd");
    printf("%s: %s\n", test_word2, is_length_even(test_word2) ? "Even" : "Odd");

    return 0;
}