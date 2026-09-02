#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Frequency;

int compare(const void *a, const void *b) {
    return ((Frequency *)a)->value - ((Frequency *)b)->value;
}

void find_frequencies(int *arr, int size, Frequency **freq, int *freq_size) {
    if (arr == NULL || size <= 0 || freq == NULL || freq_size == NULL) {
        return;
    }
    
    Frequency *result = malloc(size * sizeof(Frequency));
    if (result == NULL) {
        return;
    }
    
    int count = 0;
    int found;
    
    for (int i = 0; i < size; i++) {
        found = 0;
        for (int j = 0; j < count; j++) {
            if (result[j].value == arr[i]) {
                result[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            result[count].value = arr[i];
            result[count].count = 1;
            count++;
        }
    }
    
    qsort(result, count, sizeof(Frequency), compare);
    
    *freq = result;
    *freq_size = count;
}

int main(void) {
    int arr[] = {4, 2, 2, 8, 3, 3, 3, 4, 9, 4};
    int size = sizeof(arr) / sizeof(arr[0]);
    Frequency *frequencies = NULL;
    int freq_size = 0;
    
    find_frequencies(arr, size, &frequencies, &freq_size);
    
    if (frequencies != NULL) {
        printf("Element\tFrequency\n");
        for (int i = 0; i < freq_size; i++) {
            printf("%d\t%d\n", frequencies[i].value, frequencies[i].count);
        }
        free(frequencies);
    }
    
    return 0;
}