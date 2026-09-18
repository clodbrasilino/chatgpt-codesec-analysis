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
        free(lists[i]);
        lists[i] = NULL;
    }

    return 0;
}