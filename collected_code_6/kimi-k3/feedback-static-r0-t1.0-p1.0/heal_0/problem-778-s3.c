#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Sublist;

typedef struct {
    Sublist *sublists;
    int count;
} PackedList;

PackedList pack_consecutive_duplicates(int *arr, int n) {
    PackedList result;
    result.count = 0;
    result.sublists = NULL;

    if (arr == NULL || n <= 0) {
        return result;
    }

    result.sublists = (Sublist *)malloc(n * sizeof(Sublist));
    if (result.sublists == NULL) {
        return result;
    }

    int i = 0;
    while (i < n) {
        int start = i;
        int value = arr[i];
        while (i < n && arr[i] == value) {
            i++;
        }
        int len = i - start;

        result.sublists[result.count].data = (int *)malloc(len * sizeof(int));
        if (result.sublists[result.count].data == NULL) {
            for (int j = 0; j < result.count; j++) {
                free(result.sublists[j].data);
            }
            free(result.sublists);
            result.sublists = NULL;
            result.count = 0;
            return result;
        }

        for (int j = 0; j < len; j++) {
            result.sublists[result.count].data[j] = value;
        }
        result.sublists[result.count].size = len;
        result.count++;
    }

    return result;
}

void free_packed_list(PackedList *pl) {
    if (pl == NULL) {
        return;
    }
    if (pl->sublists != NULL) {
        for (int i = 0; i < pl->count; i++) {
            free(pl->sublists[i].data);
        }
        free(pl->sublists);
        pl->sublists = NULL;
    }
    pl->count = 0;
}

void print_packed_list(PackedList *pl) {
    if (pl == NULL || pl->sublists == NULL) {
        printf("[]\n");
        return;
    }
    printf("[");
    for (int i = 0; i < pl->count; i++) {
        printf("[");
        for (int j = 0; j < pl->sublists[i].size; j++) {
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
    int arr[] = {1, 1, 2, 3, 3, 3, 4, 4, 5, 1, 1};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));

    printf("Original list: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    PackedList packed = pack_consecutive_duplicates(arr, n);

    printf("Packed list: ");
    print_packed_list(&packed);

    free_packed_list(&packed);

    return 0;
}