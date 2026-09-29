#include <stdio.h>

// Function to count the occurrence of elements in a tuple
void countOccurrence(int list[], int listSize, int tuple[], int tupleSize) {
    int count = 0;

    // Iterate through each element of the tuple
    for (int i = 0; i < tupleSize; i++) {
        count = 0;

        // Iterate through each element of the list
        for (int j = 0; j < listSize; j++) {
            // If the current element of the list matches the current element of the tuple
            /* Possible weaknesses found:
             *  Cannot determine that 'tuple[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'list[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (list[j] == tuple[i]) {
                // Increment the occurrence count
                count++;
            }
        }

        // Print the count of the current element in the tuple
        /* Possible weaknesses found:
         *  Cannot determine that 'tuple[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        printf("Element %d occurs %d time(s)\n", tuple[i], count);
    }
}

int main() {
    int list[] = {1, 2, 3, 4, 5};  // Example list
    int tuple[] = {1, 2, 3, 2, 1};  // Example tuple

    int listSize = sizeof(list) / sizeof(list[0]);
    int tupleSize = sizeof(tuple) / sizeof(tuple[0]);

    countOccurrence(list, listSize, tuple, tupleSize);

    return 0;
}