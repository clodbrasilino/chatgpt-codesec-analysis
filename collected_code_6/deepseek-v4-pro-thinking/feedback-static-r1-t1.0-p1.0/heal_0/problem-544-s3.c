#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int first;
    int second;
    struct Tuple *next;
} Tuple;

char *flatten_tuple_list(const Tuple *head);

char *flatten_tuple_list(const Tuple *head) {
    const Tuple *node;
    size_t length = 1;
    size_t remaining;
    int written;
    char *result;
    char *cursor;

    for (node = head; node != NULL; node = node->next) {
        written = snprintf(NULL, 0, "%d,%d", node->first, node->second);
        if (written < 0) {
            return NULL;
        }
        length += (size_t)written;
        if (node->next != NULL) {
            length += 1;
        }
    }

    result = malloc(length);
    if (result == NULL) {
        return NULL;
    }

    cursor = result;
    remaining = length;

    for (node = head; node != NULL; node = node->next) {
        written = snprintf(cursor, remaining, "%d,%d", node->first, node->second);
        if (written < 0) {
            free(result);
            return NULL;
        }
        if ((size_t)written >= remaining) {
            free(result);
            return NULL;
        }

        cursor += written;
        remaining -= (size_t)written;

        if (node->next != NULL) {
            if (remaining < 2) {
                free(result);
                return NULL;
            }
            *cursor = ',';
            cursor++;
            remaining--;
        }
    }

    *cursor = '\0';
    return result;
}

int main(void) {
    Tuple third = {3, 4, NULL};
    Tuple second = {2, 3, &third};
    Tuple first = {1, 2, &second};
    char *flattened = flatten_tuple_list(&first);

    if (flattened == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", flattened);
    free(flattened);

    return EXIT_SUCCESS;
}