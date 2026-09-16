#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Python'], got <no output>
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 2 failed: expected ['exercises'], got <no output>
  */

char **extract_strings(const char * const *strings, size_t count, size_t length, size_t *out_count)
{
    if (out_count != NULL) {
        *out_count = 0;
    }
    if (strings == NULL || count == 0) {
        return NULL;
    }

    size_t matching = 0;
    size_t i;
    for (i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            if (length == 0 || length == (size_t)-1 || strlen(strings[i]) == length) {
                matching++;
            }
        }
    }

    if (matching == 0) {
        return NULL;
    }

    char **result = malloc((matching + 1) * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    size_t result_index = 0;
    for (i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            if (length == 0 || length == (size_t)-1 || strlen(strings[i]) == length) {
                size_t len = strlen(strings[i]);
                char *copy = malloc(len + 1);
                if (copy == NULL) {
                    size_t k;
                    for (k = 0; k < result_index; k++) {
                        free(result[k]);
                    }
                    free(result);
                    return NULL;
                }
                memcpy(copy, strings[i], len + 1);
                result[result_index++] = copy;
            }
        }
    }

    result[result_index] = NULL;
    if (out_count != NULL) {
        *out_count = matching;
    }

    return result;
}

int main(void)
{
    const char *test0[] = {"practice", "solution"};
    size_t cnt0 = sizeof(test0) / sizeof(test0[0]);
    size_t out0 = 0;
    char **res0 = extract_strings(test0, cnt0, 8, &out0);
    if (res0) {
        for (size_t i = 0; i < out0; i++) {
            printf("%s\n", res0[i]);
            free(res0[i]);
        }
        free(res0);
    }

    const char *test1[] = {"Python"};
    size_t cnt1 = sizeof(test1) / sizeof(test1[0]);
    size_t out1 = 0;
    char **res1 = extract_strings(test1, cnt1, 6, &out1);
    if (res1) {
        for (size_t i = 0; i < out1; i++) {
            printf("%s\n", res1[i]);
            free(res1[i]);
        }
        free(res1);
    }

    const char *test2[] = {"exercises"};
    size_t cnt2 = sizeof(test2) / sizeof(test2[0]);
    size_t out2 = 0;
    char **res2 = extract_strings(test2, cnt2, 9, &out2);
    if (res2) {
        for (size_t i = 0; i < out2; i++) {
            printf("%s\n", res2[i]);
            free(res2[i]);
        }
        free(res2);
    }

    return 0;
}