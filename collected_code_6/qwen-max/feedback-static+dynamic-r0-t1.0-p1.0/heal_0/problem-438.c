#include <stdio.h>
#include <stdlib.h>

int count_bidirectional_pairs(int *array, int length) {
    int count = 0;
    for(int i = 0; i < length; ++i) {
        for(int j = i + 1; j < length; ++j) {
            if(array[i] == array[j] || (array[i] - array[j]) == -(array[j] - array[i])) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int data[] = {1, 5, 3, 4, 2, 5, 3, 1};
    int len = sizeof(data) / sizeof(data[0]);
    printf("Number of bidirectional tuple pairs: %d\n", count_bidirectional_pairs(data, len));
    return 0;
}