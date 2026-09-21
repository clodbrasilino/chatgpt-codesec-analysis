#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef struct IntList {
    int *data;
    size_t length;
} IntList;

typedef struct ListOfLists {
    IntList *lists;
    size_t count;
} ListOfLists;

typedef struct ResultLists {
    IntList *lists;
    size_t count;
} ResultLists;

static void free_int_list(IntList *list) {
    if (list != NULL) {
        free(list->data);
        list->data = NULL;
        list->length = 0U;
    }
}

static void free_list_of_lists(ListOfLists *lol) {
    if (lol != NULL) {
        if (lol->lists != NULL) {
            for (size_t i = 0U; i < lol->count; i++) {
                free_int_list(&lol->lists[i]);
            }
            free(lol->lists);
            lol->lists = NULL;
        }
        lol->count = 0U;
    }
}

static void free_result_lists(ResultLists *result) {
    if (result != NULL) {
        if (result->lists != NULL) {
            for (size_t i = 0U; i < result->count; i++) {
                free_int_list(&result->lists[i]);
            }
            free(result->lists);
            result->lists = NULL;
        }
        result->count = 0U;
    }
}

static int copy_int_list(const IntList *src, IntList *dst) {
    if (src == NULL || dst == NULL) {
        return -1;
    }
    if (src->length > 0U && src->data == NULL) {
        return -1;
    }
    if (src->length > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    dst->length = 0U;
    dst->data = NULL;
    if (src->length > 0U) {
        size_t bytes = src->length * sizeof(int);
        if (bytes / sizeof(int) != src->length) {
            return -1;
        }
        int *new_data = (int *)malloc(bytes);
        if (new_data == NULL) {
            return -1;
        }
        if (src->data != NULL && bytes > 0U) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(new_data, src->data, bytes);
        }
        dst->data = new_data;
        dst->length = src->length;
    }
    return 0;
}

int find_min_length_lists(const ListOfLists *input, ResultLists *output) {
    if (input == NULL || output == NULL) {
        return -1;
    }
    output->lists = NULL;
    output->count = 0U;

    if (input->count == 0U || input->lists == NULL) {
        return 0;
    }

    size_t min_len = input->lists[0].length;
    for (size_t i = 1U; i < input->count; i++) {
        if (input->lists[i].length < min_len) {
            min_len = input->lists[i].length;
        }
    }

    size_t min_count = 0U;
    for (size_t i = 0U; i < input->count; i++) {
        if (input->lists[i].length == min_len) {
            min_count++;
        }
    }

    if (min_count > SIZE_MAX / sizeof(IntList)) {
        return -1;
    }

    output->lists = (IntList *)calloc(min_count, sizeof(IntList));
    if (output->lists == NULL) {
        return -1;
    }

    output->count = 0U;
    for (size_t i = 0U; i < input->count; i++) {
        if (input->lists[i].length == min_len) {
            if (copy_int_list(&input->lists[i], &output->lists[output->count]) != 0) {
                free_result_lists(output);
                return -1;
            }
            output->count++;
        }
    }

    return 0;
}

static int init_int_list(IntList *list, const int *values, size_t length) {
    if (list == NULL) {
        return -1;
    }
    if (length > 0U && values == NULL) {
        return -1;
    }
    if (length > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    list->length = 0U;
    list->data = NULL;
    if (length > 0U) {
        size_t bytes = length * sizeof(int);
        if (bytes / sizeof(int) != length) {
            return -1;
        }
        int *new_data = (int *)malloc(bytes);
        if (new_data == NULL) {
            return -1;
        }
        if (values != NULL && bytes > 0U) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(new_data, values, bytes);
        }
        list->data = new_data;
        list->length = length;
    }
    return 0;
}

static void print_int_list(const IntList *list) {
    if (list == NULL) {
        return;
    }
    printf("[");
    for (size_t j = 0U; j < list->length; j++) {
        printf("%d", list->data[j]);
        if (j + 1U < list->length) {
            printf(", ");
        }
    }
    printf("]");
}

int main(void) {
    const int a[] = {1, 2, 3};
    const int b[] = {4, 5};
    const int c[] = {6};
    const int d[] = {7, 8};
    const int e[] = {9};

    ListOfLists input;
    input.lists = (IntList *)calloc(5U, sizeof(IntList));
    if (input.lists == NULL) {
        fprintf(stderr, "Allocation failed\n");
        return EXIT_FAILURE;
    }
    input.count = 5U;

    if (init_int_list(&input.lists[0], a, 3U) != 0 ||
        init_int_list(&input.lists[1], b, 2U) != 0 ||
        init_int_list(&input.lists[2], c, 1U) != 0 ||
        init_int_list(&input.lists[3], d, 2U) != 0 ||
        init_int_list(&input.lists[4], e, 1U) != 0) {
        fprintf(stderr, "Initialization failed\n");
        free_list_of_lists(&input);
        return EXIT_FAILURE;
    }

    ResultLists result;
    result.lists = NULL;
    result.count = 0U;

    int status = find_min_length_lists(&input, &result);
    if (status != 0) {
        fprintf(stderr, "find_min_length_lists failed\n");
        free_list_of_lists(&input);
        return EXIT_FAILURE;
    }

    printf("Lists with minimum length (%zu):\n", result.count > 0U ? result.lists[0].length : 0U);
    for (size_t i = 0U; i < result.count; i++) {
        print_int_list(&result.lists[i]);
        printf("\n");
    }

    free_result_lists(&result);
    free_list_of_lists(&input);

    return EXIT_SUCCESS;
}