void assignPairs(int arr[], int n) {
    for (int i = 0; i < n; i += 2) {
        arr[i + 1] = arr[i];
    }
}