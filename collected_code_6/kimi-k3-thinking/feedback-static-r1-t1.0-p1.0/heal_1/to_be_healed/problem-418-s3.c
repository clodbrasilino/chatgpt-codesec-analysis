#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} IntList;

static const IntList *find_longest_sublist(const IntList *lists, size_t count)
{
    size_t i;
    const IntList *longest;

    if (lists == NULL || count == 0U) {
        return NULL;
    }

    longest = &lists[0];
    for (i = 1U; i < count; i++) {
        if (lists[i].length > longest->length) {
            longest = &lists[i];
        }
    }

    return longest;
}

static int init_list(IntList *list, size_t length, int start)
{
    size_t i;

    if (list == NULL) {
        return -1;
    }

    list->data = NULL;
    list->length = 0U;

    if (length == 0U) {
        return 0;
    }

    list->data = malloc(length * sizeof(*list->data));
    if (list->data == NULL) {
        return -1;
    }

    for (i = 0U; i < length; i++) {
        list->data[i] = start + (int)i;
    }
    list->length = length;

    return 0;
}

int main(void)
{
    IntList lists[4];
    const size_t lengths[4] = {3U, 7U, 2U, 5U};
    const size_t count = 4U;
    size_t initialized = 0U;
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'j' can be reduced. [variableScope]
     */
    size_t j;
    /* Possible weaknesses found:
     *  The scope of the variable 'longest' can be reduced. [variableScope]
     */
    const IntList *longest;
    int status = EXIT_SUCCESS;

    for (i = 0U; i < count; i++) {
        lists[i].data = NULL;
        lists[i].length = 0U;
    }

    for (i = 0U; i < count; i++) {
        if (init_list(&lists[i], lengths[i], (int)(i * 10U)) != 0) {
            fprintf(stderr, "Failed to allocate memory for sublist %zu\n", i);
            status = EXIT_FAILURE;
            break;
        }
        initialized++;
    }

    if (status == EXIT_SUCCESS) {
        longest = find_longest_sublist(lists, count);
        if (longest != NULL) {
            printf("Longest sublist index: %zu\n", (size_t)(longest - lists));
            printf("Longest sublist length: %zu\n", longest->length);
            printf("Elements:");
            for (j = 0U; j < longest->length; j++) {
                printf(" %d", longest->data[j]);
            }
            printf("\n");
        } else {
            printf("No sublist available\n");
        }
    }

    for (i = 0U; i < initialized; i++) {
        free(lists[i].data);
        lists[i].data = NULL;
        lists[i].length = 0U;
    }

    return status;
}