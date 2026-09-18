#include <stdio.h>

int* sumOfLists(int* list1, int* list2, int size) {
    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    int* sumList = malloc(size * sizeof(int));
    if(sumList == NULL) {
        printf("Memory not allocated.\n");
        /* Possible weaknesses found:
         *  include the header <stdlib.h> or explicitly provide a declaration for 'exit'
         *  call to undeclared library function 'exit' with type 'void (int) __attribute__((noreturn))'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
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
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    free(sumList);
    return 0;
}