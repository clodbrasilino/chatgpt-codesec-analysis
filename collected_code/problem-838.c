#include <stdio.h>

// Function to find minimum number of swaps
// to make two binary strings equal
int minSwaps(char* s1, char* s2) {
    int n = 0; // number of swaps

    for (int i = 0; s1[i]; i++) {
        if (s1[i] != s2[i]) {
            n++;
            i++; // Skip checking the next index as it will also be different
        }
    }

    return n;
}

// Driver code
int main() {
    char s1[] = "1001";
    char s2[] = "0110";

    int swaps = minSwaps(s1, s2);
    printf("Minimum number of swaps required: %d\n", swaps);

    return 0;
}