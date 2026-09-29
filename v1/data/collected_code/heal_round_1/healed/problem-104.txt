#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sortSublists(char*** lists, const int numLists, const int* listSizes) {
    for (int i = 0; i < numLists; i++) {
        for (int j = 0; j < listSizes[i]; j++) {
            for (int k = 0; k < listSizes[i] - j - 1; k++) {
                if (strcmp(lists[i][k], lists[i][k + 1]) > 0) {
                    char* temp = lists[i][k];
                    lists[i][k] = lists[i][k + 1];
                    lists[i][k + 1] = temp;
                }
            }
        }
    }
}

int main() {
    char* list1[] = {"apple", "orange", "banana"};
    char* list2[] = {"cat", "dog", "bird"};
    char* list3[] = {"car", "bus", "bike", "train"};
    
    char*** lists = (char***) malloc(3 * sizeof(char**));
    if (lists == NULL) {
        return 1; // Failed to allocate memory
    }
    
    int listSizes[] = {3, 3, 4};
    lists[0] = list1;
    lists[1] = list2;
    lists[2] = list3;
    
    sortSublists(lists, 3, listSizes);
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < listSizes[i]; j++) {
            printf("%s ", lists[i][j]);
        }
        printf("\n");
    }
    
    free(lists);
    
    return 0;
}