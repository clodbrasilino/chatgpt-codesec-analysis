#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} StringList;

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, source, length + 1);
    return copy;
}

static char *concatenate_strings(const char *left, const char *right)
{
    size_t left_length;
    size_t right_length;
    char *result;

    if (left == NULL || right == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    left_length = strlen(left);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    right_length = strlen(right);

    if (left_length > SIZE_MAX - right_length - 1) {
        return NULL;
    }

    result = malloc(left_length + right_length + 1);
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, left, left_length);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result + left_length, right, right_length + 1);
    return result;
}

static int merge_first_and_last(const StringList *lists, size_t list_count,
                                char **merged_first, char **merged_last)
{
    char *first_result;
    char *last_result;
    size_t i;

    if (lists == NULL || merged_first == NULL || merged_last == NULL ||
        list_count == 0) {
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
        char *new_first;
        char *new_last;

        if (lists[i].items == NULL || lists[i].count == 0 ||
            lists[i].items[0] == NULL ||
            lists[i].items[lists[i].count - 1] == NULL) {
            free(first_result);
            free(last_result);
            return -1;
        }

        new_first = concatenate_strings(first_result, lists[i].items[0]);
        if (new_first == NULL) {
            free(first_result);
            free(last_result);
            return -1;
        }

        free(first_result);
        first_result = new_first;

        new_last = concatenate_strings(
            last_result, lists[i].items[lists[i].count - 1]);
        if (new_last == NULL) {
            free(first_result);
            free(last_result);
            return -1;
        }

        free(last_result);
        last_result = new_last;
    }

    *merged_first = first_result;
    *merged_last = last_result;
    return 0;
}

int main(void)
{
    char *items1[] = {"Hello", "middle", "World"};
    char *items2[] = {"Good", "item", "Morning"};
    char *items3[] = {"C", "value", "Language"};
    StringList lists[] = {
        {items1, sizeof(items1) / sizeof(items1[0])},
        {items2, sizeof(items2) / sizeof(items2[0])},
        {items3, sizeof(items3) / sizeof(items3[0])}
    };
    char *merged_first;
    char *merged_last;

    if (merge_first_and_last(
            lists, sizeof(lists) / sizeof(lists[0]),
            &merged_first, &merged_last) != 0) {
        fputs("Failed to merge list elements.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Merged first elements: %s\n", merged_first) < 0 ||
        printf("Merged last elements: %s\n", merged_last) < 0) {
        free(merged_first);
        free(merged_last);
        return EXIT_FAILURE;
    }

    free(merged_first);
    free(merged_last);
    return EXIT_SUCCESS;
}