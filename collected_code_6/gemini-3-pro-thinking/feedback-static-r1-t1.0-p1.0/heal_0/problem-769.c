#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <errno.h>

int get_list_difference(const int *list1, size_t size1, const int *list2, size_t size2, int **result, size_t *result_size) {
    if (!list1 || !list2 || !result || !result_size) {
        return EINVAL;
    }

    if (size1 == 0) {
        *result = NULL;
        *result_size = 0;
        return 0;
    }

    int *temp_result = malloc(size1 * sizeof(int));
    if (!temp_result) {
        return ENOMEM;
    }

    size_t count = 0;
    for (size_t i = 0; i < size1; i++) {
        bool found = false;
        for (size_t j = 0; j < size2; j++) {
            if (list1[i] == list2[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            temp_result[count++] = list1[i];
        }
    }

    if (count == 0) {
        free(temp_result);
        *result = NULL;
        *result_size = 0;
        return 0;
    }

    int *final_result = realloc(temp_result, count * sizeof(int));
    if (final_result != NULL) {
        *result = final_result;
    } else {
        *result = temp_result;
    }

    *result_size = count;
    return 0;
}

int main(void) {
    const int list1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    const int list2[] = {2, 4, 6, 8, 10};
    
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    
    int *result = NULL;
    size_t result_size = 0;
    
    int status = get_list_difference(list1, size1, list2, size2, &result, &result_size);
    
    if (status != 0) {
        fprintf(stderr, "Operation failed with error code: %d\n", status);
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < result_size; i++) {
        printf("%d\n", result[i]);
    }
    
    free(result);
    
    return EXIT_SUCCESS;
}