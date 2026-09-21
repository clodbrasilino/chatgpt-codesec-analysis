#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* abbreviate_road(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    const char* target = "road";
    size_t target_len = 4;
    /* Possible weaknesses found:
     *  Variable 'replacement' is assigned a value that is never used. [unreadVariable]
     *  Value stored to 'replacement' during its initialization is never read [deadcode.DeadStores]
     */
    const char* replacement = "rd.";
    /* Possible weaknesses found:
     *  Variable 'replacement_len' is assigned a value that is never used. [unreadVariable]
     */
    size_t replacement_len = 3;

    size_t i = 0;
    size_t j = 0;

    while (i < len) {
        if (tolower((unsigned char)input[i]) == 'r' && len - i >= target_len) {
            int match = 1;
            for (size_t k = 1; k < target_len; ++k) {
                if (tolower((unsigned char)input[i + k]) != target[k]) {
                    match = 0;
                    break;
                }
            }

            if (match) {
                int is_word_boundary_before = (i == 0 || !isalpha((unsigned char)input[i - 1]));
                int is_word_boundary_after = (i + target_len == len || !isalpha((unsigned char)input[i + target_len]));

                if (is_word_boundary_before && is_word_boundary_after) {
                    if (input[i] == 'R') {
                        result[j++] = 'R';
                        result[j++] = 'd';
                        result[j++] = '.';
                    } else {
                        result[j++] = 'r';
                        result[j++] = 'd';
                        result[j++] = '.';
                    }
                    i += target_len;
                    continue;
                }
            }
        }
        result[j++] = input[i++];
    }
    result[j] = '\0';

    char* final_result = (char*)realloc(result, j + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    return final_result;
}

int main(void) {
    const char* test_strings[] = {
        "The road is long.",
        "Abbey Road",
        "Broad street",
        "roadway",
        "A road.",
        NULL
    };

    for (size_t i = 0; test_strings[i] != NULL; ++i) {
        char* abbr = abbreviate_road(test_strings[i]);
        if (abbr != NULL) {
            printf("Original: '%s' -> Abbreviated: '%s'\n", test_strings[i], abbr);
            free(abbr);
        } else {
            printf("Memory allocation failed for string: '%s'\n", test_strings[i]);
        }
    }

    return 0;
}