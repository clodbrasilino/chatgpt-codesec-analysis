#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **items;
    int *sizes;
    int count;
} ListOfLists;

void free_list_of_lists(ListOfLists l) {
    if (l.items != NULL) {
        for (int i = 0; i < l.count; i++) {
            free(l.items[i]);
        }
        free(l.items);
    }
    if (l.sizes != NULL) {
        free(l.sizes);
    }
}

ListOfLists zip_lists_of_lists(ListOfLists a, ListOfLists b) {
    ListOfLists result = {NULL, NULL, 0};
    int min_count = a.count < b.count ? a.count : b.count;
    if (min_count == 0) {
        return result;
    }

    result.items = malloc(min_count * sizeof(int *));
    if (result.items == NULL) {
        return result;
    }

    result.sizes = malloc(min_count * sizeof(int));
    if (result.sizes == NULL) {
        free(result.items);
        result.items = NULL;
        return result;
    }

    result.count = min_count;

    for (int i = 0; i < min_count; i++) {
        int min_size = a.sizes[i] < b.sizes[i] ? a.sizes[i] : b.sizes[i];
        int new_size = min_size * 2;
        result.sizes[i] = new_size;

        if (new_size == 0) {
            result.items[i] = NULL;
            continue;
        }

        result.items[i] = malloc(new_size * sizeof(int));
        if (result.items[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result.items[j]);
            }
            free(result.items);
            free(result.sizes);
            result.items = NULL;
            result.sizes = NULL;
            result.count = 0;
            return result;
        }

        for (int j = 0; j < min_size; j++) {
            result.items[i][2 * j] = a.items[i][j];
            result.items[i][2 * j + 1] = b.items[i][j];
        }
    }

    return result;
}

int main() {
    int a1[] = {1, 2};
    int a2[] = {3, 4, 5};
    int *a_items[] = {a1, a2};
    int a_sizes[] = {2, 3};
    ListOfLists a = {a_items, a_sizes, 2};

    int b1[] = {6, 7};
    int b2[] = {8, 9, 10};
    int *b_items[] = {b1, b2};
    int b_sizes[] = {2, 3};
    ListOfLists b = {b_items, b_sizes, 2};

    ListOfLists c = zip_lists_of_lists(a, b);

    for (int i = 0; i < c.count; i++) {
        for (int j = 0; j < c.sizes[i]; j++) {
            printf("%d ", c.items[i][j]);
        }
        printf("\n");
    }

    free_list_of_lists(c);

    return 0;
}