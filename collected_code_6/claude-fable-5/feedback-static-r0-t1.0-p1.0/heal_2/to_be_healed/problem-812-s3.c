#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096

char *abbreviate_road(const char *input)
{
    static const char pattern[] = "road";
    static const char replacement[] = "rd.";
    size_t pattern_len;
    size_t replacement_len;
    size_t input_len;
    size_t count;
    size_t result_len;
    size_t remaining;
    const char *p;
    char *result;
    char *dest;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len == MAX_INPUT_LEN && input[MAX_INPUT_LEN] != '\0') {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Assignment 'pattern_len=sizeof(pattern)-1', assigned value is 4
     */
    pattern_len = sizeof(pattern) - 1;
    /* Possible weaknesses found:
     *  Assignment 'replacement_len=sizeof(replacement)-1', assigned value is 3
     */
    replacement_len = sizeof(replacement) - 1;

    /* Possible weaknesses found:
     *  Condition 'pattern_len==0' is always false
     *  Condition 'pattern_len==0' is always false [knownConditionTrueFalse]
     */
    if (pattern_len == 0) {
        return NULL;
    }

    count = 0;
    p = input;
    while ((p = strstr(p, pattern)) != NULL) {
        count++;
        p += pattern_len;
    }

    /* Possible weaknesses found:
     *  Condition 'replacement_len>pattern_len' is always false
     *  Condition 'replacement_len>pattern_len' is always false [knownConditionTrueFalse]
     */
    if (count > 0 && replacement_len > pattern_len) {
        size_t growth = replacement_len - pattern_len;
        if (count > (SIZE_MAX - input_len - 1) / growth) {
            return NULL;
        }
    }

    result_len = input_len + count * replacement_len - count * pattern_len;

    result = malloc(result_len + 1);
    if (result == NULL) {
        return NULL;
    }

    dest = result;
    remaining = result_len;
    p = input;
    while (*p != '\0') {
        if (strncmp(p, pattern, pattern_len) == 0) {
            if (remaining < replacement_len) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(dest, replacement, replacement_len);
            dest += replacement_len;
            remaining -= replacement_len;
            p += pattern_len;
        } else {
            if (remaining < 1) {
                free(result);
                return NULL;
            }
            *dest = *p;
            dest++;
            remaining--;
            p++;
        }
    }
    *dest = '\0';

    return result;
}

int main(void)
{
    const char *text = "Take the main road until the road forks near Elm road.";
    char *abbreviated;

    abbreviated = abbreviate_road(text);
    if (abbreviated == NULL) {
        fprintf(stderr, "Failed to abbreviate string\n");
        return EXIT_FAILURE;
    }

    if (printf("Original:    %s\n", text) < 0) {
        free(abbreviated);
        return EXIT_FAILURE;
    }

    if (printf("Abbreviated: %s\n", abbreviated) < 0) {
        free(abbreviated);
        return EXIT_FAILURE;
    }

    free(abbreviated);
    return EXIT_SUCCESS;
}