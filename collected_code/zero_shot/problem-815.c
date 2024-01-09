void sortArray(int arr[], int n) {
    int count[3] = {0}; // array to store count of 0s, 1s and 2s

    // Count number of 0s, 1s and 2s
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    int index = 0; // index for updating the original array

    // Update the original array with sorted elements
    for (int i = 0; i < 3; i++) {
        while (count[i] > 0) {
            arr[index] = i; 
            index++;
            count[i]--;
        }
    }
}

int main() {
    int arr[] = {0, 1, 2, 0, 1, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    sortArray(arr, n);

    // Print the sorted array
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}