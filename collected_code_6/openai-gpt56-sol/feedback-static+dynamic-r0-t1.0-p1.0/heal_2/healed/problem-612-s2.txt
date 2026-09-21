#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *const *items;
    size_t count;
} StringList;

static int checked_string_length(const char *source, size_t maximum,
                                 size_t *length)
{
    const char *terminator;

    if (source == NULL || length == NULL || maximum == 0) {
        return -1;
    }

    terminator = memchr(source, '\0', maximum);
    if (terminator == NULL) {
        return -1;
    }

    *length = (size_t)(terminator - source);
    return 0;
}

static int append_string(char **destination, size_t *destination_length,
                         const char *source, size_t maximum_source_length)
{
    size_t source_length;
    size_t new_length;
    size_t allocation_size;
    char *resized;

    if (destination == NULL || destination_length == NULL ||
        *destination == NULL || source == NULL) {
        return -1;
    }

    if (checked_string_length(source, maximum_source_length,
                              &source_length) != 0) {
        return -1;
    }

    if (source_length > SIZE_MAX - *destination_length) {
        return -1;
    }

    new_length = *destination_length + source_length;

    if (new_length == SIZE_MAX) {
        return -1;
    }

    allocation_size = new_length + 1;
    resized = realloc(*destination, allocation_size);
    if (resized == NULL) {
        return -1;
    }

    if (source_length > 0) {
        memmove(resized + *destination_length, source, source_length);
    }

    resized[new_length] = '\0';
    *destination = resized;
    *destination_length = new_length;

    return 0;
}

static int merge_first_and_last(const StringList *lists, size_t list_count,
                                size_t maximum_string_length,
                                char **merged_first, char **merged_last)
{
    char *first_result;
    char *last_result;
    size_t first_length = 0;
    size_t last_length = 0;
    size_t i;

    if (lists == NULL || list_count == 0 || maximum_string_length == 0 ||
        merged_first == NULL || merged_last == NULL ||
        merged_first == merged_last) {
        return -1;
    }

    *merged_first = NULL;
    *merged_last = NULL;

    first_result = malloc(1);
    last_result = malloc(1);
    if (first_result == NULL || last_result == NULL) {
        free(first_result);
        free(last_result);
        return -1;
    }

    first_result[0] = '\0';
    last_result[0] = '\0';

    for (i = 0; i < list_count; ++i) {
        const char *first;
        const char *last;

        if (lists[i].items == NULL || lists[i].count == 0) {
            free(first_result);
            free(last_result);
            return -1;
        }

        first = lists[i].items[0];
        last = lists[i].items[lists[i].count - 1];

        if (first == NULL || last == NULL ||
            append_string(&first_result, &first_length, first,
                          maximum_string_length) != 0 ||
            append_string(&last_result, &last_length, last,
                          maximum_string_length) != 0) {
            free(first_result);
            free(last_result);
            return -1;
        }
    }

    *merged_first = first_result;
    *merged_last = last_result;
    return 0;
}

int main(void)
{
    static const char *const items1[] = {
        "Hello", "middle", "World"
    };
    static const char *const items2[] = {
        "Good", "item", "Morning"
    };
    static const char *const items3[] = {
        "C", "value", "Language"
    };
    static const StringList lists[] = {
        {items1, sizeof(items1) / sizeof(items1[0])},
        {items2, sizeof(items2) / sizeof(items2[0])},
        {items3, sizeof(items3) / sizeof(items3[0])}
    };
    char *merged_first = NULL;
    char *merged_last = NULL;

    if (merge_first_and_last(
            lists, sizeof(lists) / sizeof(lists[0]), 1024,
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