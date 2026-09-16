#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int value;
    int count;
} Frequency;

void find_frequency(int **lists, int num_lists, int *sizes, Frequency **result, int *result_size) {
    if (lists == NULL || sizes == NULL || result == NULL || result_size == NULL || num_lists < 0) {
        return;
    }
    
    int capacity = 16;
    int count = 0;
    Frequency *freq = malloc(capacity * sizeof(Frequency));
    if (freq == NULL) {
        *result = NULL;
        *result_size = 0;
        return;
    }
    
    for (int i = 0; i < num_lists; i++) {
        if (lists[i] == NULL || sizes[i] < 0) {
            continue;
        }
        
        for (int j = 0; j < sizes[i]; j++) {
            int val = lists[i][j];
            int found = 0;
            
            for (int k = 0; k < count; k++) {
                if (freq[k].value == val) {
                    freq[k].count++;
                    found = 1;
                    break;
                }
            }
            
            if (!found) {
                if (count >= capacity) {
                    int new_capacity = capacity * 2;
                    Frequency *temp = realloc(freq, new_capacity * sizeof(Frequency));
                    if (temp == NULL) {
                        free(freq);
                        *result = NULL;
                        *result_size = 0;
                        return;
                    }
                    freq = temp;
                    capacity = new_capacity;
                }
                freq[count].value = val;
                freq[count].count = 1;
                count++;
            }
        }
    }
    
    *result = freq;
    *result_size = count;
}

int main(void) {
    int list1[] = {1, 2, 3, 2, 1};
    int list2[] = {4, 5, 4, 2};
    int list3[] = {1, 1, 5, 6};
    
    int *lists[] = {list1, list2, list3};
    int sizes[] = {5, 4, 4};
    int num_lists = 3;
    
    Frequency *result = NULL;
    int result_size = 0;
    
    find_frequency(lists, num_lists, sizes, &result, &result_size);
    
    if (result != NULL) {
        printf("Element frequencies:\n");
        for (int i = 0; i < result_size; i++) {
            printf("%d: %d\n", result[i].value, result[i].count);
        }
        free(result);
    }
    
    return 0;
}