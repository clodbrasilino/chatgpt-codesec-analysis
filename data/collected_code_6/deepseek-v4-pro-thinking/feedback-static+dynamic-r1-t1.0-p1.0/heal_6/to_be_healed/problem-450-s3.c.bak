#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Python'], got <no output>
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 2 failed: expected ['exercises'], got <no output>
  */

char **extract_strings(const char *input[], size_t target_len, size_t *out_count)
{
    size_t count, i, j, k;
    char **result;

    if (out_count != NULL) {
        *out_count = 0;
    }

    if (input == NULL || out_count == NULL) {
        return NULL;
    }

    count = 0;
    while (input[count] != NULL) {
        count++;
    }

    if (count == 0) {
        result = malloc(sizeof(char *));
        if (result == NULL) {
            return NULL;
        }
        result[0] = NULL;
        return result;
    }

    if (count > (size_t)-1 / sizeof(char *) - 1) {
        return NULL;
    }

    result = malloc((count + 1) * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 0; i < count; i++) {
        size_t len = strlen(input[i]);
        if (len != target_len) {
            continue;
        }

        char *copy = malloc(len + 1);
        if (copy == NULL) {
            for (k = 0; k < j; k++) {
                free(result[k]);
            }
            free(result);
            return NULL;
        }

        memcpy(copy, input[i], len);
        copy[len] = '\0';
        result[j++] = copy;
    }

    result[j] = NULL;
    *out_count = j;
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
    const char *input[] = {"practice", "solution", "C", "code", "test", NULL};
    size_t out_count;
    size_t i;
    char **result;

    result = extract_strings(input, 8, &out_count);
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