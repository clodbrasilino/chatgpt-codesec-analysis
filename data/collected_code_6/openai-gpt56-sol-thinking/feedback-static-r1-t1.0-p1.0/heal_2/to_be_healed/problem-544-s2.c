#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TupleItem {
    const char *data;
    size_t length;
} TupleItem;

typedef struct Tuple {
    const TupleItem *items;
    size_t count;
    const struct Tuple *next;
} Tuple;

static int tuple_list_has_cycle(const Tuple *head)
{
    const Tuple *slow = head;
    const Tuple *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return 1;
        }
    }

    return 0;
}

static int add_length(size_t *total, size_t amount)
{
    if (amount > SIZE_MAX - *total) {
        errno = EOVERFLOW;
        return -1;
    }

    *total += amount;
    return 0;
}

static int append_bytes(char *destination,
                        size_t capacity,
                        size_t *offset,
                        const char *source,
                        size_t length)
{
    if (length == 0) {
        return 0;
    }

    if (source == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (*offset > capacity || length > capacity - *offset) {
        errno = EOVERFLOW;
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(destination + *offset, source, length);
    *offset += length;
    return 0;
}

char *flatten_tuple_list(const Tuple *head,
                         const char *separator,
                         size_t separator_length)
{
    const Tuple *tuple;
    size_t total_length = 0;
    size_t offset = 0;
    int has_item = 0;
    char *result;

    if ((separator_length != 0 && separator == NULL) ||
        tuple_list_has_cycle(head)) {
        errno = EINVAL;
        return NULL;
    }

    for (tuple = head; tuple != NULL; tuple = tuple->next) {
        size_t i;

        if (tuple->count != 0 && tuple->items == NULL) {
            errno = EINVAL;
            return NULL;
        }

        for (i = 0; i < tuple->count; ++i) {
            const TupleItem *item = &tuple->items[i];

            if (item->length != 0 && item->data == NULL) {
                errno = EINVAL;
                return NULL;
            }

            if (has_item && add_length(&total_length, separator_length) != 0) {
                return NULL;
            }

            if (add_length(&total_length, item->length) != 0) {
                return NULL;
            }

            has_item = 1;
        }
    }

    if (total_length == SIZE_MAX) {
        errno = EOVERFLOW;
        return NULL;
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    has_item = 0;

    for (tuple = head; tuple != NULL; tuple = tuple->next) {
        size_t i;

        for (i = 0; i < tuple->count; ++i) {
            const TupleItem *item = &tuple->items[i];

            if (has_item &&
                append_bytes(result, total_length, &offset,
                             separator, separator_length) != 0) {
                free(result);
                return NULL;
            }

            if (append_bytes(result, total_length, &offset,
                             item->data, item->length) != 0) {
                free(result);
                return NULL;
            }

            has_item = 1;
        }
    }

    result[offset] = '\0';
    return result;
}

int main(void)
{
    static const TupleItem first_items[] = {
        {"one", sizeof("one") - 1},
        {"two", sizeof("two") - 1}
    };
    static const TupleItem second_items[] = {
        {"three", sizeof("three") - 1},
        {"four", sizeof("four") - 1},
        {"five", sizeof("five") - 1}
    };
    static const char separator[] = ", ";
    const Tuple second = {
        second_items,
        sizeof(second_items) / sizeof(second_items[0]),
        NULL
    };
    const Tuple first = {
        first_items,
        sizeof(first_items) / sizeof(first_items[0]),
        &second
    };
    char *flattened = flatten_tuple_list(
        &first,
        separator,
        sizeof(separator) - 1
    );

    if (flattened == NULL) {
        perror("flatten_tuple_list");
        return EXIT_FAILURE;
    }

    if (puts(flattened) == EOF) {
        free(flattened);
        return EXIT_FAILURE;
    }

    free(flattened);
    return EXIT_SUCCESS;
}