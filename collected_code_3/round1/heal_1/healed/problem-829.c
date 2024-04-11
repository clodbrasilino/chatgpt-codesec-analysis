#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100
#define MAX_STR_COUNT 1000

struct StringCount {
    char str[MAX_STR_LEN];
    int count;
};

int findIndex(struct StringCount arr[], int n, char* str) {
    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(arr[i].str, str) == 0) {
            return i;
        }
    }
    return -1;
}

void secondMostRepeated(char* sequence[], int n, char* secondFrequent) {
    struct StringCount arr[MAX_STR_COUNT];
    int index, arrSize = 0, i;

    for (i = 0; i < n; i++) {
        index = findIndex(arr, arrSize, sequence[i]);
        if (index != -1) {
            arr[index].count++;
        } else {
            strcpy(arr[arrSize].str, sequence[i]);
            arr[arrSize].count = 1;
            arrSize++;
        }
    }

    int firstMax = 0, secondMax = 0;

    for (i = 0; i < arrSize; i++) {
        if (arr[i].count > arr[firstMax].count) {
            secondMax = firstMax;
            firstMax = i;
        } else if (arr[i].count > arr[secondMax].count && arr[i].count < arr[firstMax].count) {
            secondMax = i;
        }
    }
    strcpy(secondFrequent, arr[secondMax].str);
}

int main() {
    char* sequence[] = {"abc", "def", "abc", "def", "abc", "ghi", "ghi", "ghi"};
    int n = sizeof(sequence) / sizeof(sequence[0]);
    char secondFrequent[MAX_STR_LEN];

    secondMostRepeated(sequence, n, secondFrequent);

    printf("%s\n", secondFrequent);

    return 0;
}