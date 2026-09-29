#include <stdio.h>
#include <stdlib.h>

static void reverse_list(int *list, size_t size)
{
    size_t left;
    size_t right;
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    int temp;

    if (list == NULL || size == 0) {
        return;
    }

    left = 0;
    right = size - 1;
    while (left < right) {
        temp = list[left];
        list[left] = list[right];
        list[right] = temp;
        left++;
        right--;
    }
}

static int reverse_each_list(int **lists, const size_t *sizes, size_t num_lists)
{
    size_t k;

    if (num_lists == 0) {
        return 0;
    }

    if (lists == NULL || sizes == NULL) {
        return -1;
    }

    for (k = 0; k < num_lists; k++) {
        if (lists[k] == NULL && sizes[k] > 0) {
            return -1;
        }
        reverse_list(lists[k], sizes[k]);
    }

    return 0;
}

static void print_lists(int *const *lists, const size_t *sizes, size_t num_lists)
{
    size_t k;
    size_t i;

    if (lists == NULL || sizes == NULL) {
        return;
    }

    for (k = 0; k < num_lists; k++) {
        printf("List %zu: [", k);
        for (i = 0; i < sizes[k]; i++) {
            printf("%d", lists[k][i]);
            if (i + 1 < sizes[k]) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

int main(void)
{
    const size_t num_lists = 3;
    int **lists;
    size_t *sizes;
    size_t k;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'value' can be reduced. [variableScope]
     */
    int value;
    int exit_code;

    lists = malloc(num_lists * sizeof(*lists));
    if (lists == NULL) {
        fprintf(stderr, "Error: failed to allocate list array\n");
        return EXIT_FAILURE;
    }

    sizes = malloc(num_lists * sizeof(*sizes));
    if (sizes == NULL) {
        fprintf(stderr, "Error: failed to allocate sizes array\n");
        free(lists);
        return EXIT_FAILURE;
    }

    sizes[0] = 5;
    sizes[1] = 3;
    sizes[2] = 4;

    for (k = 0; k < num_lists; k++) {
        lists[k] = NULL;
    }

    exit_code = EXIT_SUCCESS;

    for (k = 0; k < num_lists; k++) {
        lists[k] = malloc(sizes[k] * sizeof(*lists[k]));
        if (lists[k] == NULL) {
            fprintf(stderr, "Error: failed to allocate list %zu\n", k);
            exit_code = EXIT_FAILURE;
            break;
        }
    }

    if (exit_code == EXIT_SUCCESS) {
        value = 1;
        for (k = 0; k < num_lists; k++) {
            for (i = 0; i < sizes[k]; i++) {
                lists[k][i] = value;
                value++;
            }
        }

        printf("Before reversing:\n");
        print_lists(lists, sizes, num_lists);

        if (reverse_each_list(lists, sizes, num_lists) != 0) {
            fprintf(stderr, "Error: failed to reverse lists\n");
            exit_code = EXIT_FAILURE;
        } else {
            printf("After reversing:\n");
            print_lists(lists, sizes, num_lists);
        }
    }

    for (k = 0; k < num_lists; k++) {
        free(lists[k]);
        lists[k] = NULL;
    }
    free(lists);
    free(sizes);

    return exit_code;
}