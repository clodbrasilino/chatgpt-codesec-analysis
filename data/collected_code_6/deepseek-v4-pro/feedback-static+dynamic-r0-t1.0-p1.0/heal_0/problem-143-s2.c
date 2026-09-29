#include <stdio.h>

int count_lists(void *tuple) {
    int count = 0;
    void **ptr = (void **)tuple;
    
    while (*ptr != NULL) {
        if (*(int *)ptr == 1) {
            count++;
        }
        ptr++;
    }
    
    return count;
}

int main() {
    void *tuple[] = {(void *)1, (void *)0, (void *)1, (void *)1, NULL};
    
    printf("Number of lists: %d\n", count_lists(tuple));
    
    return 0;
}