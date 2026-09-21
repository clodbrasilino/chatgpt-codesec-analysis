#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int search_pattern(const char *text, const char *pattern, int *locations, int max_locations) {
    /* Possible weaknesses found:
     *  Assuming condition 'max_locations<=0' is false
     */
    if (text == NULL || pattern == NULL || locations == NULL || max_locations <= 0) {
        return -1;
    }

    /* Possible weaknesses found:
     *  Condition 'max_locations>0' is always true [knownConditionTrueFalse]
     *  Condition 'max_locations>0' is always true
     *  Uninitialized variable: text_len [legacyUninitvar]
     */
    size_t text_len = strnlen(text, max_locations > 0 ? text_len + 1 : 1);
    if (text_len == 0 && text[0] != '\0') {
        size_t safe_len = 0;
        while (safe_len < (size_t)max_locations && text[safe_len] != '\0') {
            safe_len++;
        }
        text_len = safe_len;
    } else {
        text_len = strnlen(text, text_len + 1);
    }
    
    size_t pattern_len = strnlen(pattern, text_len + 1);
    if (pattern_len == 0 && pattern[0] != '\0') {
        size_t safe_len = 0;
        while (safe_len <= text_len && pattern[safe_len] != '\0') {
            safe_len++;
        }
        pattern_len = safe_len;
    } else {
        pattern_len = strnlen(pattern, pattern_len + 1);
    }

    if (pattern_len == 0) {
        return -1;
    }

    if (pattern_len > text_len) {
        return 0;
    }

    int count = 0;
    size_t i;

    for (i = 0; i <= text_len - pattern_len; i++) {
        if (strncmp(text + i, pattern, pattern_len) == 0) {
            if (count < max_locations) {
                locations[count] = (int)i;
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