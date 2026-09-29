#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int length;
    int *elements;
} List;

List** findMinLengthLists(List **lists, int size, int *resultSize) {
    int min = lists[0]->length;
    for(int i = 1; i < size; i++) {
        if(lists[i]->length < min) {
            min = lists[i]->length;
        }
    }

    List **result = malloc(sizeof(List*) * size);
    if (result == NULL) {
        return NULL;
    }

    *resultSize = 0;
    for(int i = 0; i < size; i++) {
        if(lists[i]->length == min) {
            result[(*resultSize)++] = lists[i];
        }
    }

    return result;
}

int main() {
    int size = 3;
    List **lists = malloc(sizeof(List*) * size);
    if (lists == NULL) {
        return -1;
    }

    for(int i = 0; i < size; i++) {
        lists[i] = malloc(sizeof(List));
        if (lists[i] == NULL) {
            for(int j = 0; j < i; j++){
                /* Possible weaknesses found:
                 *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
                 */
                free(lists[j]);
            }
            free(lists);
            return -1;
        }

        lists[i]->length = i + 1;
        lists[i]->elements = malloc(sizeof(int) * (i + 1));
        if (lists[i]->elements == NULL) {
            for(int j = 0; j <= i; j++){
                if(lists[j] != NULL){
                    /* Possible weaknesses found:
                     *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
                     */
                    free(lists[j]);
                }
            }
            free(lists);
            return -1;
        }
    }

    int resultSize;
    List **minLengthLists = findMinLengthLists(lists, size, &resultSize);
    if (minLengthLists == NULL) {
        for(int i = 0; i < size; i++){
            if(lists[i] != NULL){
                free(lists[i]->elements);
                free(lists[i]);
            }
        }
        free(lists);
        return -1;
    }

    printf("Lists with minimum length:\n");
    for(int i = 0; i < resultSize; i++) {
        printf("List %d, length: %d\n", i + 1, minLengthLists[i]->length);
    }

    for(int i = 0; i < size; i++) {
        if(lists[i] != NULL){
            free(lists[i]->elements);
            free(lists[i]);
        }
    }
    free(lists);
    free(minLengthLists);

    return 0;
}