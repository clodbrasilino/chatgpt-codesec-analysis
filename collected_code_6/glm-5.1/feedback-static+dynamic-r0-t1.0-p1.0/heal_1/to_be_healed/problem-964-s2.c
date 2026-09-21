#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_length_even(const char *word) {
    if (word == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(word);

    if (len == 0) {
        return false;
    }

    return len % 2 == 0;
}

int main(void) {
    const char *test_word = "hello";
    
    if (is_length_even(test_word)) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }

    return 0;
}