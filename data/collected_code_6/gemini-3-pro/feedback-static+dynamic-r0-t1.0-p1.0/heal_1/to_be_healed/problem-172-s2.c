#include <stdio.h>
#include <string.h>

int find_std_occurrences(const char *str) {
    if (str == NULL) {
        return -1;
    }

    int count = 0;
    const char *ptr = str;
    const char *target = "std";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t target_len = strlen(target);

    while ((ptr = strstr(ptr, target)) != NULL) {
        count++;
        ptr += target_len;
    }

    return count;
}

int main(void) {
    const char *test_string = "1. list item 1. list item 1. list item 2. list item 2. list item 2. list item";
    int occurrences = find_std_occurrences(test_string);

    if (occurrences >= 0) {
        printf("Occurrences of 'std': %d\n", occurrences);
    } else {
        printf("Error processing string.\n");
    }

    return 0;
}