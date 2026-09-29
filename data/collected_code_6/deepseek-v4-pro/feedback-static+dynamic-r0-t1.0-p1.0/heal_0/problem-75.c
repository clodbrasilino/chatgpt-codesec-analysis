#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

Tuple *find_divisible_tuples(Tuple *tuples, int tuple_count, int k, int *result_count) {
    if (tuples == NULL || tuple_count <= 0 || k == 0) {
        *result_count = 0;
        return NULL;
    }
    
    Tuple *result = (Tuple *)malloc(tuple_count * sizeof(Tuple));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }
    
    int count = 0;
    
    for (int i = 0; i < tuple_count; i++) {
        if (tuples[i].elements == NULL || tuples[i].size <= 0) {
            continue;
        }
        
        int all_divisible = 1;
        for (int j = 0; j < tuples[i].size; j++) {
            if (tuples[i].elements[j] % k != 0) {
                all_divisible = 0;
                break;
            }
        }
        
        if (all_divisible) {
            result[count].size = tuples[i].size;
            result[count].elements = (int *)malloc(tuples[i].size * sizeof(int));
            if (result[count].elements == NULL) {
                for (int j = 0; j < count; j++) {
                    free(result[j].elements);
                }
                free(result);
                *result_count = 0;
                return NULL;
            }
            
            for (int j = 0; j < tuples[i].size; j++) {
                result[count].elements[j] = tuples[i].elements[j];
            }
            count++;
        }
    }
    
    if (count == 0) {
        free(result);
        *result_count = 0;
        return NULL;
    }
    
    Tuple *final_result = (Tuple *)realloc(result, count * sizeof(Tuple));
    if (final_result == NULL && count > 0) {
        for (int j = 0; j < count; j++) {
            free(result[j].elements);
        }
        free(result);
        *result_count = 0;
        return NULL;
    }
    
    *result_count = count;
    return final_result != NULL ? final_result : result;
}

void free_tuples(Tuple *tuples, int count) {
    if (tuples == NULL) {
        return;
    }
    
    for (int i = 0; i < count; i++) {
        if (tuples[i].elements != NULL) {
            free(tuples[i].elements);
        }
    }
    free(tuples);
}

int main(void) {
    int elements1[] = {3, 6, 9, 12};
    int elements2[] = {5, 10, 15, 20};
    int elements3[] = {7, 14, 21, 28};
    int elements4[] = {2, 4, 7, 8};
    
    Tuple tuples[4];
    tuples[0].elements = elements1;
    tuples[0].size = 4;
    tuples[1].elements = elements2;
    tuples[1].size = 4;
    tuples[2].elements = elements3;
    tuples[2].size = 4;
    tuples[3].elements = elements4;
    tuples[3].size = 4;
    
    int result_count = 0;
    int k = 3;
    
    Tuple *result = find_divisible_tuples(tuples, 4, k, &result_count);
    
    if (result == NULL || result_count == 0) {
        printf("No tuples found with all elements divisible by %d\n", k);
    } else {
        printf("Tuples with all elements divisible by %d:\n", k);
        for (int i = 0; i < result_count; i++) {
            printf("(");
            for (int j = 0; j < result[i].size; j++) {
                printf("%d", result[i].elements[j]);
                if (j < result[i].size - 1) {
                    printf(", ");
                }
            }
            printf(")\n");
        }
        free_tuples(result, result_count);
    }
    
    return 0;
}