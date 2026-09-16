#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void *data;
    size_t size;
} Tuple;

typedef struct {
    int *counts;
    int length;
} CountResult;

int compare_items(const void *a, const void *b, size_t size) {
    return memcmp(a, b, size);
}

/* Possible weaknesses found:
 *  Parameter 'item' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'found_indices' can be declared as pointer to const [constParameterPointer]
 */
int find_item(Tuple *tuple, int tuple_len, void *item, size_t size, int *found_indices, int found_count) {
    for (int i = 0; i < tuple_len; i++) {
        int already_counted = 0;
        for (int j = 0; j < found_count; j++) {
            if (found_indices[j] == i) {
                already_counted = 1;
                break;
            }
        }
        if (!already_counted && compare_items(tuple[i].data, item, size) == 0) {
            return i;
        }
    }
    return -1;
}

CountResult count_repeated(Tuple *tuple, int tuple_len, size_t item_size) {
    CountResult result;
    result.length = 0;
    result.counts = (int *)malloc(sizeof(int) * tuple_len);
    
    if (result.counts == NULL) {
        result.length = -1;
        return result;
    }
    
    int *processed = (int *)calloc(tuple_len, sizeof(int));
    if (processed == NULL) {
        free(result.counts);
        result.length = -1;
        return result;
    }
    
    for (int i = 0; i < tuple_len; i++) {
        if (processed[i]) {
            continue;
        }
        
        int count = 1;
        for (int j = i + 1; j < tuple_len; j++) {
            if (!processed[j] && compare_items(tuple[i].data, tuple[j].data, item_size) == 0) {
                count++;
                processed[j] = 1;
            }
        }
        
        processed[i] = 1;
        
        if (count > 1) {
            result.counts[result.length++] = count;
        }
    }
    
    free(processed);
    
    if (result.length == 0) {
        free(result.counts);
        result.counts = NULL;
    }
    
    return result;
}

void print_count_result(CountResult result) {
    if (result.length == -1) {
        printf("Error: Memory allocation failed\n");
        return;
    }
    
    if (result.length == 0) {
        printf("No repeated items found\n");
        return;
    }
    
    printf("Repeated item counts: ");
    for (int i = 0; i < result.length; i++) {
        printf("%d ", result.counts[i]);
    }
    printf("\n");
}

int main(void) {
    int values[] = {1, 2, 3, 2, 4, 1, 1, 5, 3};
    int tuple_len = sizeof(values) / sizeof(values[0]);
    
    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple) * tuple_len);
    if (tuple == NULL) {
        printf("Error: Memory allocation failed\n");
        return 1;
    }
    
    for (int i = 0; i < tuple_len; i++) {
        tuple[i].data = &values[i];
        tuple[i].size = sizeof(int);
    }
    
    CountResult result = count_repeated(tuple, tuple_len, sizeof(int));
    print_count_result(result);
    
    if (result.counts != NULL) {
        free(result.counts);
    }
    free(tuple);
    
    char str_values[][7] = {"apple", "banana", "apple", "cherry", "banana", "date"};
    int str_len = sizeof(str_values) / sizeof(str_values[0]);
    
    Tuple *str_tuple = (Tuple *)malloc(sizeof(Tuple) * str_len);
    if (str_tuple == NULL) {
        printf("Error: Memory allocation failed\n");
        return 1;
    }
    
    for (int i = 0; i < str_len; i++) {
        str_tuple[i].data = str_values[i];
        str_tuple[i].size = strlen(str_values[i]) + 1;
    }
    
    CountResult str_result = count_repeated(str_tuple, str_len, sizeof(char[7]));
    print_count_result(str_result);
    
    if (str_result.counts != NULL) {
        free(str_result.counts);
    }
    free(str_tuple);
    
    return 0;
}