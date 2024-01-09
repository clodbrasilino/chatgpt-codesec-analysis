#include <stdio.h>

// Function to remove duplicates from tuple
void removeDuplicates(int tuple[], int size) {
    int i, j, k;
    
    // Iterate through each element of the tuple
    for (i = 0; i < size; i++) {
        // Check if the element has already been visited
        for (j = i + 1; j < size; j++) {
            // If duplicate found, shift elements to left
            if (tuple[i] == tuple[j]) {
                for (k = j; k < size - 1; k++) {
                    tuple[k] = tuple[k+1];
                }
                size--;
                j--;
            }
        }
    }
}

int main() {
    int tuple[] = {1, 2, 3, 2, 4, 3, 5, 6, 1};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    
    // Call removeDuplicates function
    removeDuplicates(tuple, size);
    
    // Print the tuple after removing duplicates
    for (int i = 0; i < size; i++) {
        printf("%d ", tuple[i]);
    }
    
    return 0;
}