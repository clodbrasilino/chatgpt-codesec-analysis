#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} IntList;

typedef struct {
    IntList *lists;
    size_t count;
} ListOfLists;

int merge_first_last(const ListOfLists *input, IntList *firsts, IntList *lasts)
{
    size_t i;

    if (input == NULL || firsts == NULL || lasts == NULL) {
        return -1;
    }

    if (input->count == 0) {
        firsts->data = NULL;
        firsts->size = 0;
        lasts->data = NULL;
        lasts->size = 0;
        return 0;
    }

    firsts->data = malloc(input->count * sizeof(int));
    if (firsts->data == NULL) {
        return -1;
    }

    lasts->data = malloc(input->count * sizeof(int));
    if (lasts->data == NULL) {
        free(firsts->data);
        firsts->data = NULL;
        return -1;
    }

    firsts->size = 0;
    lasts->size = 0;

    for (i = 0; i < input->count; i++) {
        if (input->lists[i].data == NULL || input->lists[i].size == 0) {
            free(firsts->data);
            free(lasts->data);
            firsts->data = NULL;
            lasts->data = NULL;
            firsts->size = 0;
            lasts->size = 0;
            return -1;
        }
        firsts->data[firsts->size] = input->lists[i].data[0];
        firsts->size++;
        lasts->data[lasts->size] = input->lists[i].data[input->lists[i].size - 1];
        lasts->size++;
    }

    return 0;
}

static void print_list(const IntList *list, const char *label)
{
    size_t i;

    if (list == NULL || label == NULL) {
        return;
    }

    printf("%s: [", label);
    for (i = 0; i < list->size; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d", list->data[i]);
    }
    printf("]\n");
}

int main(void)
{
    int row0[] = {1, 2, 3};
    int row1[] = {4, 5, 6};
    int row2[] = {7, 8, 9, 10};
    IntList rows[3];
    ListOfLists input;
    IntList firsts;
    IntList lasts;

    rows[0].data = row0;
    rows[0].size = sizeof(row0) / sizeof(row0[0]);
    rows[1].data = row1;
    rows[1].size = sizeof(row1) / sizeof(row1[0]);
    rows[2].data = row2;
    rows[2].size = sizeof(row2) / sizeof(row2[0]);

    input.lists = rows;
    input.count = 3;

    firsts.data = NULL;
    firsts.size = 0;
    lasts.data = NULL;
    lasts.size = 0;

    if (merge_first_last(&input, &firsts, &lasts) != 0) {
        fprintf(stderr, "Failed to merge lists\n");
        return EXIT_FAILURE;
    }

    print_list(&firsts, "First elements");
    print_list(&lasts, "Last elements");

    free(firsts.data);
    free(lasts.data);

    return EXIT_SUCCESS;
}