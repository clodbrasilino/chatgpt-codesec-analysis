#include <stdio.h>

int countInversions(int ar[], int n) {
    int inv_count = 0;
    int i, j;

    for (i = 0; i < n - 1; i++)
        for (j = i+1; j < n; j++)
            if (ar[i] > ar[j])
                inv_count++;

    return inv_count;
}

int findInversionsInTuple(int tupleList[][5], int rows) {
    int totalInversions = 0;
    for(int i = 0; i < rows; i++) {
        totalInversions += countInversions(tupleList[i], 5);
    }
    return totalInversions;
}

int main() {
    int tupleList[3][5] = {
        {1, 20, 6, 4, 5},
        {2, 4, 1, 3, 5},
        {7, 6, 5, 4, 2}
    };

    printf("Number of inversions are %d \n", findInversionsInTuple(tupleList, 3));

    return 0;
}