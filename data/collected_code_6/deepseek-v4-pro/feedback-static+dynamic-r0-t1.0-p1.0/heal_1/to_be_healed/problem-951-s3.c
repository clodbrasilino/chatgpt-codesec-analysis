#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

/* Possible weaknesses found:
 *  expected 'int *' but argument is of type 'int **'
 */
int max_of_similar_indices(Tuple *list1, int size1, Tuple *list2, int size2, int *result, int *result_size) {
    if (list1 == NULL || list2 == NULL || result == NULL || result_size == NULL) {
        return -1;
    }
    
    if (size1 <= 0 || size2 <= 0) {
        *result_size = 0;
        return 0;
    }
    
    int min_size = size1 < size2 ? size1 : size2;
    int *temp_result = (int *)malloc(min_size * sizeof(int));
    
    if (temp_result == NULL) {
        return -1;
    }
    
    for (int i = 0; i < min_size; i++) {
        int max_val = list1[i].first;
        
        if (list1[i].second > max_val) {
            max_val = list1[i].second;
        }
        
        if (list2[i].first > max_val) {
            max_val = list2[i].first;
        }
        
        if (list2[i].second > max_val) {
            max_val = list2[i].second;
        }
        
        temp_result[i] = max_val;
    }
    
    *result = *temp_result;
    *result_size = min_size;
    
    free(temp_result);
    
    return 0;
}

int main(void) {
    Tuple list1[] = {
        {1, 5},
        {3, 7},
        {9, 2},
        {4, 6}
    };
    
    Tuple list2[] = {
        {8, 3},
        {1, 10},
        {5, 12}
    };
    
    int *result = NULL;
    int result_size = 0;
    
    /* Possible weaknesses found:
     *  passing argument 5 of 'max_of_similar_indices' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    int status = max_of_similar_indices(list1, 4, list2, 3, &result, &result_size);
    
    if (status == 0 && result != NULL) {
        printf("Maximum values at similar indices:\n");
        for (int i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("Error processing lists\n");
    }
    
    return 0;
}