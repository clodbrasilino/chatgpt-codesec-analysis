#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Sublist;

typedef struct {
    Sublist *sublists;
    size_t count;
    size_t capacity;
} PackedList;

int init_packed_list(PackedList *pl, size_t initial_capacity) {
    if (pl == NULL || initial_capacity == 0) {
        return 0;
    }
    pl->sublists = (Sublist *)malloc(initial_capacity * sizeof(Sublist));
    if (pl->sublists == NULL) {
        return 0;
    }
    pl->count = 0;
    pl->capacity = initial_capacity;
    return 1;
}

int add_sublist(PackedList *pl, int value) {
    if (pl == NULL) {
        return 0;
    }
    if (pl->count == pl->capacity) {
        size_t new_capacity = pl->capacity * 2;
        Sublist *new_sublists = (Sublist *)realloc(pl->sublists, new_capacity * sizeof(Sublist));
        if (new_sublists == NULL) {
            return 0;
        }
        pl->sublists = new_sublists;
        pl->capacity = new_capacity;
    }
    pl->sublists[pl->count].data = (int *)malloc(sizeof(int));
    if (pl->sublists[pl->count].data == NULL) {
        return 0;
    }
    pl->sublists[pl->count].data[0] = value;
    pl->sublists[pl->count].size = 1;
    pl->count++;
    return 1;
}

int append_to_last_sublist(PackedList *pl, int value) {
    if (pl == NULL || pl->count == 0) {
        return 0;
    }
    Sublist *last = &pl->sublists[pl->count - 1];
    int *new_data = (int *)realloc(last->data, (last->size + 1) * sizeof(int));
    if (new_data == NULL) {
        return 0;
    }
    last->data = new_data;
    last->data[last->size] = value;
    last->size++;
    return 1;
}

PackedList *pack_consecutive_duplicates(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return NULL;
    }
    PackedList *result = (PackedList *)malloc(sizeof(PackedList));
    if (result == NULL) {
        return NULL;
    }
    if (!init_packed_list(result, 4)) {
        free(result);
        return NULL;
    }
    if (!add_sublist(result, arr[0])) {
        free(result->sublists);
        free(result);
        return NULL;
    }
    for (size_t i = 1; i < n; i++) {
        if (arr[i] == arr[i - 1]) {
            if (!append_to_last_sublist(result, arr[i])) {
                for (size_t j = 0; j < result->count; j++) {
                    free(result->sublists[j].data);
                }
                free(result->sublists);
                free(result);
                return NULL;
            }
        } else {
            if (!add_sublist(result, arr[i])) {
                for (size_t j = 0; j < result->count; j++) {
                    free(result->sublists[j].data);
                }
                free(result->sublists);
                free(result);
                return NULL;
            }
        }
    }
    return result;
}

void free_packed_list(PackedList *pl) {
    if (pl != NULL) {
        for (size_t i = 0; i < pl->count; i++) {
            free(pl->sublists[i].data);
        }
        free(pl->sublists);
        free(pl);
    }
}

void print_packed_list(const PackedList *pl) {
    if (pl == NULL) {
        printf("NULL\n");
        return;
    }
    printf("[");
    for (size_t i = 0; i < pl->count; i++) {
        printf("[");
        for (size_t j = 0; j < pl->sublists[i].size; j++) {
            printf("%d", pl->sublists[i].data[j]);
            if (j < pl->sublists[i].size - 1) {
                printf(", ");
            }
        }
        printf("]");
        if (i < pl->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    int arr[] = {1, 1, 2, 2, 2, 3, 1, 1, 4, 4, 4, 4};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    PackedList *packed = pack_consecutive_duplicates(arr, n);
    if (packed == NULL) {
        fprintf(stderr, "Error: Failed to pack list\n");
        return EXIT_FAILURE;
    }
    printf("Original: [");
    for (size_t i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    printf("Packed:   ");
    print_packed_list(packed);
    free_packed_list(packed);
    return EXIT_SUCCESS;
}