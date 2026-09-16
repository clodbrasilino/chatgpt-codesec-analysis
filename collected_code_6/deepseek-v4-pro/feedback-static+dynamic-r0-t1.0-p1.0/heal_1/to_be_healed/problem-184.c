#include <stdio.h>
#include <stdlib.h>

int* find_greater_values(const int* list, int list_size, int threshold, int* result_size) {
    /* Possible weaknesses found:
     *  Assuming that condition 'result_size==NULL' is not redundant
     */
    if (list == NULL || list_size <= 0 || result_size == NULL) {
        /* Possible weaknesses found:
         *  Either the condition 'result_size==NULL' is redundant or there is possible null pointer dereference: result_size. [nullPointerRedundantCheck]
         *  Null pointer dereference
         */
        *result_size = 0;
        return NULL;
    }

    int count = 0;
    int i;
    for (i = 0; i < list_size; i++) {
        if (list[i] > threshold) {
            count++;
        }
    }

    if (count == 0) {
        *result_size = 0;
        return NULL;
    }

    int* result = (int*)malloc((size_t)count * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    int index = 0;
    for (i = 0; i < list_size; i++) {
        if (list[i] > threshold) {
            result[index++] = list[i];
        }
    }

    *result_size = count;
    return result;
}

int main(void) {
    int test_list[] = {5, 12, 3, 19, 7, 22, 1, 15};
    int list_size = (int)(sizeof(test_list) / sizeof(test_list[0]));
    int threshold = 10;
    int result_size = 0;
    int* greater_values = find_greater_values(test_list, list_size, threshold, &result_size);

    if (greater_values != NULL) {
        int i;
        for (i = 0; i < result_size; i++) {
            printf("%d ", greater_values[i]);
        }
        printf("\n");
        free(greater_values);
    } else {
        printf("No values greater than %d found.\n", threshold);
    }

    return 0;
}