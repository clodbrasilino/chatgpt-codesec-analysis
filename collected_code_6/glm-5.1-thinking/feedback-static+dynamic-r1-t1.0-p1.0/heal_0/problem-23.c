#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *data;
    size_t size;
} IntList;

typedef struct {
    IntList *lists;
    size_t count;
} ListOfLists;

int find_max_sum(const ListOfLists *lol) {
    if (lol == NULL || lol->count == 0) {
        return 0;
    }

    int max_sum = INT_MIN;

    for (size_t i = 0; i < lol->count; i++) {
        int current_sum = 0;
        IntList current = lol->lists[i];
        if (current.data != NULL) {
            for (size_t j = 0; j < current.size; j++) {
                current_sum += current.data[j];
            }
        }
        if (i == 0 || current_sum > max_sum) {
            max_sum = current_sum;
        }
    }

    return max_sum;
}

int main(void) {
    ListOfLists lol;
    lol.count = 3;
    lol.lists = malloc(lol.count * sizeof(IntList));
    if (lol.lists == NULL) {
        return EXIT_FAILURE;
    }

    lol.lists[0].size = 4;
    lol.lists[0].data = malloc(lol.lists[0].size * sizeof(int));
    if (lol.lists[0].data == NULL) {
        free(lol.lists);
        return EXIT_FAILURE;
    }
    lol.lists[0].data[0] = 1;
    lol.lists[0].data[1] = 2;
    lol.lists[0].data[2] = 3;
    lol.lists[0].data[3] = 4;

    lol.lists[1].size = 3;
    lol.lists[1].data = malloc(lol.lists[1].size * sizeof(int));
    if (lol.lists[1].data == NULL) {
        free(lol.lists[0].data);
        free(lol.lists);
        return EXIT_FAILURE;
    }
    lol.lists[1].data[0] = 10;
    lol.lists[1].data[1] = -5;
    lol.lists[1].data[2] = 2;

    lol.lists[2].size = 2;
    lol.lists[2].data = malloc(lol.lists[2].size * sizeof(int));
    if (lol.lists[2].data == NULL) {
        free(lol.lists[1].data);
        free(lol.lists[0].data);
        free(lol.lists);
        return EXIT_FAILURE;
    }
    lol.lists[2].data[0] = -1;
    lol.lists[2].data[1] = -2;

    int max = find_max_sum(&lol);
    printf("%d\n", max);

    free(lol.lists[2].data);
    free(lol.lists[1].data);
    free(lol.lists[0].data);
    free(lol.lists);

    return EXIT_SUCCESS;
}