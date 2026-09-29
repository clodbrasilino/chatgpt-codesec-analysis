#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

#define MAX_LENGTH 100

int** findMaxLists(int** arr, int rows) {
    int max_length = 0;
    int num_lists = 0;
    
    for (int i = 0; i < rows; i++) {
        int length = 0;
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        int* list = arr[i];
        
        /* Possible weaknesses found:
         *  Cannot determine that 'list' is initialized [premium-bughuntingUninit]
         */
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
    
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     */
    int** max_lists = (int**)malloc(num_lists * sizeof(int*));
    
    int index = 0;
    for (int i = 0; i < rows; i++) {
        int length = 0;
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        int* list = arr[i];
        
        /* Possible weaknesses found:
         *  Cannot determine that 'list' is initialized [premium-bughuntingUninit]
         */
        while (*list != -1) {
            length++;
            list++;
        }
        
        if (length == max_length) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'max_lists' is initialized [premium-bughuntingUninit]
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
    for (int i = 0; i < sizeof(max_lists) / sizeof(max_lists[0]); i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'max_lists' [CWE-690] [-Wanalyzer-possible-null-dereference]
         *  use of uninitialized value '*max_lists_31 + _2' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        int* list = max_lists[i];
        while (*list != -1) {
            printf("%d ", *list);
            list++;
        }
        printf("\n");
    }
    
    return 0;
}