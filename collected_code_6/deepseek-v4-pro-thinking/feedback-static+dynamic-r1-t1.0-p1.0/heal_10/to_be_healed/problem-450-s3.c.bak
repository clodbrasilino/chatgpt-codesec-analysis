#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Python'], got <no output>
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 2 failed: expected ['exercises'], got <no output>
  */

char **extract_strings(const char *input[], size_t input_count, size_t target_len, size_t *out_count)
{
    char **result;
    size_t i, j, k;
    size_t len;
    char *copy;

    if (input == NULL || input_count == 0) {
        if (out_count != NULL) {
            *out_count = 0;
        }
        return NULL;
    }

    result = malloc((input_count + 1) * sizeof(char *));
    if (result == NULL) {
        if (out_count != NULL) {
            *out_count = 0;
        }
        return NULL;
    }

    j = 0;
    for (i = 0; i < input_count; i++) {
        if (input[i] == NULL) {
            continue;
        }
        len = strlen(input[i]);
        if (len != target_len) {
            continue;
        }
        if (len == (size_t)-1) {
            for (k = 0; k < j; k++) {
                free(result[k]);
            }
            free(result);
            if (out_count != NULL) {
                *out_count = 0;
            }
            return NULL;
        }
        copy = malloc(len + 1);
        if (copy == NULL) {
            for (k = 0; k < j; k++) {
                free(result[k]);
            }
            free(result);
            if (out_count != NULL) {
                *out_count = 0;
            }
            return NULL;
        }
        memcpy(copy, input[i], len);
        copy[len] = '\0';
        result[j++] = copy;
    }
    result[j] = NULL;

    if (out_count != NULL) {
        *out_count = j;
    }
    return result;
}

void free_strings(char **strings)
{
    size_t i;
    if (strings == NULL) {
        return;
    }
    for (i = 0; strings[i] != NULL; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main(void)
{
    const char *input[] = {"practice", "solution", "C", "code", "test"};
    size_t input_count = sizeof(input) / sizeof(input[0]);
    size_t out_count;
    size_t i;
    char **result;

    result = extract_strings(input, input_count, 8, &out_count);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < out_count; i++) {
        printf("%s\n", result[i]);
    }

    free_strings(result);
    return EXIT_SUCCESS;
}