#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Frequency;

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
void getFrequency(int arr[], int n, Frequency **result, int *resultSize) {
    /* Possible weaknesses found:
     *  Assuming that condition 'resultSize==NULL' is not redundant
     *  Assuming that condition 'result==NULL' is not redundant
     */
    if (arr == NULL || result == NULL || resultSize == NULL || n <= 0) {
        /* Possible weaknesses found:
         *  Null pointer dereference
         *  Either the condition 'result==NULL' is redundant or there is possible null pointer dereference: result. [nullPointerRedundantCheck]
         */
        *result = NULL;
        /* Possible weaknesses found:
         *  Null pointer dereference
         *  Either the condition 'resultSize==NULL' is redundant or there is possible null pointer dereference: resultSize. [nullPointerRedundantCheck]
         */
        *resultSize = 0;
        return;
    }

    Frequency *freq = malloc(n * sizeof(Frequency));
    if (freq == NULL) {
        *result = NULL;
        *resultSize = 0;
        return;
    }

    int uniqueCount = 0;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < uniqueCount; j++) {
            if (freq[j].value == arr[i]) {
                freq[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            freq[uniqueCount].value = arr[i];
            freq[uniqueCount].count = 1;
            uniqueCount++;
        }
    }

    *result = freq;
    *resultSize = uniqueCount;
}

int main(void) {
    int arr[] = {4, 2, 2, 8, 3, 3, 3, 1, 4, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    Frequency *freq = NULL;
    int freqSize = 0;

    getFrequency(arr, n, &freq, &freqSize);

    if (freq != NULL) {
        printf("Element Frequencies:\n");
        for (int i = 0; i < freqSize; i++) {
            printf("%d: %d\n", freq[i].value, freq[i].count);
        }
        free(freq);
    }

    return 0;
}