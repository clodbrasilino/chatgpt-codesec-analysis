#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a, b;
    int sumDigit;
} tuple;

int countDigits(int n){
    int count = 0;
    while(n != 0){
        n /= 10;
        ++count;
    }
    return count;
}

int compare(const void * a, const void * b){
    tuple *tupleA = (tuple *)a;
    tuple *tupleB = (tuple *)b;
    return (tupleA->sumDigit - tupleB->sumDigit);
}

void sortDigitsInTuple(tuple * arr, int n){
    for(int i=0; i<n; i++)
        {
            arr[i].sumDigit = countDigits(arr[i].a) + countDigits(arr[i].b);
        }
    qsort(arr, n, sizeof(tuple), compare);
}

int main() {
    int n = 5;
    tuple arr[] = {{123, 456, 0}, {789, 1011, 0}, {12, 345, 0}, {67, 89, 0}, {101, 211, 0}};
    sortDigitsInTuple(arr, n);

    for(int i=0; i<n; i++)
        {
            printf("(%d, %d)\n", arr[i].a, arr[i].b);
        }

    return 0;
}