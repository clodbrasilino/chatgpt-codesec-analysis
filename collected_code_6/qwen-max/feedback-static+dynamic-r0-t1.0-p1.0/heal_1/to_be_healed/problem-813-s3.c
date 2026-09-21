#include <stdio.h>
#include <string.h>

size_t string_length(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    return strlen(str);
}

int main() {
    const char *test_string = "Hello, World!";
    printf("Length: %zu\n", string_length(test_string));
    return 0;
}