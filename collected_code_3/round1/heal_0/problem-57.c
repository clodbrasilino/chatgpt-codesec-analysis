#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return *(char*)b - *(char*)a;
}

void findLargestNum(char* arr, int n) {
    qsort(arr, n, sizeof(arr[0]), compare);
}

int main() {
    char arr[] = {'5', '3', '1', '9', '8', '6', '7', '2', '0'};
    int n = sizeof(arr)/sizeof(arr[0]);

    findLargestNum(arr, n);

    printf("Largest Number is ");
    for(int i = 0; i < n; i++)
        printf("%c", arr[i]);

    return 0;
}