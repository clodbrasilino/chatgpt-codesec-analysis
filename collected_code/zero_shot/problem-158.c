int findOperations(int arr[], int n, int k) {
    int max_val = arr[0];
    int min_val = arr[0];
    for (int i = 1; i < n; i++) {
        max_val = max(max_val, arr[i]);
        min_val = min(min_val, arr[i]);
    }
    int operations = 0;
    while (max_val - min_val > 0) {
        max_val -= k;
        min_val += k;
        operations++;
    }
    return operations;
}