#include <stdio.h>
#include <stdlib.h>

// Function to compare elements for sorting list
int compare(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

void sortlist(int *list, int size){
    qsort(list, size, sizeof(int), compare);
}

int main(void) {
    
    int size, i;

    printf("Enter the size of the list: ");
    scanf("%d", &size);

    int *list = malloc(size * sizeof(int));

    if(list == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }

    printf("Enter the elements of the list: ");
    for(i=0; i<size; i++) {
        scanf("%d", &list[i]);
    }

    sortlist(list, size);

    printf("Sorted List: ");
    for(i=0; i<size; i++) {
        printf("%d ", list[i]);
    }

    free(list);
    
    return 0;
}