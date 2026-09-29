#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t len;
} IntList;

typedef struct {
    IntList firsts;
    IntList lasts;
} MergeResult;

static int merge_first_last(const IntList *lists, size_t count, MergeResult *result)
{
    size_t i;

    if (lists == NULL || result == NULL || count == 0) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (lists[i].data == NULL || lists[i].len == 0) {
            return -1;
        }
    }

    result->firsts.data = malloc(count * sizeof(int));
    if (result->firsts.data == NULL) {
        return -1;
    }

    result->lasts.data = malloc(count * sizeof(int));
    if (result->lasts.data == NULL) {
        free(result->firsts.data);
        result->firsts.data = NULL;
        return -1;
    }

    for (i = 0; i < count; i++) {
        result->firsts.data[i] = lists[i].data[0];
        result->lasts.data[i] = lists[i].data[lists[i].len - 1];
    }

    result->firsts.len = count;
    result->lasts.len = count;

    return 0;
}

static void free_merge_result(MergeResult *result)
{
    if (result != NULL) {
        free(result->firsts.data);
        free(result->lasts.data);
        result->firsts.data = NULL;
        result->lasts.data = NULL;
        result->firsts.len = 0;
        result->lasts.len = 0;
    }
}

static void print_list(const IntList *list, const char *label)
{
    size_t i;

    if (list == NULL || list->data == NULL || label == NULL) {
        return;
    }

    printf("%s: [", label);
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
    int a[] = {1, 3};
    int b[] = {5, 7};
    int c[] = {9, 11};
    int d[] = {13, 15, 17};

    IntList lists[4];
    MergeResult result;
    int status;

    lists[0].data = a;
    lists[0].len = sizeof(a) / sizeof(a[0]);
    lists[1].data = b;
    lists[1].len = sizeof(b) / sizeof(b[0]);
    lists[2].data = c;
    lists[2].len = sizeof(c) / sizeof(c[0]);
    lists[3].data = d;
    lists[3].len = sizeof(d) / sizeof(d[0]);

    result.firsts.data = NULL;
    result.firsts.len = 0;
    result.lasts.data = NULL;
    result.lasts.len = 0;

    status = merge_first_last(lists, sizeof(lists) / sizeof(lists[0]), &result);
    if (status != 0) {
        fprintf(stderr, "Error: failed to merge lists\n");
        return EXIT_FAILURE;
    }

    print_list(&result.firsts, "First elements");
    print_list(&result.lasts, "Last elements");

    free_merge_result(&result);

    return EXIT_SUCCESS;
}