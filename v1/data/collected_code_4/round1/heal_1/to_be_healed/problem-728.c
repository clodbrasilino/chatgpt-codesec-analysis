#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

int* sumOfLists(int* list1, int* list2, int size) {
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     */
    int* sumList = malloc(size * sizeof(int));
    if(sumList == NULL) {
        printf("Memory not allocated.\n");
        /* Possible weaknesses found:
         *  include '<stdlib.h>' or provide a declaration of 'exit'
         *  incompatible implicit declaration of built-in function 'exit' [-Wbuiltin-declaration-mismatch]
         *  implicit declaration of function 'exit' [-Wimplicit-function-declaration]
         */
        exit(0);
    }

    for(int i=0; i<size; i++) {
        sumList[i] = list1[i] + list2[i];
    }
    return sumList;
}

int main() {
    int size = 5;
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {6, 7, 8, 9, 10};

    int* sumList = sumOfLists(list1, list2, size);
    if (sumList == NULL) {
        printf("Summation failed.\n");
        return -1;
    }

    for(int i=0; i<size; i++) {
        printf("%d ", sumList[i]);
    }
    printf("\n");

    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     */
    free(sumList);
    return 0;
}