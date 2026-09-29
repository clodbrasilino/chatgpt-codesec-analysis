#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Python'], got <no output>
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 2 failed: expected ['exercises'], got <no output>
  */

char** extract_substrings(char** strings, size_t count, size_t size, size_t* out_count) {
    if (strings == NULL || out_count == NULL) {
        return NULL;
    }

    size_t valid_count = 0;
    for (size_t i = 0; i < count; ++i) {
        if (strings[i] != NULL && strlen(strings[i]) >= size) {
            valid_count++;
        }
    }

    if (valid_count == 0) {
        *out_count = 0;
        return NULL;
    }

    char** result = (char**)malloc(valid_count * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    size_t res_idx = 0;
    for (size_t i = 0; i < count; ++i) {
        if (strings[i] != NULL && strlen(strings[i]) >= size) {
            result[res_idx] = (char*)malloc((size + 1) * sizeof(char));
            if (result[res_idx] == NULL) {
                for (size_t j = 0; j < res_idx; ++j) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            strncpy(result[res_idx], strings[i], size);
            result[res_idx][size] = '\0';
            res_idx++;
        }
    }

    *out_count = valid_count;
    return result;
}

int main(void) {
    size_t test_count = 3;
    struct {
        char** strings;
        size_t count;
        size_t size;
        char** expected;
        size_t expected_count;
    } test_cases[3];

    char* tc0[] = {"practice", "solution"};
    test_cases[0].strings = tc0;
    test_cases[0].count = 2;
    test_cases[0].size = 8;
    char* exp0[] = {"practice", "solution"};
    test_cases[0].expected = exp0;
    test_cases[0].expected_count = 2;

    char* tc1[] = {"Python"};
    test_cases[1].strings = tc1;
    test_cases[1].count = 1;
    test_cases[1].size = 6;
    char* exp1[] = {"Python"};
    test_cases[1].expected = exp1;
    test_cases[1].expected_count = 1;

    char* tc2[] = {"exercises"};
    test_cases[2].strings = tc2;
    test_cases[2].count = 1;
    test_cases[2].size = 9;
    char* exp2[] = {"exercises"};
    test_cases[2].expected = exp2;
    test_cases[2].expected_count = 1;

    for (size_t t = 0; t < test_count; ++t) {
        size_t out_count = 0;
        char** extracted = extract_substrings(test_cases[t].strings, test_cases[t].count, test_cases[t].size, &out_count);

        if (extracted != NULL) {
            for (size_t i = 0; i < out_count; ++i) {
                printf("%s\n", extracted[i]);
                free(extracted[i]);
            }
            free(extracted);
        }
    }

    return 0;
}