#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t len;
} List;

List *find_min_length_list(List *lists, size_t num_lists);

int main(void) {
    size_t num_lists = 3;
    List *lists = malloc(num_lists * sizeof(List));
    if (lists == NULL) {
        return EXIT_FAILURE;
    }

    lists[0].len = 5;
    lists[0].data = malloc(lists[0].len * sizeof(int));
    if (lists[0].data == NULL) {
        free(lists);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < lists[0].len; i++) {
        lists[0].data[i] = (int)i;
    }

    lists[1].len = 2;
    lists[1].data = malloc(lists[1].len * sizeof(int));
    if (lists[1].data == NULL) {
        free(lists[0].data);
        free(lists);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < lists[1].len; i++) {
        lists[1].data[i] = (int)i + 10;
    }

    lists[2].len = 4;
    lists[2].data = malloc(lists[2].len * sizeof(int));
    if (lists[2].data == NULL) {
        free(lists[1].data);
        free(lists[0].data);
        free(lists);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < lists[2].len; i++) {
        lists[2].data[i] = (int)i + 20;
    }

    List *min_list = find_min_length_list(lists, num_lists);
    if (min_list != NULL) {
        printf("Minimum length: %zu\n", min_list->len);
        printf("Data: ");
        for (size_t i = 0; i < min_list->len; i++) {
            printf("%d ", min_list->data[i]);
        }
        printf("\n");
    }

    free(lists[0].data);
    free(lists[1].data);
    free(lists[2].data);
    free(lists);

    return EXIT_SUCCESS;
}

List *find_min_length_list(List *lists, size_t num_lists) {
    if (lists == NULL || num_lists == 0) {
        return NULL;
    }

    size_t min_len = lists[0].len;
    List *min_list = &lists[0];

    for (size_t i = 1; i < num_lists; i++) {
        if (lists[i].len < min_len) {
            min_len = lists[i].len;
            min_list = &lists[i];
        }
    }

    return min_list;
}