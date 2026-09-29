#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *const *items;
    size_t count;
} StringList;

static int checked_string_length(const char *string, size_t *length)
{
    const char *end;

    if (string == NULL || length == NULL) {
        return -1;
    }

    end = strchr(string, '\0');
    if (end == NULL) {
        return -1;
    }

    *length = (size_t)(end - string);
    return 0;
}

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (checked_string_length(source, &length) != 0 ||
        length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    return copy;
}

static char *concatenate_strings(const char *left, const char *right)
{
    size_t left_length;
    size_t right_length;
    size_t result_size;
    char *result;

    if (checked_string_length(left, &left_length) != 0 ||
        checked_string_length(right, &right_length) != 0 ||
        left_length > SIZE_MAX - right_length ||
        left_length + right_length == SIZE_MAX) {
        return NULL;
    }

    result_size = left_length + right_length + 1;
    result = malloc(result_size);
    if (result == NULL) {
        return NULL;
    }

    if (left_length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, left, left_length);
    }
    if (right_length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + left_length, right, right_length);
    }
    result[left_length + right_length] = '\0';

    return result;
}

static int merge_first_and_last(const StringList *lists, size_t list_count,
                                char **merged_first, char **merged_last)
{
    char *first_result;
    char *last_result;
    size_t i;

    if (lists == NULL || list_count == 0 ||
        merged_first == NULL || merged_last == NULL ||
        merged_first == merged_last) {
        return -1;
    }

    *merged_first = NULL;
    *merged_last = NULL;

    first_result = duplicate_string("");
    last_result = duplicate_string("");

    if (first_result == NULL || last_result == NULL) {
        free(first_result);
        free(last_result);
        return -1;
    }

    for (i = 0; i < list_count; ++i) {
        const char *first_item;
        const char *last_item;
        char *new_first;
        char *new_last;

        if (lists[i].items == NULL || lists[i].count == 0) {
            free(first_result);
            free(last_result);
            return -1;
        }

        first_item = lists[i].items[0];
        last_item = lists[i].items[lists[i].count - 1];

        if (first_item == NULL || last_item == NULL) {
            free(first_result);
            free(last_result);
            return -1;
        }

        new_first = concatenate_strings(first_result, first_item);
        if (new_first == NULL) {
            free(first_result);
            free(last_result);
            return -1;
        }

        new_last = concatenate_strings(last_result, last_item);
        if (new_last == NULL) {
            free(new_first);
            free(first_result);
            free(last_result);
            return -1;
        }

        free(first_result);
        free(last_result);
        first_result = new_first;
        last_result = new_last;
    }

    *merged_first = first_result;
    *merged_last = last_result;

    return 0;
}

int main(void)
{
    const char *const items1[] = {"Hello", "middle", "World"};
    const char *const items2[] = {"Good", "item", "Morning"};
    const char *const items3[] = {"C", "value", "Language"};
    const StringList lists[] = {
        {items1, sizeof items1 / sizeof items1[0]},
        {items2, sizeof items2 / sizeof items2[0]},
        {items3, sizeof items3 / sizeof items3[0]}
    };
    char *merged_first = NULL;
    char *merged_last = NULL;
    int status = EXIT_SUCCESS;

    if (merge_first_and_last(lists, sizeof lists / sizeof lists[0],
                             &merged_first, &merged_last) != 0) {
        fputs("Failed to merge list elements.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Merged first elements: %s\n", merged_first) < 0 ||
        printf("Merged last elements: %s\n", merged_last) < 0) {
        status = EXIT_FAILURE;
    }

    free(merged_first);
    free(merged_last);

    return status;
}