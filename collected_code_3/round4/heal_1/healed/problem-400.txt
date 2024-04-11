#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    int a;
    int b;
} Tuple;

typedef struct TupleFreq {
    Tuple tuple;
    int freq;
} TupleFreq;

int findTuple(TupleFreq *arr, int n, Tuple t) {
    for (int i = 0; i < n; i++) {
        if (arr[i].tuple.a == t.a && arr[i].tuple.b == t.b) {
            return i;
        }
    }
    return -1;
}

void printTupleFreq(Tuple *arr, int n) {
    if(n <= 0) 
        return;

    TupleFreq *freqArr = (TupleFreq *)malloc(n * sizeof(TupleFreq));

    if(freqArr == NULL)
        return;
        
    int freqCount = 0;

    for (int i = 0; i < n; i++) {
        int index = findTuple(freqArr, freqCount, arr[i]);
        if (index != -1) {
            freqArr[index].freq++;
        } else {
            freqArr[freqCount].tuple = arr[i];
            freqArr[freqCount].freq = 1;
            freqCount++;
        }
    }

    for (int i = 0; i < freqCount; i++) {
        printf("(%d, %d): %d\n", freqArr[i].tuple.a, freqArr[i].tuple.b, freqArr[i].freq);
    }

    free(freqArr);
}

int main() {
    Tuple arr[] = {{1, 2}, {2, 3}, {1, 2}, {4, 5}, {2, 3}, {1, 2}};
    int n = sizeof(arr) / sizeof(arr[0]);

    printTupleFreq(arr, n);

    return 0;
}