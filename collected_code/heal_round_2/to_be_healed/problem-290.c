#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 100

int** findMaxLists(int** arr, int rows) {
    int max_length = 0;
    int num_lists = 0;
    
    for (int i = 0; i < rows; i++) {
        int length = 0;
        int* list = arr[i];
        
        while (*list != -1) {
            length++;
            list++;
        }
        
        if (length > max_length) {
            max_length = length;
            num_lists = 1;
        }
        else if (length == max_length) {
            num_lists++;
        }
    }

    if(num_lists == 0)
        return NULL;
    
    int** max_lists = malloc(num_lists * sizeof(int*));
    
    int index = 0;
    for (int i = 0; i < rows; i++) {
        int length = 0;
        int* list = arr[i];
        
        while (*list != -1) {
            length++;
            list++;
        }
        
        if (length == max_length) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'max_lists' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            max_lists[index] = arr[i];
            index++;
        }
    }
    
    return max_lists;
}

int main() {
    int list1[] = {1, 2, 3, -1};
    int list2[] = {4, 5, -1};
    int list3[] = {6, 7, 8, -1};
    int list4[] = {9, -1};
    int list5[] = {-1};
    
    int* input[] = {list1, list2, list3, list4, list5};
    
    int** max_lists = findMaxLists(input, 5);
    
    printf("Lists with maximum length:\n");
    for (int i = 0; i < 2; i++) {

        /* Possible weaknesses found:
         *  use of uninitialized value '*max_lists_31 + _2' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         *  dereference of NULL 'max_lists' [CWE-476] [-Wanalyzer-null-dereference]
         *  dereference of possibly-NULL 'max_lists' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        int* list = max_lists[i];
        while (*list != -1) {
            printf("%d ", *list);
            list++;
        }
        printf("\n");
    }
    
    free(max_lists);
    
    return 0;
}