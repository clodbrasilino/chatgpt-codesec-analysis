#include <stdio.h>
#include <stdlib.h>

// Function to find total digits in a tuple
int findDigits(int num) {
    int count = 0;
    while (num != 0) {
        num /= 10;
        count++;
    }
    return count;
}

// Function to swap two tuples
void swap(int* a, int* b) {
    /* Possible weaknesses found:
     *  Cannot determine that '*a' is initialized [premium-bughuntingUninit]
     */
    int temp = *a;
    /* Possible weaknesses found:
     *  Cannot determine that '*b' is initialized [premium-bughuntingUninit]
     */
    *a = *b;
    *b = temp;
}

// Function to perform bubble sort on the tuple list based on total digits
void sortTupleList(int tuples[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'tuples[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            int digits1 = findDigits(tuples[j]);
            /* Possible weaknesses found:
             *  Cannot determine that 'tuples[j+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            int digits2 = findDigits(tuples[j + 1]);
            if (digits1 > digits2) {
                swap(&tuples[j], &tuples[j + 1]);
            }
        }
    }
}

int main() {
    // Example usage
    int tuples[] = { 123, 9, 95, 876, 45678 };
    int size = sizeof(tuples) / sizeof(tuples[0]);

    sortTupleList(tuples, size);

    printf("Sorted Tuple List: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", tuples[i]);
    }

    return 0;
}