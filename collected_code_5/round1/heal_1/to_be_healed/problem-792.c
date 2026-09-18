#include <stdio.h>

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
         *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
         *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
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
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        free(lists[i]);
        lists[i] = NULL;
    }

    return 0;
}