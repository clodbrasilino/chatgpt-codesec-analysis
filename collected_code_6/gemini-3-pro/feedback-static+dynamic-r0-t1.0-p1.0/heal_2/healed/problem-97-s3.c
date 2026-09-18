#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val;
    int count;
} FreqElement;

typedef struct {
    FreqElement *elements;
    size_t size;
    size_t capacity;
} FreqList;

FreqList* init_freq_list() {
    FreqList *list = malloc(sizeof(FreqList));
    if (!list) return NULL;
    list->size = 0;
    list->capacity = 10;
    list->elements = malloc(list->capacity * sizeof(FreqElement));
    if (!list->elements) {
        free(list);
        return NULL;
    }
    return list;
}

void add_freq(FreqList *list, int val) {
    if (!list) return;
    for (size_t i = 0; i < list->size; ++i) {
        if (list->elements[i].val == val) {
            list->elements[i].count++;
            return;
        }
    }
    if (list->size >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        FreqElement *new_elements = realloc(list->elements, new_capacity * sizeof(FreqElement));
        if (!new_elements) return;
        list->elements = new_elements;
        list->capacity = new_capacity;
    }
    list->elements[list->size].val = val;
    list->elements[list->size].count = 1;
    list->size++;
}

void free_freq_list(FreqList *list) {
    if (!list) return;
    free(list->elements);
    free(list);
}

FreqList* get_frequency_count(int **listOfLists, int numLists, const int *listSizes) {
    if (!listOfLists || !listSizes || numLists <= 0) return NULL;
    
    FreqList *freq_list = init_freq_list();
    if (!freq_list) return NULL;

    for (int i = 0; i < numLists; i++) {
        if (!listOfLists[i]) continue;
        for (int j = 0; j < listSizes[i]; j++) {
            add_freq(freq_list, listOfLists[i][j]);
        }
    }
    
    return freq_list;
}

int main(void) {
    int numLists = 3;
    const int listSizes[] = {3, 2, 4};
    
    int **listOfLists = malloc(numLists * sizeof(int*));
    if (!listOfLists) return EXIT_FAILURE;
    
    listOfLists[0] = malloc(3 * sizeof(int));
    if (listOfLists[0]) {
        listOfLists[0][0] = 1; listOfLists[0][1] = 2; listOfLists[0][2] = 3;
    }
    
    listOfLists[1] = malloc(2 * sizeof(int));
    if (listOfLists[1]) {
        listOfLists[1][0] = 2; listOfLists[1][1] = 4;
    }
    
    listOfLists[2] = malloc(4 * sizeof(int));
    if (listOfLists[2]) {
        listOfLists[2][0] = 1; listOfLists[2][1] = 2; listOfLists[2][2] = 5; listOfLists[2][3] = 4;
    }
    
    FreqList *freqCount = get_frequency_count(listOfLists, numLists, listSizes);
    
    if (freqCount) {
        for (size_t i = 0; i < freqCount->size; i++) {
            printf("Value: %d, Frequency: %d\n", freqCount->elements[i].val, freqCount->elements[i].count);
        }
        free_freq_list(freqCount);
    }
    
    for (int i = 0; i < numLists; i++) {
        free(listOfLists[i]);
    }
    free(listOfLists);
    
    return EXIT_SUCCESS;
}