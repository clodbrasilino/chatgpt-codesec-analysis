#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *data;
    size_t length;
} StringView;

typedef struct {
    const StringView *items;
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

static int append_string(char **destination, size_t *destination_length,
                         size_t *destination_capacity, const char *source,
                         size_t source_length)
{
    size_t new_length;
    size_t required_capacity;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;
    char *resized;

    if (destination == NULL || *destination == NULL ||
        destination_length == NULL || destination_capacity == NULL ||
        (source == NULL && source_length != 0) ||
        *destination_capacity == 0 ||
        *destination_length >= *destination_capacity) {
        return -1;
    }

    if (checked_add_size(*destination_length, source_length, &new_length) != 0 ||
        checked_add_size(new_length, 1, &required_capacity) != 0) {
        return -1;
    }

    if (required_capacity > *destination_capacity) {
        new_capacity = *destination_capacity;

        while (new_capacity < required_capacity) {
            if (new_capacity > SIZE_MAX / 2) {
                new_capacity = required_capacity;
                break;
            }

            new_capacity *= 2;
        }

        resized = realloc(*destination, new_capacity);
        if (resized == NULL) {
            return -1;
        }

        *destination = resized;
        *destination_capacity = new_capacity;
    }

    if (source_length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(*destination + *destination_length, source, source_length);
    }

    (*destination)[new_length] = '\0';
    *destination_length = new_length;

    return 0;
}

static char *create_empty_string(size_t *capacity)
{
    char *string;

    if (capacity == NULL) {
        return NULL;
    }

    string = malloc(1);
    if (string == NULL) {
        return NULL;
    }

    string[0] = '\0';
    *capacity = 1;

    return string;
}

static int merge_first_and_last(const StringList *lists, size_t list_count,
                                char **merged_first, char **merged_last)
{
    char *first_result;
    char *last_result;
    size_t first_length = 0;
    size_t last_length = 0;
    size_t first_capacity;
    size_t last_capacity;
    size_t i;

    if (lists == NULL || list_count == 0 ||
        merged_first == NULL || merged_last == NULL ||
        merged_first == merged_last) {
        return -1;
    }

    *merged_first = NULL;
    *merged_last = NULL;

    first_result = create_empty_string(&first_capacity);
    if (first_result == NULL) {
        return -1;
    }

    last_result = create_empty_string(&last_capacity);
    if (last_result == NULL) {
        free(first_result);
        return -1;
    }

    for (i = 0; i < list_count; ++i) {
        const StringView *first_item;
        const StringView *last_item;

        if (lists[i].items == NULL || lists[i].count == 0) {
            free(first_result);
            free(last_result);
            return -1;
        }

        first_item = &lists[i].items[0];
        last_item = &lists[i].items[lists[i].count - 1];

        if ((first_item->data == NULL && first_item->length != 0) ||
            (last_item->data == NULL && last_item->length != 0)) {
            free(first_result);
            free(last_result);
            return -1;
        }

        if (append_string(&first_result, &first_length, &first_capacity,
                          first_item->data, first_item->length) != 0 ||
            append_string(&last_result, &last_length, &last_capacity,
                          last_item->data, last_item->length) != 0) {
            free(first_result);
            free(last_result);
            return -1;
        }
    }

    *merged_first = first_result;
    *merged_last = last_result;

    return 0;
}

#define STRING_VIEW(value) { (value), sizeof(value) - 1 }

int main(void)
{
    static const StringView items1[] = {
        STRING_VIEW("Hello"),
        STRING_VIEW("middle"),
        STRING_VIEW("World")
    };
    static const StringView items2[] = {
        STRING_VIEW("Good"),
        STRING_VIEW("item"),
        STRING_VIEW("Morning")
    };
    static const StringView items3[] = {
        STRING_VIEW("C"),
        STRING_VIEW("value"),
        STRING_VIEW("Language")
    };
    static const StringList lists[] = {
        { items1, sizeof(items1) / sizeof(items1[0]) },
        { items2, sizeof(items2) / sizeof(items2[0]) },
        { items3, sizeof(items3) / sizeof(items3[0]) }
    };
    char *merged_first = NULL;
    char *merged_last = NULL;
    int status = EXIT_SUCCESS;

    if (merge_first_and_last(lists, sizeof(lists) / sizeof(lists[0]),
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