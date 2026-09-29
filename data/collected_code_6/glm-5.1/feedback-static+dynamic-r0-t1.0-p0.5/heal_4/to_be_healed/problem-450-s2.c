#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['practice', 'solution'], got ["exercise","practice","solution"]
  *  test case 1 failed: expected ['Python'], got ["Python","exerci","practi","soluti"]
  */

char** extract_substrings(char** strings, int count, int size) {
    if (strings == NULL || count <= 0 || size <= 0) {
        return NULL;
    }

    char** result = (char**)malloc((count + 1) * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    int valid_count = 0;
    for (int i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        size_t len = strnlen(strings[i], (size_t)size + 1);
        if (len >= (size_t)size) {
            result[valid_count] = (char*)malloc((size_t)size + 1);
            if (result[valid_count] == NULL) {
                for (int j = 0; j < valid_count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[valid_count], strings[i], (size_t)size);
            result[valid_count][size] = '\0';
            valid_count++;
        }
    }

    result[valid_count] = NULL;
    char** final_result = (char**)realloc(result, (valid_count + 1) * sizeof(char*));
    if (final_result == NULL) {
        final_result = result;
    }

    return final_result;
}

void free_extracted_strings(char** strings) {
    if (strings == NULL) {
        return;
    }

    for (int i = 0; strings[i] != NULL; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    char* input_strings[] = {
        "Python",
        "list",
        "exercises",
        "practice",
        "solution",
        NULL
    };

    int count = 0;
    while (input_strings[count] != NULL) {
        count++;
    }

    int extract_size = 9;

    char** extracted = extract_substrings(input_strings, count, extract_size);
    if (extracted == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; extracted[i] != NULL; i++) {
        printf("%s\n", extracted[i]);
    }

    free_extracted_strings(extracted);

    return 0;
}