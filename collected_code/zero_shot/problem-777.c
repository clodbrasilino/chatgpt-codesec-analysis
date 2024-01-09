#include <stdbool.h>

int sumNonRepeatedElements(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        bool repeated = false;
        for (int j = 0; j < n; j++) {
            if (i != j && arr[i] == arr[j]) {
                repeated = true;
                break;
            }
        }
        if (!repeated) {
            sum += arr[i];
        }
    }
    return sum;
}