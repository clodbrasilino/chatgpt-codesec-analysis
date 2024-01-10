#include <stdbool.h>

int calculateProduct(const int arr[], int n) {
    int product = 1;
    bool visited[1000] = { false };

    for (int i = 0; i < n; i++) {
        if (!visited[arr[i]]) {
            visited[arr[i]] = true;
            product *= arr[i];
        }
    }
    return product;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int product = calculateProduct(arr, n);
    return 0;
}