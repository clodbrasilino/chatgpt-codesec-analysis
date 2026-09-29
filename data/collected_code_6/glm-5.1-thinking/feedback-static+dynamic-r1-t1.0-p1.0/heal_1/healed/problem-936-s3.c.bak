#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    int value;
} Tuple;

int rearrange_tuples(Tuple *tuples, int tuple_count, const int *order, int order_count) {
    if (tuples == NULL || order == NULL) {
        return -1;
    }
    if (tuple_count <= 0 || order_count <= 0) {
        return -1;
    }
    if (tuple_count != order_count) {
        return -1;
    }

    Tuple *temp = malloc(tuple_count * sizeof(Tuple));
    if (temp == NULL) {
        return -1;
    }

    for (int i = 0; i < order_count; i++) {
        int found = 0;
        for (int j = 0; j < tuple_count; j++) {
            if (tuples[j].key == order[i]) {
                temp[i] = tuples[j];
                found = 1;
                break;
            }
        }
        if (!found) {
            free(temp);
            return -1;
        }
    }

    memcpy(tuples, temp, tuple_count * sizeof(Tuple));
    free(temp);
    return 0;
}

int main(void) {
    Tuple tuples[] = {{3, 30}, {1, 10}, {2, 20}, {4, 40}};
    const int order[] = {2, 4, 1, 3};
    int count = 4;

    printf("Before:\n");
    for (int i = 0; i < count; i++) {
        printf("(%d, %d) ", tuples[i].key, tuples[i].value);
    }
    printf("\n");

    int result = rearrange_tuples(tuples, count, order, count);
    if (result != 0) {
        fprintf(stderr, "Failed to rearrange tuples\n");
        return 1;
    }

    printf("After:\n");
    for (int i = 0; i < count; i++) {
        printf("(%d, %d) ", tuples[i].key, tuples[i].value);
    }
    printf("\n");

    return 0;
}