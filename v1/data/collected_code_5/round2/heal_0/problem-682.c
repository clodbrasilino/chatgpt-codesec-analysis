#include <stdio.h>
#include <stdlib.h>

// Function to multiply two lists
int* multiplyLists(int* list1, int* list2, int size){
    int* resultList = (int*)malloc(size * sizeof(int));
    if(resultList == NULL) {
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
 
    for(int i=0; i<size; i++){
        resultList[i] = list1[i] * list2[i];
    }
    return resultList;  
}

// Main function
int main() {
    int size = 5;
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {6, 7, 8, 9, 10};

    int* resultList = multiplyLists(list1, list2, size);

    printf("Resulting list is: ");
    for(int i=0; i<size; i++){
        printf("%d ", resultList[i]);
    }

    free(resultList);
    return 0;
}