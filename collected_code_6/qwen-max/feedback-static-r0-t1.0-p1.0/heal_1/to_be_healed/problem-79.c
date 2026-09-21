#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_odd_length(const char *word) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(word);
    return length % 2 != 0;
}

int main() {
    const char *word = "example";
    if (is_odd_length(word)) {
        printf("%s has an odd length.\n", word);
    } else {
        printf("%s has an even length.\n", word);
    }
    return 0;
}