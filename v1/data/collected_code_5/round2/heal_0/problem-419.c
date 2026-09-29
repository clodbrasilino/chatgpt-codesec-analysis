#include <stdio.h>
#include <math.h>

void processList(int* arr, int n) {
    if (!arr || n <= 0)
        return;

    int sum = 0;

    for (int i = 0; i < n; i++) {
        int roundNum = round(arr[i]);
        sum += roundNum;
    }

    sum *= n;

    printf("Total: %d\n", sum);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int len = sizeof(arr) / sizeof(arr[0]);
    processList(arr, len);

    return 0;
}