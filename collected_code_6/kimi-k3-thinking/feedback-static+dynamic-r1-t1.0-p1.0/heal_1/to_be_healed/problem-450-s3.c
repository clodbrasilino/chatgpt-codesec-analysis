#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_strings(const char **list, size_t list_size, size_t extract_size, size_t *out_count);
void free_string_list(char **list, size_t count);
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 2 failed: expected ['exercises'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  */

char **extract_strings(const char **list, size_t list_size, size_t extract_size, size_t *out_count)
{
    char **result;
    size_t count;
    size_t i;

    if (out_count == NULL) {
        return NULL;
    }
    *out_count = 0;

    if (list == NULL || extract_size == 0) {
        return NULL;
    }

    count = extract_size;
    if (count > list_size) {
        count = list_size;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t len;

        if (list[i] == NULL) {
            free_string_list(result, i);
            return NULL;
        }

        len = strlen(list[i]);
        result[i] = malloc(len + 1);
        if (result[i] == NULL) {
            free_string_list(result, i);
            return NULL;
        }
        memcpy(result[i], list[i], len + 1);
    }

    *out_count = count;
    return result;
}

void free_string_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void)
{
    const char *list[] = {"apple", "banana", "cherry", "date", "elderberry"};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    size_t extract_size = 3;
    size_t extracted_count = 0;
    char **extracted;
    size_t i;

    extracted = extract_strings(list, list_size, extract_size, &extracted_count);
    if (extracted == NULL) {
        fprintf(stderr, "String extraction failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < extracted_count; i++) {
        if (printf("%s\n", extracted[i]) < 0) {
            fprintf(stderr, "Output error\n");
            free_string_list(extracted, extracted_count);
            return EXIT_FAILURE;
        }
    }

    free_string_list(extracted, extracted_count);

    return EXIT_SUCCESS;
}