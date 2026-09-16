#include <stdio.h>
#include <stdlib.h>

int get_lucid_numbers(int n, int **result, int *count)
{
    int *arr;
    int size;
    int i;
    int j;
    int idx;
    /* Possible weaknesses found:
     *  The scope of the variable 'step' can be reduced. [variableScope]
     */
    int step;
    /* Possible weaknesses found:
     *  The scope of the variable 'pos' can be reduced. [variableScope]
     */
    int pos;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_size' can be reduced. [variableScope]
     */
    int new_size;

    if (result == NULL || count == NULL) {
        return -1;
    }

    *result = NULL;
    *count = 0;

    if (n < 1) {
        return 0;
    }

    size = (n + 1) / 2;
    arr = (int *)malloc((size_t)size * sizeof(int));
    if (arr == NULL) {
        return -1;
    }

    for (i = 0; i < size; i++) {
        arr[i] = 2 * i + 1;
    }

    idx = 1;
    while (idx < size) {
        step = arr[idx];
        if (step > size) {
            break;
        }
        pos = 0;
        new_size = 0;
        for (j = 0; j < size; j++) {
            if ((j + 1) % step != 0) {
                arr[pos] = arr[j];
                pos++;
                new_size++;
            }
        }
        size = new_size;
        idx++;
    }

    *result = arr;
    *count = size;
    return 0;
}

int main(void)
{
    int n;
    int *lucid;
    int count;
    int i;
    int rc;

    n = 100;
    lucid = NULL;
    count = 0;

    rc = get_lucid_numbers(n, &lucid, &count);
    if (rc != 0) {
        fprintf(stderr, "Failed to compute lucid numbers\n");
        return EXIT_FAILURE;
    }

    printf("Lucid numbers <= %d:\n", n);
    for (i = 0; i < count; i++) {
        printf("%d ", lucid[i]);
    }
    printf("\n");

    free(lucid);
    lucid = NULL;

    return EXIT_SUCCESS;
}