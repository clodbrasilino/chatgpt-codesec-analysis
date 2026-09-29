#include <stdio.h>
#include <string.h>

int count_occurrences(const char *str, const char *target) {
    int count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t target_len = strlen(target);
    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (strncmp(&str[i], target, target_len) == 0) {
            count++;
            i += target_len - 1; // Move index to the end of the current match
        }
    }
    return count;
}

int main() {
    const char *input = "1. list item 1. list item 1. list item 2. list item 2. list item 2. list item";
    const char *target = "std";

    int occurrences = count_occurrences(input, target);
    printf("Occurrences of 'std' in the string: %d\n", occurrences);

    return 0;
}