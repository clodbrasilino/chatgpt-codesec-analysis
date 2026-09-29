#include <stdio.h>
#include <stdlib.h>

int checkElements(int* list, int size) {
    if(list == NULL || size <= 0) {
        return -1;
    }

    int first = list[0];

    for(int i=1; i<size; i++) {
        if(list[i] != first) {
            return 0;
        }
    }
    
    return 1;
}

int main() {
    int size;
    printf("Enter the size of the list: ");
    scanf("%d", &size);

    if(size <= 0) {
        printf("Size must be a positive integer.\n");
        return -1;
    }

    int* list = (int*) malloc(size * sizeof(int));

    if(list == NULL) {
        printf("Failed to allocate memory.\n");
        return -1;
    }

    printf("Enter the elements of the list:\n");
    for(int i=0; i<size; i++) {
        scanf("%d", &list[i]);
    }

    int result = checkElements(list, size);

    if(result == -1) {
        printf("An error occurred.\n");
    } else if(result == 0) {
        printf("The elements in the list are not same.\n");
    } else {
        printf("The elements in the list are same.\n");
    }

    free(list);

    return 0;
}