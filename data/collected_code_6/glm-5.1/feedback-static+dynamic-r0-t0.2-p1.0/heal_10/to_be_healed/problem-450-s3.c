#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['practice', 'solution'], got ["exercise","practice","solution"]
  *  test case 1 failed: expected ['Python'], got ["Python","exerci","practi","soluti"]
  */

char** extract_substrings(const char** strings, size_t count, size_t size) {
    if (strings == NULL || count == 0 || size == 0) {
        return NULL;
    }

    char** result = (char**)malloc((count + 1) * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    size_t valid_count = 0;

    for (size_t i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            for (size_t j = 0; j < valid_count; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        size_t len = strnlen(strings[i], size);
        
        if (len == size) {
            result[valid_count] = (char*)malloc((size + 1) * sizeof(char));
            if (result[valid_count] == NULL) {
                for (size_t j = 0; j < valid_count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[valid_count], strings[i], size);
            result[valid_count][size] = '\0';
            valid_count++;
        }
    }

    result[valid_count] = NULL;

    char** trimmed_result = (char**)realloc(result, (valid_count + 1) * sizeof(char*));
    if (trimmed_result != NULL) {
        result = trimmed_result;
    }

    return result;
}

void free_extracted_strings(char** strings) {
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; strings[i] != NULL; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main(void) {
    const char* input_strings[] = {
        "Python",
        "list",
        "exercises",
        "practice",
        "solution"
    };
    size_t count = sizeof(input_strings) / sizeof(input_strings[0]);
    size_t extract_sizes[] = {8, 9, 5};
    size_t num_tests = sizeof(extract_sizes) / sizeof(extract_sizes[0]);

    for (size_t t = 0; t < num_tests; t++) {
        size_t size = extract_sizes[t];
        char** extracted = extract_substrings(input_strings, count, size);
        if (extracted == NULL) {
            return EXIT_FAILURE;
        }

        printf("Extract size %zu: [", size);
        for (size_t i = 0; extracted[i] != NULL; i++) {
            printf("\"%s\"", extracted[i]);
            if (extracted[i + 1] != NULL) {
                printf(", ");
            }
        }
        printf("]\n");

        free_extracted_strings(extracted);
    }

    return EXIT_SUCCESS;
}