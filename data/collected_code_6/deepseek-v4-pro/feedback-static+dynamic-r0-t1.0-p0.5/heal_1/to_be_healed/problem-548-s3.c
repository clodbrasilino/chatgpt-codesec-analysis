#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'seq' can be declared as pointer to const [constParameterPointer]
 */
int longest_increasing_subsequence(int *seq, int n) {
    if (seq == NULL || n <= 0) {
        return 0;
    }

    int *tails = (int *)malloc(n * sizeof(int));
    if (tails == NULL) {
        return -1;
    }

    int len = 0;
    tails[0] = seq[0];
    len = 1;

    for (int i = 1; i < n; i++) {
        if (seq[i] < tails[0]) {
            tails[0] = seq[i];
        } else if (seq[i] > tails[len - 1]) {
            tails[len++] = seq[i];
        } else {
            int left = 0;
            int right = len - 1;
            int pos = -1;

            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (tails[mid] >= seq[i]) {
                    pos = mid;
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }

            if (pos != -1) {
                tails[pos] = seq[i];
            }
        }
    }

    free(tails);
    return len;
}

int main(void) {
    int seq[] = {10, 9, 2, 5, 3, 7, 101, 18};
    int n = sizeof(seq) / sizeof(seq[0]);

    int result = longest_increasing_subsequence(seq, n);
    if (result == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Length of longest increasing subsequence: %d\n", result);
    return EXIT_SUCCESS;
}