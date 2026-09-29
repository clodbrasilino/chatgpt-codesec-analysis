#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int frequency;
    int count;
} FreqMap;

int check_similar_occurrences(int *tuples, int size) {
    if (tuples == NULL || size <= 0) {
        return 0;
    }

    int *counts = (int *)malloc(size * sizeof(int));
    if (counts == NULL) {
        return 0;
    }

    int *unique = (int *)malloc(size * sizeof(int));
    if (unique == NULL) {
        free(counts);
        return 0;
    }

    int unique_size = 0;

    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < unique_size; j++) {
            if (unique[j] == tuples[i]) {
                counts[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            unique[unique_size] = tuples[i];
            counts[unique_size] = 1;
            unique_size++;
        }
    }

    FreqMap *freq_map = (FreqMap *)malloc(unique_size * sizeof(FreqMap));
    if (freq_map == NULL) {
        free(counts);
        free(unique);
        return 0;
    }

    int freq_map_size = 0;

    for (int i = 0; i < unique_size; i++) {
        int found = 0;
        for (int j = 0; j < freq_map_size; j++) {
            if (freq_map[j].frequency == counts[i]) {
                freq_map[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            freq_map[freq_map_size].frequency = counts[i];
            freq_map[freq_map_size].count = 1;
            freq_map_size++;
        }
    }

    int result = 0;
    for (int i = 0; i < freq_map_size; i++) {
        if (freq_map[i].count > 1) {
            result += freq_map[i].count;
        }
    }

    free(counts);
    free(unique);
    free(freq_map);

    return result;
}

int main() {
    int data1[] = {1, 2, 2, 3, 3, 4, 4, 4, 5, 5};
    int size1 = sizeof(data1) / sizeof(data1[0]);
    int res1 = check_similar_occurrences(data1, size1);
    printf("%d\n", res1);

    int data2[] = {1, 1, 1, 2, 2, 2, 3, 3, 3};
    int size2 = sizeof(data2) / sizeof(data2[0]);
    int res2 = check_similar_occurrences(data2, size2);
    printf("%d\n", res2);

    int data3[] = {1, 2, 3, 4, 5};
    int size3 = sizeof(data3) / sizeof(data3[0]);
    int res3 = check_similar_occurrences(data3, size3);
    printf("%d\n", res3);

    int *data4 = NULL;
    int res4 = check_similar_occurrences(data4, 0);
    printf("%d\n", res4);

    return 0;
}