#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t len;
} IntList;

int merge_first_last(const IntList *lists, size_t count, IntList *firsts, IntList *lasts)
{
    size_t i;

    if (lists == NULL || firsts == NULL || lasts == NULL || count == 0) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (lists[i].data == NULL || lists[i].len == 0) {
            return -1;
        }
    }

    firsts->data = malloc(count * sizeof(int));
    if (firsts->data == NULL) {
        return -1;
    }

    lasts->data = malloc(count * sizeof(int));
    if (lasts->data == NULL) {
        free(firsts->data);
        firsts->data = NULL;
        return -1;
    }

    for (i = 0; i < count; i++) {
        firsts->data[i] = lists[i].data[0];
        lasts->data[i] = lists[i].data[lists[i].len - 1];
    }

    firsts->len = count;
    lasts->len = count;

    return 0;
}

static void print_list(const IntList *list)
{
    size_t i;

    printf("[");
    for (i = 0; i < list->len; i++) {
        printf("%d", list->data[i]);
        if (i + 1 < list->len) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    int row0[] = {1, 2, 3};
    int row1[] = {4, 5, 6};
    int row2[] = {7, 8, 9, 10};
    IntList lists[3];
    IntList firsts = {NULL, 0};
    IntList lasts = {NULL, 0};

    lists[0].data = row0;
    lists[0].len = sizeof(row0) / sizeof(row0[0]);
    lists[1].data = row1;
    lists[1].len = sizeof(row1) / sizeof(row1[0]);
    lists[2].data = row2;
    lists[2].len = sizeof(row2) / sizeof(row2[0]);

    if (merge_first_last(lists, 3, &firsts, &lasts) != 0) {
        fprintf(stderr, "merge_first_last failed\n");
        return EXIT_FAILURE;
    }

    printf("First elements: ");
    print_list(&firsts);
    printf("Last elements: ");
    print_list(&lasts);

    free(firsts.data);
    free(lasts.data);
    firsts.data = NULL;
    lasts.data = NULL;

    return EXIT_SUCCESS;
}