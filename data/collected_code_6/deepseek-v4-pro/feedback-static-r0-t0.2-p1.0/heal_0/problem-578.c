#include <stdio.h>
#include <stdlib.h>

int* interleave(int** lists, int num_lists, int list_length) {
    if (lists == NULL || num_lists <= 0 || list_length <= 0) {
        return NULL;
    }
    
    for (int i = 0; i < num_lists; i++) {
        if (lists[i] == NULL) {
            return NULL;
        }
    }
    
    int total_length = num_lists * list_length;
    int* result = (int*)malloc(total_length * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    
    int index = 0;
    for (int i = 0; i < list_length; i++) {
        for (int j = 0; j < num_lists; j++) {
            result[index++] = lists[j][i];
        }
    }
    
    return result;
}

int main(void) {
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5, 6};
    int list3[] = {7, 8, 9};
    
    int* lists[] = {list1, list2, list3};
    int num_lists = 3;
    int list_length = 3;
    
    int* result = interleave(lists, num_lists, list_length);
    if (result == NULL) {
        fprintf(stderr, "Error: Failed to interleave lists\n");
        return 1;
    }
    
    int total_length = num_lists * list_length;
    for (int i = 0; i < total_length; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    free(result);
    return 0;
}