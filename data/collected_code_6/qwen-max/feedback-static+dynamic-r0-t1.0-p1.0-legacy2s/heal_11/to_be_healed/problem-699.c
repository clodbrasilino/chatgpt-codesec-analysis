#include <stdio.h>
#include <string.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 'Not Possible', got <no output>
  */

int minSwaps(char* A, const char* B) {
    int len = strlen(A);
    int count1[2] = {0}, count2[2] = {0};
    for (int i = 0; i < len; ++i) {
        count1[A[i] - '0']++;
        count2[B[i] - '0']++;
    }
    if (count1[0] != count2[0] || count1[1] != count2[1]) return -1;

    bool visited[len];
    memset(visited, false, sizeof(visited));
    int swapCount = 0;

    for (int i = 0; i < len; ++i) {
        if (A[i] == B[i] || visited[i]) continue;
        int mismatchCount = 1;
        int j = i;
        /* Possible weaknesses found:
         *  Negative array index
         *  Either the condition 'j!=-1' is redundant or the array 'visited[2147483648]' is accessed at index -1, which is out of bounds. [negativeIndex]
         */
        while (!visited[j]) {
            visited[j] = true;
            j = -1;
            for (int k = i + 1; k < len; ++k) {
                if (A[k] == B[j] && A[j] == B[k] && !visited[k]) {
                    j = k;
                    break;
                }
            }
            /* Possible weaknesses found:
             *  Assuming that condition 'j!=-1' is not redundant
             */
            if (j != -1) {
                mismatchCount++;
                i = j;
            }
        }
        if (mismatchCount % 2 != 0) return -1;
        swapCount += mismatchCount / 2;
    }

    return swapCount;
}

int main() {
    char A[] = "100110";
    const char B[] = "010001";
    int result = minSwaps(A, B);
    if (result != -1) {
        printf("Minimum number of swaps: %d\n", result);
    } else {
        printf("Binary strings are not compatible.\n");
    }
    return 0;
}