#include <stdio.h>
#include <string.h>

size_t count_characters(const char *str) {
    if (str == NULL) {
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    return strlen(str);
}

int main() {
    const char *test_string = "Hello, world!";
    size_t length = count_characters(test_string);
    printf("Total characters: %zu\n", length);
    return 0;
}