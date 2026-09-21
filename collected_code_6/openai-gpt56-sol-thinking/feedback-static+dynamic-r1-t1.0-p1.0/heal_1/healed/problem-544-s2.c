#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Text {
    const char *const data;
    const size_t length;
} Text;

typedef struct Tuple {
    const Text *const items;
    const size_t count;
    const struct Tuple *const next;
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

static int text_is_valid(const Text *text)
{
    size_t i;

    if (text == NULL || (text->length != 0 && text->data == NULL)) {
        return 0;
    }

    for (i = 0; i < text->length; ++i) {
        if (text->data[i] == '\0') {
            return 0;
        }
    }

    return 1;
}

static int append_text(char *destination, size_t capacity, size_t *used,
                       const Text *text)
{
    size_t i;

    if (*used > capacity || text->length > capacity - *used) {
        return 0;
    }

    for (i = 0; i < text->length; ++i) {
        destination[*used + i] = text->data[i];
    }

    *used += text->length;
    return 1;
}

char *flatten_tuple_list(const Tuple *head, const Text *separator)
{
    const Tuple *tuple;
    size_t total_length = 0;
    size_t used = 0;
    int has_item = 0;
    char *result;

    if (!text_is_valid(separator) || tuple_list_has_cycle(head)) {
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
            const Text *item = &tuple->items[i];

            if (!text_is_valid(item)) {
                errno = EINVAL;
                return NULL;
            }

            if (has_item) {
                if (separator->length > SIZE_MAX - total_length) {
                    errno = EOVERFLOW;
                    return NULL;
                }

                total_length += separator->length;
            }

            if (item->length > SIZE_MAX - total_length) {
                errno = EOVERFLOW;
                return NULL;
            }

            total_length += item->length;
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
            if (has_item &&
                !append_text(result, total_length, &used, separator)) {
                free(result);
                errno = EOVERFLOW;
                return NULL;
            }

            if (!append_text(result, total_length, &used, &tuple->items[i])) {
                free(result);
                errno = EOVERFLOW;
                return NULL;
            }

            has_item = 1;
        }
    }

    result[used] = '\0';
    return result;
}

int main(void)
{
    static const Text first_items[] = {
        {"one", sizeof("one") - 1},
        {"two", sizeof("two") - 1}
    };
    static const Text second_items[] = {
        {"three", sizeof("three") - 1},
        {"four", sizeof("four") - 1},
        {"five", sizeof("five") - 1}
    };
    static const Text separator = {
        ", ", sizeof(", ") - 1
    };
    static const Tuple second = {
        second_items,
        sizeof(second_items) / sizeof(second_items[0]),
        NULL
    };
    static const Tuple first = {
        first_items,
        sizeof(first_items) / sizeof(first_items[0]),
        &second
    };
    char *flattened = flatten_tuple_list(&first, &separator);

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