#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t len;
} List;

typedef struct {
    List *lists;
    size_t len;
} ListOfLists;

bool lists_equal(List a, List b) {
    if (a.len != b.len) {
        return false;
    }
    for (size_t i = 0; i < a.len; i++) {
        if (a.data[i] != b.data[i]) {
            return false;
        }
    }
    return true;
}

ListOfLists remove_duplicates(ListOfLists input) {
    if (input.lists == NULL || input.len == 0) {
        ListOfLists empty = {NULL, 0};
        return empty;
    }

    bool *keep = calloc(input.len, sizeof(bool));
    if (keep == NULL) {
        ListOfLists empty = {NULL, 0};
        return empty;
    }

    for (size_t i = 0; i < input.len; i++) {
        keep[i] = true;
    }

    for (size_t i = 0; i < input.len; i++) {
        if (!keep[i]) {
            continue;
        }
        for (size_t j = i + 1; j < input.len; j++) {
            if (keep[j] && lists_equal(input.lists[i], input.lists[j])) {
                keep[j] = false;
            }
        }
    }

    size_t new_len = 0;
    for (size_t i = 0; i < input.len; i++) {
        if (keep[i]) {
            new_len++;
        }
    }

    List *new_lists = NULL;
    if (new_len > 0) {
        new_lists = malloc(new_len * sizeof(List));
        if (new_lists == NULL) {
            free(keep);
            ListOfLists empty = {NULL, 0};
            return empty;
        }
    }

    size_t current = 0;
    for (size_t i = 0; i < input.len; i++) {
        if (keep[i]) {
            new_lists[current] = input.lists[i];
            current++;
        }
    }

    free(keep);
    free(input.lists);

    ListOfLists result;
    result.lists = new_lists;
    result.len = new_len;
    return result;
}

void free_list_of_lists(ListOfLists lol) {
    if (lol.lists == NULL) {
        return;
    }
    for (size_t i = 0; i < lol.len; i++) {
        free(lol.lists[i].data);
    }
    free(lol.lists);
}

int main(void) {
    List a = { .data = malloc(3 * sizeof(int)), .len = 3 };
    if (a.data == NULL) return 1;
    a.data[0] = 1; a.data[1] = 2; a.data[2] = 3;

    List b = { .data = malloc(2 * sizeof(int)), .len = 2 };
    if (b.data == NULL) { free(a.data); return 1; }
    b.data[0] = 4; b.data[1] = 5;

    List c = { .data = malloc(3 * sizeof(int)), .len = 3 };
    if (c.data == NULL) { free(a.data); free(b.data); return 1; }
    c.data[0] = 1; c.data[1] = 2; c.data[2] = 3;

    List d = { .data = malloc(1 * sizeof(int)), .len = 1 };
    if (d.data == NULL) { free(a.data); free(b.data); free(c.data); return 1; }
    d.data[0] = 9;

    List e = { .data = malloc(2 * sizeof(int)), .len = 2 };
    if (e.data == NULL) { free(a.data); free(b.data); free(c.data); free(d.data); return 1; }
    e.data[0] = 4; e.data[1] = 5;

    ListOfLists lol;
    lol.len = 5;
    lol.lists = malloc(lol.len * sizeof(List));
    if (lol.lists == NULL) {
        free(a.data); free(b.data); free(c.data); free(d.data); free(e.data);
        return 1;
    }
    lol.lists[0] = a;
    lol.lists[1] = b;
    lol.lists[2] = c;
    lol.lists[3] = d;
    lol.lists[4] = e;

    ListOfLists unique = remove_duplicates(lol);

    for (size_t i = 0; i < unique.len; i++) {
        printf("[");
        for (size_t j = 0; j < unique.lists[i].len; j++) {
            printf("%d", unique.lists[i].data[j]);
            if (j < unique.lists[i].len - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }

    free_list_of_lists(unique);

    return 0;
}