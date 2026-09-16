#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t len;
} IntList;

typedef struct {
    IntList *lists;
    size_t count;
} ListOfLists;

IntList create_int_list(const int *src, size_t len) {
    IntList list;
    list.len = 0;
    list.data = NULL;
    if (len > 0 && src != NULL) {
        list.data = malloc(len * sizeof(int));
        if (list.data != NULL) {
            list.len = len;
            for (size_t i = 0; i < len; i++) {
                list.data[i] = src[i];
            }
        }
    }
    return list;
}

void free_list_of_lists(ListOfLists *lol) {
    if (lol != NULL && lol->lists != NULL) {
        for (size_t i = 0; i < lol->count; i++) {
            free(lol->lists[i].data);
            lol->lists[i].data = NULL;
            lol->lists[i].len = 0;
        }
        free(lol->lists);
        lol->lists = NULL;
        lol->count = 0;
    }
}

bool are_lists_equal(IntList a, IntList b) {
    if (a.len != b.len) return false;
    for (size_t i = 0; i < a.len; i++) {
        if (a.data[i] != b.data[i]) return false;
    }
    return true;
}

int remove_duplicates(ListOfLists *lol) {
    if (lol == NULL) return -1;
    if (lol->count == 0 || lol->lists == NULL) return 0;

    bool *is_duplicate = calloc(lol->count, sizeof(bool));
    if (is_duplicate == NULL) return -1;

    for (size_t i = 0; i < lol->count; i++) {
        if (is_duplicate[i]) continue;
        for (size_t j = i + 1; j < lol->count; j++) {
            if (!is_duplicate[j] && are_lists_equal(lol->lists[i], lol->lists[j])) {
                is_duplicate[j] = true;
            }
        }
    }

    size_t unique_count = 0;
    for (size_t i = 0; i < lol->count; i++) {
        if (!is_duplicate[i]) {
            lol->lists[unique_count++] = lol->lists[i];
        } else {
            free(lol->lists[i].data);
            lol->lists[i].data = NULL;
            lol->lists[i].len = 0;
        }
    }

    free(is_duplicate);
    lol->count = unique_count;

    if (unique_count > 0) {
        IntList *temp = realloc(lol->lists, unique_count * sizeof(IntList));
        if (temp != NULL) {
            lol->lists = temp;
        }
    } else {
        free(lol->lists);
        lol->lists = NULL;
    }

    return 0;
}

int main(void) {
    int a1[] = {1, 2, 3};
    int a2[] = {4, 5};
    int a3[] = {1, 2, 3};
    int a4[] = {1, 2, 4};
    int a5[] = {4, 5};

    ListOfLists lol;
    lol.count = 5;
    lol.lists = malloc(lol.count * sizeof(IntList));
    if (lol.lists == NULL) return EXIT_FAILURE;

    lol.lists[0] = create_int_list(a1, 3);
    lol.lists[1] = create_int_list(a2, 2);
    lol.lists[2] = create_int_list(a3, 3);
    lol.lists[3] = create_int_list(a4, 3);
    lol.lists[4] = create_int_list(a5, 2);

    if (remove_duplicates(&lol) != 0) {
        free_list_of_lists(&lol);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < lol.count; i++) {
        printf("[");
        for (size_t j = 0; j < lol.lists[i].len; j++) {
            printf("%d", lol.lists[i].data[j]);
            if (j < lol.lists[i].len - 1) printf(", ");
        }
        printf("]\n");
    }

    free_list_of_lists(&lol);
    return EXIT_SUCCESS;
}