#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

int find_dissimilar(const Tuple *t1, const Tuple *t2, Tuple *result) {
    size_t i, j, k = 0;
    int found;
    size_t max_size;
    int *temp;

    if (t1 == NULL || t2 == NULL || result == NULL || t1->data == NULL || t2->data == NULL) {
        return -1;
    }

    max_size = t1->size + t2->size;
    if (max_size == 0) {
        result->data = NULL;
        result->size = 0;
        return 0;
    }

    temp = (int *)malloc(max_size * sizeof(int));
    if (temp == NULL) {
        return -1;
    }

    for (i = 0; i < t1->size; i++) {
        found = 0;
        for (j = 0; j < t2->size; j++) {
            if (t1->data[i] == t2->data[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            temp[k++] = t1->data[i];
        }
    }

    for (i = 0; i < t2->size; i++) {
        found = 0;
        for (j = 0; j < t1->size; j++) {
            if (t2->data[i] == t1->data[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            temp[k++] = t2->data[i];
        }
    }

    if (k == 0) {
        free(temp);
        result->data = NULL;
        result->size = 0;
        return 0;
    }

    result->data = (int *)malloc(k * sizeof(int));
    if (result->data == NULL) {
        free(temp);
        return -1;
    }

    for (i = 0; i < k; i++) {
        result->data[i] = temp[i];
    }
    result->size = k;

    free(temp);
    return 0;
}

int main(void) {
    Tuple t1, t2, result;
    int data1[] = {1, 2, 3, 4, 5};
    int data2[] = {4, 5, 6, 7, 8};
    size_t i;
    int status;

    t1.data = data1;
    t1.size = sizeof(data1) / sizeof(data1[0]);
    t2.data = data2;
    t2.size = sizeof(data2) / sizeof(data2[0]);
    result.data = NULL;
    result.size = 0;

    status = find_dissimilar(&t1, &t2, &result);
    if (status != 0) {
        fprintf(stderr, "Error: Failed to compute dissimilar elements\n");
        return EXIT_FAILURE;
    }

    printf("Dissimilar elements: ");
    for (i = 0; i < result.size; i++) {
        printf("%d ", result.data[i]);
    }
    printf("\n");

    free(result.data);
    result.data = NULL;
    result.size = 0;

    return EXIT_SUCCESS;
}