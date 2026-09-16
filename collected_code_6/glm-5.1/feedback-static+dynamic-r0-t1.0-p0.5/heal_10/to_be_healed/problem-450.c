#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Python'], got <no output>
  *  test case 2 failed: expected ['exercises'], got <no output>
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  */

char** extract_substrings(char** strings, int target_length) {
    if (strings == NULL || target_length < 0) {
        return NULL;
    }

    int count = 0;
    while (strings[count] != NULL) {
        count++;
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

        size_t len = strlen(strings[i]);
        if (len == (size_t)target_length) {
            char* str_copy = (char*)malloc(len + 1);
            if (str_copy == NULL) {
                for (int j = 0; j < valid_count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            strcpy(str_copy, strings[i]);
            result[valid_count++] = str_copy;
        }
    }

    result[valid_count] = NULL;
    
    char** trimmed_result = (char**)realloc(result, (valid_count + 1) * sizeof(char*));
    if (trimmed_result != NULL) {
        return trimmed_result;
    }

    return result;
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

    int test_lengths[] = {8, 9, 6};
    int num_tests = sizeof(test_lengths) / sizeof(test_lengths[0]);

    for (int t = 0; t < num_tests; t++) {
        char** extracted = extract_substrings(input_strings, test_lengths[t]);
        if (extracted == NULL) {
            fprintf(stderr, "Memory allocation failed or invalid size\n");
            continue;
        }

        for (int i = 0; extracted[i] != NULL; i++) {
            printf("%s\n", extracted[i]);
        }

        free_extracted_strings(extracted);
    }

    return 0;
}