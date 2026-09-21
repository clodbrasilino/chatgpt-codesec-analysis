#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *const *items;
    size_t count;
} StringList;

static int checked_add_size(size_t left, size_t right, size_t *result)
{
    if (result == NULL || left > SIZE_MAX - right) {
        return -1;
    }

    *result = left + right;
    return 0;
}

static char *append_string(char *destination, size_t *destination_length,
                           const char *source)
{
    size_t source_length;
    size_t new_length;
    size_t allocation_size;
    char *resized;

    if (destination == NULL || destination_length == NULL || source == NULL) {
        free(destination);
        return NULL;
    }

    source_length = strlen(source);

    if (checked_add_size(*destination_length, source_length, &new_length) != 0 ||
        checked_add_size(new_length, 1, &allocation_size) != 0) {
        free(destination);
        return NULL;
    }

    resized = realloc(destination, allocation_size);
    if (resized == NULL) {
        free(destination);
        return NULL;
    }

    if (source_length > 0) {
        memcpy(resized + *destination_length, source, source_length);
    }

    resized[new_length] = '\0';
    *destination_length = new_length;

    return resized;
}

static char *create_empty_string(void)
{
    char *string = malloc(1);

    if (string != NULL) {
        string[0] = '\0';
    }

    return string;
}

static int merge_first_and_last(const StringList *lists, size_t list_count,
                                char **merged_first, char **merged_last)
{
    char *first_result;
    char *last_result;
    size_t first_length = 0;
    size_t last_length = 0;
    size_t i;

    if (lists == NULL || list_count == 0 ||
        merged_first == NULL || merged_last == NULL ||
        merged_first == merged_last) {
        return -1;
    }

    *merged_first = NULL;
    *merged_last = NULL;

    first_result = create_empty_string();
    last_result = create_empty_string();

    if (first_result == NULL || last_result == NULL) {
        free(first_result);
        free(last_result);
        return -1;
    }

    for (i = 0; i < list_count; ++i) {
        const char *first_item;
        const char *last_item;

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

        first_result = append_string(first_result, &first_length, first_item);
        if (first_result == NULL) {
            free(last_result);
            return -1;
        }

        last_result = append_string(last_result, &last_length, last_item);
        if (last_result == NULL) {
            free(first_result);
            return -1;
        }
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