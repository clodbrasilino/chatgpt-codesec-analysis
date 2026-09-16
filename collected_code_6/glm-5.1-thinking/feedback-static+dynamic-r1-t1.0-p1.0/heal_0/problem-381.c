#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *items;
    int length;
} List;

typedef struct {
    List *inner;
    int count;
} ListOfLists;

static void swap_lists(List *a, List *b) {
    List temp = *a;
    *a = *b;
    *b = temp;
}

static int partition(List *arr, int low, int high, int index) {
    int pivot_val = INT_MIN;
    if (arr[high].length > index) {
        pivot_val = arr[high].items[index];
    }
    
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        int current_val = INT_MIN;
        if (arr[j].length > index) {
            current_val = arr[j].items[index];
        }
        
        if (current_val < pivot_val) {
            i++;
            swap_lists(&arr[i], &arr[j]);
        }
    }
    swap_lists(&arr[i + 1], &arr[high]);
    return i + 1;
}

static void quicksort_lists(List *arr, int low, int high, int index) {
    if (low < high) {
        int pi = partition(arr, low, high, index);
        quicksort_lists(arr, low, pi - 1, index);
        quicksort_lists(arr, pi + 1, high, index);
    }
}

void sort_by_index(ListOfLists *lol, int index) {
    if (lol == NULL || lol->inner == NULL || lol->count < 2 || index < 0) {
        return;
    }
    quicksort_lists(lol->inner, 0, lol->count - 1, index);
}

int main(void) {
    int count = 3;
    int inner_len = 3;
    ListOfLists lol;
    lol.count = count;
    lol.inner = malloc(count * sizeof(List));
    if (!lol.inner) {
        return 1;
    }

    int data[9] = {5, 9, 2, 3, 1, 4, 8, 6, 7};

    for (int i = 0; i < count; i++) {
        lol.inner[i].length = inner_len;
        lol.inner[i].items = malloc(inner_len * sizeof(int));
        if (!lol.inner[i].items) {
            for (int j = 0; j < i; j++) {
                free(lol.inner[j].items);
            }
            free(lol.inner);
            return 1;
        }
        for (int k = 0; k < inner_len; k++) {
            lol.inner[i].items[k] = data[i * inner_len + k];
        }
    }

    sort_by_index(&lol, 1);

    for (int i = 0; i < lol.count; i++) {
        for (int j = 0; j < lol.inner[i].length; j++) {
            printf("%d ", lol.inner[i].items[j]);
        }
        printf("\n");
    }

    for (int i = 0; i < lol.count; i++) {
        free(lol.inner[i].items);
    }
    free(lol.inner);

    return 0;
}