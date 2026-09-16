#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int longestConsecutiveSubsequence(int arr[], int n) {
    bool visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    int max_length = 1;
    for (int i = 0; i < n; i++) {
        if (visited[i] == false) {
            visited[i] = true;
            int current_length = 1;

            int j = i + 1;
            while (j < n && arr[j] == arr[i] + 1) {
                visited[j] = true;
                current_length++;
                j++;
            }

            j = i - 1;
            while (j >= 0 && arr[j] == arr[i] - 1) {
                visited[j] = true;
                current_length++;
                j--;
            }

            if (current_length > max_length) {
                max_length = current_length;
            }
        }
    }

    return max_length;
}

int main() {
    int arr[] = {1, 9, 3, 10, 4, 20, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = longestConsecutiveSubsequence(arr, n);
    printf("Length of the longest consecutive subsequence is %d\n", result);
    return 0;
}