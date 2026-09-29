#include <stdio.h>
#include <string.h>

int count_std_occurrences(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;
    const char *target = "std";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t target_len = strlen(target);
    const char *ptr = str;

    while ((ptr = strstr(ptr, target)) != NULL) {
        count++;
        ptr += target_len;
    }

    return count;
}

int main(void) {
    const char *test_string = "1. list item 1. list item 1. list item std 2. list item 2. list item std 2. list item std";
    
    int occurrences = count_std_occurrences(test_string);
    
    printf("Occurrences of 'std': %d\n", occurrences);
    
    return 0;
}