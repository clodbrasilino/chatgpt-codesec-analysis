#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t len;
} List;

static int lists_equal(const List *a, const List *b)
{
    if (a == NULL || b == NULL) {
        return 0;
    }
    if (a->len != b->len) {
        return 0;
    }
    if (a->len == 0U) {
        return 1;
    }
    if (a->data == NULL || b->data == NULL) {
        return 0;
    }
    return (memcmp(a->data, b->data, a->len * sizeof(int)) == 0) ? 1 : 0;
}

static int remove_duplicates(List *lists, size_t *count)
{
    size_t write_idx;
    size_t i;
    size_t j;

    if (lists == NULL || count == NULL) {
        return -1;
    }

    write_idx = 0U;
    for (i = 0U; i < *count; i++) {
        int is_duplicate = 0;
        for (j = 0U; j < write_idx; j++) {
            if (lists_equal(&lists[i], &lists[j]) == 1) {
                is_duplicate = 1;
                break;
            }
        }
        if (is_duplicate == 1) {
            free(lists[i].data);
            lists[i].data = NULL;
            lists[i].len = 0U;
        } else {
            if (write_idx != i) {
                lists[write_idx] = lists[i];
                lists[i].data = NULL;
                lists[i].len = 0U;
            }
            write_idx++;
        }
    }

    *count = write_idx;
    return 0;
}

static int make_list(List *out, const int *values, size_t len)
{
    size_t total_size;

    if (out == NULL) {
        return -1;
    }
    out->data = NULL;
    out->len = 0U;
    if (len == 0U) {
        return 0;
    }
    if (values == NULL) {
        return -1;
    }
    if (len > (SIZE_MAX / sizeof(int))) {
        return -1;
    }
    total_size = len * sizeof(int);
    out->data = (int *)malloc(total_size);
    if (out->data == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(out->data, values, total_size);
    out->len = len;
    return 0;
}

static void free_lists(List *lists, size_t count)
{
    size_t i;
    if (lists == NULL) {
        return;
    }
    for (i = 0U; i < count; i++) {
        free(lists[i].data);
        lists[i].data = NULL;
        lists[i].len = 0U;
    }
}

static void print_lists(const List *lists, size_t count)
{
    size_t i;
    size_t j;
    if (lists == NULL) {
        return;
    }
    for (i = 0U; i < count; i++) {
        printf("[");
        if (lists[i].data != NULL) {
            for (j = 0U; j < lists[i].len; j++) {
                printf("%d", lists[i].data[j]);
                if (j + 1U < lists[i].len) {
                    printf(", ");
                }
            }
        }
        printf("]\n");
    }
}

int main(void)
{
    List lists[5];
    size_t count = 5U;
    size_t created = 0U;
    size_t i;
    const int a[] = {1, 2, 3};
    const int b[] = {4, 5};
    const int c[] = {1, 2, 3};
    const int d[] = {6};
    const int e[] = {4, 5};

    if (make_list(&lists[0], a, sizeof(a) / sizeof(a[0])) != 0) {
        goto fail;
    }
    created = 1U;
    if (make_list(&lists[1], b, sizeof(b) / sizeof(b[0])) != 0) {
        goto fail;
    }
    created = 2U;
    if (make_list(&lists[2], c, sizeof(c) / sizeof(c[0])) != 0) {
        goto fail;
    }
    created = 3U;
    if (make_list(&lists[3], d, sizeof(d) / sizeof(d[0])) != 0) {
        goto fail;
    }
    created = 4U;
    if (make_list(&lists[4], e, sizeof(e) / sizeof(e[0])) != 0) {
        goto fail;
    }
    created = 5U;

    printf("Before:\n");
    print_lists(lists, count);

    if (remove_duplicates(lists, &count) != 0) {
        goto fail;
    }

    printf("After:\n");
    print_lists(lists, count);

    free_lists(lists, count);
    return EXIT_SUCCESS;

fail:
    for (i = 0U; i < created; i++) {
        free(lists[i].data);
        lists[i].data = NULL;
        /* Possible weaknesses found:
         *  Variable 'lists[i].len' is assigned a value that is never used. [unreadVariable]
         */
        lists[i].len = 0U;
    }
    fprintf(stderr, "Error: operation failed\n");
    return EXIT_FAILURE;
}