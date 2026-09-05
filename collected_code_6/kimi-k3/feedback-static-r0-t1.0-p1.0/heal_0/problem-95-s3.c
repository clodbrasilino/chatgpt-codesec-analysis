#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_min_sublist_length(const int arr[], int n, int target_sum)
{
    int min_length = INT_MAX;
    int current_sum = 0;
    int left = 0;
    int right;

    if (arr == NULL || n <= 0) {
        return -1;
    }

    for (right = 0; right < n; right++) {
        current_sum += arr[right];

        while (current_sum >= target_sum) {
            int current_length = right - left + 1;
            if (current_length < min_length) {
                min_length = current_length;
            }
            current_sum -= arr[left];
            left++;
        }
    }

    if (min_length == INT_MAX) {
        return 0;
    }

    return min_length;
}

int main(void)
{
    int arr[] = {2, 3, 1, 2, 4, 3};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));
    int target_sum = 7;
    int result;

    result = find_min_sublist_length(arr, n, target_sum);

    if (result == -1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    } else if (result == 0) {
        printf("No sublist found with sum >= %d\n", target_sum);
    } else {
        printf("Minimum length of sublist with sum >= %d is: %d\n", target_sum, result);
    }

    return EXIT_SUCCESS;
}