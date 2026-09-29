#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t length;
} SubList;

typedef struct {
    SubList *lists;
    size_t count;
} ListOfLists;

void free_list_of_lists(ListOfLists *lol) {
    if (!lol) {
        return;
    }
    if (lol->lists) {
        for (size_t i = 0; i < lol->count; i++) {
            free(lol->lists[i].elements);
        }
        free(lol->lists);
    }
    free(lol);
}

ListOfLists* get_max_length_lists(const ListOfLists *input) {
    if (!input || !input->lists || input->count == 0) {
        return NULL;
    }

    size_t max_len = 0;
    for (size_t i = 0; i < input->count; i++) {
        if (input->lists[i].length > max_len) {
            max_len = input->lists[i].length;
        }
    }

    size_t max_count = 0;
    for (size_t i = 0; i < input->count; i++) {
        if (input->lists[i].length == max_len) {
            max_count++;
        }
    }

    ListOfLists *result = malloc(sizeof(ListOfLists));
    if (!result) {
        return NULL;
    }

    result->count = max_count;
    result->lists = calloc(max_count, sizeof(SubList));
    if (!result->lists) {
        free(result);
        return NULL;
    }

    size_t idx = 0;
    for (size_t i = 0; i < input->count; i++) {
        if (input->lists[i].length == max_len) {
            result->lists[idx].length = max_len;
            if (max_len > 0 && input->lists[i].elements) {
                size_t dest_bytes = max_len * sizeof(int);
                result->lists[idx].elements = malloc(dest_bytes);
                if (!result->lists[idx].elements) {
                    result->count = idx;
                    free_list_of_lists(result);
                    return NULL;
                }
                
                size_t src_bytes = input->lists[i].length * sizeof(int);
                if (src_bytes <= dest_bytes) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result->lists[idx].elements, input->lists[i].elements, src_bytes);
                }
            } else {
                result->lists[idx].elements = NULL;
            }
            idx++;
        }
    }

    return result;
}

int main(void) {
    ListOfLists *input = malloc(sizeof(ListOfLists));
    if (!input) {
        return EXIT_FAILURE;
    }

    input->count = 4;
    input->lists = calloc(input->count, sizeof(SubList));
    if (!input->lists) {
        free(input);
        return EXIT_FAILURE;
    }

    int data1[] = {1, 2};
    int data2[] = {3, 4, 5};
    int data3[] = {6, 7};
    int data4[] = {8, 9, 10};

    input->lists[0].length = 2;
    input->lists[0].elements = malloc(2 * sizeof(int));
    
    input->lists[1].length = 3;
    input->lists[1].elements = malloc(3 * sizeof(int));
    
    input->lists[2].length = 2;
    input->lists[2].elements = malloc(2 * sizeof(int));
    
    input->lists[3].length = 3;
    input->lists[3].elements = malloc(3 * sizeof(int));

    if (!input->lists[0].elements || !input->lists[1].elements || 
        !input->lists[2].elements || !input->lists[3].elements) {
        free_list_of_lists(input);
        return EXIT_FAILURE;
    }

    size_t bytes;

    bytes = sizeof(data1);
    if (bytes <= input->lists[0].length * sizeof(int)) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(input->lists[0].elements, data1, bytes);
    }

    bytes = sizeof(data2);
    if (bytes <= input->lists[1].length * sizeof(int)) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(input->lists[1].elements, data2, bytes);
    }

    bytes = sizeof(data3);
    if (bytes <= input->lists[2].length * sizeof(int)) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(input->lists[2].elements, data3, bytes);
    }

    bytes = sizeof(data4);
    if (bytes <= input->lists[3].length * sizeof(int)) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(input->lists[3].elements, data4, bytes);
    }

    ListOfLists *result = get_max_length_lists(input);
    if (!result) {
        free_list_of_lists(input);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result->count; i++) {
        if (result->lists[i].elements) {
            for (size_t j = 0; j < result->lists[i].length; j++) {
                printf("%d ", result->lists[i].elements[j]);
            }
            printf("\n");
        }
    }

    free_list_of_lists(result);
    free_list_of_lists(input);

    return EXIT_SUCCESS;
}