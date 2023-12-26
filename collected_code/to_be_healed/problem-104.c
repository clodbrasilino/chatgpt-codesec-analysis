#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sortSublists(char*** lists, int numLists, int* listSizes) {
    for (int i = 0; i < numLists; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'listSizes[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        for (int j = 0; j < listSizes[i]; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'listSizes[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
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
    int listSizes[] = {3, 3, 4};
    
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'lists' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    lists[0] = list1;
    lists[1] = list2;
    lists[2] = list3;
    
    /* Possible weaknesses found:
     *  Cannot determine that 'lists' is initialized [premium-bughuntingUninit]
     */
    sortSublists(lists, 3, listSizes);
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < listSizes[i]; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'lists' is initialized [premium-bughuntingUninit]
             */
            printf("%s ", lists[i][j]);
        }
        printf("\n");
    }
    
    /* Possible weaknesses found:
     *  Cannot determine that 'lists' is initialized [premium-bughuntingUninit]
     */
    free(lists);
    
    return 0;
}