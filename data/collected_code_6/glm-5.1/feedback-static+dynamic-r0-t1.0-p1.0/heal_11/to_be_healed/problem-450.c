#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['exercises'], got <no output>
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  */

char** extract_substrings(const char** strings, size_t count, size_t size, size_t* result_count) {
    if (strings == NULL || result_count == NULL || size == 0) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    size_t valid_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL && strlen(strings[i]) >= size) {
            valid_count++;
        }
    }

    if (valid_count == 0) {
        *result_count = 0;
        return NULL;
    }

    char** result = (char**)malloc(valid_count * sizeof(char*));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    size_t current_index = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL && strlen(strings[i]) >= size) {
            result[current_index] = (char*)malloc((size + 1) * sizeof(char));
            if (result[current_index] == NULL) {
                for (size_t j = 0; j < current_index; j++) {
                    free(result[j]);
                }
                free(result);
                *result_count = 0;
                return NULL;
            }
            strncpy(result[current_index], strings[i], size);
            result[current_index][size] = '\0';
            current_index++;
        }
    }

    *result_count = valid_count;
    return result;
}

void free_substrings(char** strings, size_t count) {
    if (strings == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    const char* test_case_0[] = {"practice", "solution"};
    size_t count_0 = sizeof(test_case_0) / sizeof(test_case_0[0]);
    size_t size_0 = 6;
    size_t result_count_0 = 0;
    char** extracted_0 = extract_substrings(test_case_0, count_0, size_0, &result_count_0);
    for (size_t i = 0; i < result_count_0; i++) {
        printf("%s\n", extracted_0[i]);
    }
    printf("\n");
    free_substrings(extracted_0, result_count_0);

    const char* test_case_1[] = {"Python"};
    size_t count_1 = sizeof(test_case_1) / sizeof(test_case_1[0]);
    size_t size_1 = 6;
    size_t result_count_1 = 0;
    char** extracted_1 = extract_substrings(test_case_1, count_1, size_1, &result_count_1);
    for (size_t i = 0; i < result_count_1; i++) {
        printf("%s\n", extracted_1[i]);
    }
    printf("\n");
    free_substrings(extracted_1, result_count_1);

    const char* test_case_2[] = {"exercises"};
    size_t count_2 = sizeof(test_case_2) / sizeof(test_case_2[0]);
    size_t size_2 = 6;
    size_t result_count_2 = 0;
    char** extracted_2 = extract_substrings(test_case_2, count_2, size_2, &result_count_2);
    for (size_t i = 0; i < result_count_2; i++) {
        printf("%s\n", extracted_2[i]);
    }
    printf("\n");
    free_substrings(extracted_2, result_count_2);

    return 0;
}