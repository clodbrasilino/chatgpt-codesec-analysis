#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    const char *const *items;
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

char *flatten_tuple_list(const Tuple *head, const char *separator)
{
    const Tuple *tuple;
    size_t separator_length;
    size_t total_length = 0;
    int has_item = 0;
    char *result;
    char *destination;

    if (separator == NULL || tuple_list_has_cycle(head)) {
        errno = EINVAL;
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    separator_length = strlen(separator);

    for (tuple = head; tuple != NULL; tuple = tuple->next) {
        size_t i;

        if (tuple->count > 0 && tuple->items == NULL) {
            errno = EINVAL;
            return NULL;
        }

        for (i = 0; i < tuple->count; ++i) {
            size_t item_length;

            if (tuple->items[i] == NULL) {
                errno = EINVAL;
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            item_length = strlen(tuple->items[i]);

            if (has_item) {
                if (separator_length > SIZE_MAX - total_length) {
                    errno = EOVERFLOW;
                    return NULL;
                }
                total_length += separator_length;
            }

            if (item_length > SIZE_MAX - total_length) {
                errno = EOVERFLOW;
                return NULL;
            }

            total_length += item_length;
            has_item = 1;
        }
    }

    if (total_length == SIZE_MAX) {
        errno = EOVERFLOW;
        return NULL;
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    destination = result;
    has_item = 0;

    for (tuple = head; tuple != NULL; tuple = tuple->next) {
        size_t i;

        for (i = 0; i < tuple->count; ++i) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t item_length = strlen(tuple->items[i]);

            if (has_item && separator_length > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(destination, separator, separator_length);
                destination += separator_length;
            }

            if (item_length > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(destination, tuple->items[i], item_length);
                destination += item_length;
            }

            has_item = 1;
        }
    }

    *destination = '\0';
    return result;
}

int main(void)
{
    const char *first_items[] = {"one", "two"};
    const char *second_items[] = {"three", "four", "five"};
    const Tuple second = {second_items, 3, NULL};
    const Tuple first = {first_items, 2, &second};
    char *flattened = flatten_tuple_list(&first, ", ");

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