#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int search_pattern(const char *text, const char *pattern, int *locations, int max_locations) {
    if (text == NULL || pattern == NULL || locations == NULL || max_locations <= 0) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int text_len = strlen(text);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int pattern_len = strlen(pattern);

    if (pattern_len == 0) {
        return -1;
    }

    if (pattern_len > text_len) {
        return 0;
    }

    int count = 0;
    int i;

    for (i = 0; i <= text_len - pattern_len; i++) {
        if (strncmp(text + i, pattern, pattern_len) == 0) {
            if (count < max_locations) {
                locations[count] = i;
            }
            count++;
        }
    }

    return count;
}

int main(void) {
    const char *text = "This is a test string for testing pattern search in test environment";
    const char *pattern = "test";
    int locations[10];
    int result = search_pattern(text, pattern, locations, 10);

    if (result == -1) {
        printf("Invalid input parameters\n");
        return 1;
    }

    printf("Pattern '%s' found %d times in text\n", pattern, result);

    if (result > 0) {
        printf("Locations (indices): ");
        int limit = (result < 10) ? result : 10;
        for (int i = 0; i < limit; i++) {
            printf("%d", locations[i]);
            if (i < limit - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }

    return 0;
}