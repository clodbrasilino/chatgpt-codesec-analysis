#include <stdbool.h>

int calculateProduct(int arr[], int n) {
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