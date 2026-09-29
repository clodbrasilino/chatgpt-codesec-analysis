#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *items;
    size_t length;
} List;

typedef struct {
    List *lists;
    size_t count;
} ListOfLists;

static bool lists_equal(const List *a, const List *b)
{
    size_t i;

    if (a == NULL || b == NULL) {
        return false;
    }
    if (a->length != b->length) {
        return false;
    }
    for (i = 0; i < a->length; i++) {
        if (a->items[i] != b->items[i]) {
            return false;
        }
    }
    return true;
}

static int copy_list(List *dest, const List *src)
{
    size_t i;

    if (dest == NULL || src == NULL) {
        return -1;
    }
    dest->length = src->length;
    if (src->length == 0) {
        dest->items = NULL;
        return 0;
    }
    dest->items = malloc(src->length * sizeof(int));
    if (dest->items == NULL) {
        return -1;
    }
    for (i = 0; i < src->length; i++) {
        dest->items[i] = src->items[i];
    }
    return 0;
}

static void free_list_of_lists(ListOfLists *lol)
{
    size_t i;

    if (lol == NULL) {
        return;
    }
    if (lol->lists != NULL) {
        for (i = 0; i < lol->count; i++) {
            free(lol->lists[i].items);
            lol->lists[i].items = NULL;
        }
        free(lol->lists);
        lol->lists = NULL;
    }
    lol->count = 0;
}

static int remove_duplicates(const ListOfLists *input, ListOfLists *output)
{
    size_t i;
    size_t j;
    bool duplicate;

    if (input == NULL || output == NULL) {
        return -1;
    }

    output->lists = NULL;
    output->count = 0;

    if (input->count == 0) {
        return 0;
    }

    output->lists = malloc(input->count * sizeof(List));
    if (output->lists == NULL) {
        return -1;
    }

    for (i = 0; i < input->count; i++) {
        duplicate = false;
        for (j = 0; j < output->count; j++) {
            if (lists_equal(&input->lists[i], &output->lists[j])) {
                duplicate = true;
                break;
            }
        }
        if (!duplicate) {
            if (copy_list(&output->lists[output->count], &input->lists[i]) != 0) {
                free_list_of_lists(output);
                return -1;
            }
            output->count++;
        }
    }
    return 0;
}

static void print_list_of_lists(const ListOfLists *lol)
{
    size_t i;
    size_t j;

    if (lol == NULL) {
        return;
    }
    printf("[\n");
    for (i = 0; i < lol->count; i++) {
        printf("  [");
        for (j = 0; j < lol->lists[i].length; j++) {
            printf("%d", lol->lists[i].items[j]);
            if (j + 1 < lol->lists[i].length) {
                printf(", ");
            }
        }
        printf("]\n");
    }
    printf("]\n");
}

int main(void)
{
    int a[] = {1, 2, 3};
    int b[] = {4, 5};
    int c[] = {1, 2, 3};
    int d[] = {6};
    int e[] = {4, 5};

    List source_lists[5];
    ListOfLists input;
    ListOfLists output;

    source_lists[0].items = a;
    source_lists[0].length = sizeof(a) / sizeof(a[0]);
    source_lists[1].items = b;
    source_lists[1].length = sizeof(b) / sizeof(b[0]);
    source_lists[2].items = c;
    source_lists[2].length = sizeof(c) / sizeof(c[0]);
    source_lists[3].items = d;
    source_lists[3].length = sizeof(d) / sizeof(d[0]);
    source_lists[4].items = e;
    source_lists[4].length = sizeof(e) / sizeof(e[0]);

    input.lists = source_lists;
    input.count = 5;

    printf("Original:\n");
    print_list_of_lists(&input);

    if (remove_duplicates(&input, &output) != 0) {
        fprintf(stderr, "Failed to remove duplicates\n");
        return EXIT_FAILURE;
    }

    printf("Deduplicated:\n");
    print_list_of_lists(&output);

    free_list_of_lists(&output);

    return EXIT_SUCCESS;
}