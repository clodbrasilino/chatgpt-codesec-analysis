#include<stdio.h>

int cumulativeSum(const int tupleList[], int size) {
    int sum = 0;
    for(int i = 0; i < size; i++) {
        sum += tupleList[i];
    }
    return sum;
}

int main() {
    int tupleList[] = {1, 2, 3, 4, 5};
    int size = sizeof(tupleList) / sizeof(tupleList[0]);
    int sum = cumulativeSum(tupleList, size);
    printf("Cumulative Sum: %d\n", sum);
    return 0;
}