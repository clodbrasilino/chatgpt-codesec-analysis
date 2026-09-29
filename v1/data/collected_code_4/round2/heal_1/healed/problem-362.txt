#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 1000

struct item {
    int value;
    int count;
};

int find_max_occurrences(int* array, int length) {
    struct item counts[MAX_ELEMENTS] = { 0 };
    
    for(int i = 0; i < length; ++i) {
        counts[array[i]].value = array[i];
        counts[array[i]].count++;
    }

    int max_count = 0;
    int max_value = 0;
    
    for(int i = 0; i < MAX_ELEMENTS; ++i) {
        if(counts[i].count > max_count) {
            max_count = counts[i].count;
            max_value = counts[i].value;
        }
    }

    return max_value;
}

int main() {
    int array[] = {1, 2, 2, 3, 3, 3, 4};
    int length = sizeof(array) / sizeof(array[0]);

    int result = find_max_occurrences(array, length);

    printf("Element with maximum occurrences is: %d\n", result);

    return 0;
}