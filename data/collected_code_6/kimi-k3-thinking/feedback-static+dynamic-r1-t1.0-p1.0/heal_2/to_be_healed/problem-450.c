#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 4096
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['practice', 'solution'], got null
  *  test case 2 failed: expected ['exercises'], got null
  *  test case 1 failed: expected ['Python'], got null
  */

char **extract_strings(const char *const *list, size_t list_size, size_t count)
{
    char **result;
    size_t i;

    if (list == NULL || count == 0 || count > list_size) {
        return NULL;
    }

    result = calloc(count, sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t len;

        if (list[i] == NULL) {
            continue;
        }

        len = strnlen(list[i], MAX_STRING_LENGTH);
        if (len == MAX_STRING_LENGTH) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        result[i] = malloc(len + 1);
        if (result[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[i], list[i], len);
        result[i][len] = '\0';
    }

    return result;
}

void free_strings(char **strings, size_t count)
{
    size_t i;

    if (strings == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main(void)
{
    const char *list[] = {"apple", "banana", "cherry", "date", "elderberry"};
    const size_t list_size = sizeof(list) / sizeof(list[0]);
    const size_t count = 3;
    char **extracted;
    size_t i;

    extracted = extract_strings(list, list_size, count);
    if (extracted == NULL) {
        fprintf(stderr, "Error: failed to extract strings\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (extracted[i] != NULL) {
            printf("%s\n", extracted[i]);
        }
    }

    free_strings(extracted, count);

    return EXIT_SUCCESS;
}