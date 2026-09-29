#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

int *find_similar_elements(Tuple *list1, int size1, Tuple *list2, int size2, int *result_size) {
    if (list1 == NULL || list2 == NULL || result_size == NULL) {
        return NULL;
    }
    
    int max_result_size = 0;
    for (int i = 0; i < size1; i++) {
        max_result_size += list1[i].size;
    }
    
    int *result = (int *)malloc(max_result_size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    
    int count = 0;
    
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < list1[i].size; j++) {
            int current = list1[i].elements[j];
            int found = 0;
            
            for (int k = 0; k < size2; k++) {
                for (int l = 0; l < list2[k].size; l++) {
                    if (list2[k].elements[l] == current) {
                        found = 1;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
            
            if (found) {
                int already_exists = 0;
                for (int m = 0; m < count; m++) {
                    if (result[m] == current) {
                        already_exists = 1;
                        break;
                    }
                }
                
                if (!already_exists) {
                    result[count++] = current;
                }
            }
        }
    }
    
    *result_size = count;
    
    if (count == 0) {
        free(result);
        return NULL;
    }
    
    int *final_result = (int *)realloc(result, count * sizeof(int));
    if (final_result == NULL) {
        free(result);
        return NULL;
    }
    
    return final_result;
}

void free_tuple_list(Tuple *list, int size) {
    if (list == NULL) {
        return;
    }
    
    for (int i = 0; i < size; i++) {
        free(list[i].elements);
    }
    free(list);
}

int main(void) {
    int elements1_1[] = {1, 2, 3, 4};
    int elements1_2[] = {5, 6, 7};
    int elements1_3[] = {8, 9, 10, 11, 12};
    
    Tuple tuple1_1 = {elements1_1, 4};
    Tuple tuple1_2 = {elements1_2, 3};
    Tuple tuple1_3 = {elements1_3, 5};
    
    Tuple *list1 = (Tuple *)malloc(3 * sizeof(Tuple));
    if (list1 == NULL) {
        return 1;
    }
    list1[0] = tuple1_1;
    list1[1] = tuple1_2;
    list1[2] = tuple1_3;
    
    int elements2_1[] = {3, 4, 5, 6};
    int elements2_2[] = {7, 8, 9};
    int elements2_3[] = {10, 11};
    int elements2_4[] = {12, 13, 14, 15, 16};
    
    Tuple tuple2_1 = {elements2_1, 4};
    Tuple tuple2_2 = {elements2_2, 3};
    Tuple tuple2_3 = {elements2_3, 2};
    Tuple tuple2_4 = {elements2_4, 5};
    
    Tuple *list2 = (Tuple *)malloc(4 * sizeof(Tuple));
    if (list2 == NULL) {
        free(list1);
        return 1;
    }
    list2[0] = tuple2_1;
    list2[1] = tuple2_2;
    list2[2] = tuple2_3;
    list2[3] = tuple2_4;
    
    int result_size = 0;
    int *similar = find_similar_elements(list1, 3, list2, 4, &result_size);
    
    if (similar != NULL) {
        printf("Similar elements: ");
        for (int i = 0; i < result_size; i++) {
            printf("%d ", similar[i]);
        }
        printf("\n");
        free(similar);
    } else {
        printf("No similar elements found or error occurred.\n");
    }
    
    free(list1);
    free(list2);
    
    return 0;
}