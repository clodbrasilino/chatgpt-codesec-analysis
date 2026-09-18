#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

#define MAX_LISTS 10

int count_lists(int* lists[]) {
    int count = 0;
    for (int i = 0; i < MAX_LISTS; ++i) {
        if (lists[i] != NULL) {
            ++count;
        }
    }
    return count;
}

int main() {
    int* lists[MAX_LISTS] = {0};  

    for(int i=0; i<5; ++i)
    {
        /* Possible weaknesses found:
         *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
         *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
         *  include '<stdlib.h>' or provide a declaration of 'malloc'
         */
        int* list = malloc(5 * sizeof(int));
        if(list == NULL)
        {
          printf("Memory allocation failed.\n");
          return 1;
        }
        lists[i] = list;
    }
    
    printf("Number of lists: %d\n", count_lists(lists));

    for(int i=0; i<5; ++i)
    {
        /* Possible weaknesses found:
         *  include '<stdlib.h>' or provide a declaration of 'free'
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
         */
        free(lists[i]);
        lists[i] = NULL;
    }

    return 0;
}