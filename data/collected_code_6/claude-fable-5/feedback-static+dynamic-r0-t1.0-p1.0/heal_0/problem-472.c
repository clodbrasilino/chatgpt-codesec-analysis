#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

static bool is_consecutive(const int *list, size_t n)
{
    int *copy = NULL;
    size_t i;
    bool result = true;

    if (list == NULL || n == 0) {
        return false;
    }

    if (n == 1) {
        return true;
    }

    copy = malloc(n * sizeof(*copy));
    if (copy == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n; i++) {
        copy[i] = list[i];
    }

    qsort(copy, n, sizeof(*copy), compare_ints);

    for (i = 1; i < n; i++) {
        if (copy[i - 1] == INT_MAX || copy[i] != copy[i - 1] + 1) {
            result = false;
            break;
        }
    }

    free(copy);
    return result;
}

int main(void)
{
    int list1[] = {5, 3, 4, 1, 2};
    int list2[] = {4, 6, 7, 8};
    int list3[] = {10};
    size_t n1 = sizeof(list1) / sizeof(list1[0]);
    size_t n2 = sizeof(list2) / sizeof(list2[0]);
    size_t n3 = sizeof(list3) / sizeof(list3[0]);

    if (printf("List 1 consecutive: %s\n", is_consecutive(list1, n1) ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }
    if (printf("List 2 consecutive: %s\n", is_consecutive(list2, n2) ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }
    if (printf("List 3 consecutive: %s\n", is_consecutive(list3, n3) ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}