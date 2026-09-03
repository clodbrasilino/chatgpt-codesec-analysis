#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['exercises'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  */

char **extract_strings(const char *const *input, size_t input_count, size_t *output_count) {
    *output_count = 0;
    if (input == NULL || input_count == 0) return NULL;

    char **result = (char **)malloc(input_count * sizeof(char *));
    if (result == NULL) return NULL;

    for (size_t i = 0; i < input_count; ++i) {
        result[i] = (char *)malloc(strlen(input[i]) + 1);
        if (result[i] == NULL) {
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        strcpy(result[i], input[i]);
    }

    *output_count = input_count;
    return result;
}

void free_strings(char **strings, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    const char *input0[] = {"practice", "solution"};
    size_t input_count0 = sizeof(input0) / sizeof(input0[0]);
    size_t output_count0;

    const char *input1[] = {"Python"};
    size_t input_count1 = sizeof(input1) / sizeof(input1[0]);
    size_t output_count1;

    const char *input2[] = {"exercises"};
    size_t input_count2 = sizeof(input2) / sizeof(input2[0]);
    size_t output_count2;

    char **result0 = extract_strings(input0, input_count0, &output_count0);
    if (result0 != NULL) {
        for (size_t i = 0; i < output_count0; ++i) {
            printf("%s\n", result0[i]);
        }
        free_strings(result0, output_count0);
    } else {
        printf("Failed to allocate memory.\n");
    }

    char **result1 = extract_strings(input1, input_count1, &output_count1);
    if (result1 != NULL) {
        for (size_t i = 0; i < output_count1; ++i) {
            printf("%s\n", result1[i]);
        }
        free_strings(result1, output_count1);
    } else {
        printf("Failed to allocate memory.\n");
    }

    char **result2 = extract_strings(input2, input_count2, &output_count2);
    if (result2 != NULL) {
        for (size_t i = 0; i < output_count2; ++i) {
            printf("%s\n", result2[i]);
        }
        free_strings(result2, output_count2);
    } else {
        printf("Failed to allocate memory.\n");
    }

    return 0;
}