#include <stdio.h>

// Structure for a tuple
struct Tuple {
    int x;
    int y;
};

// Function to extract the nth element from a list of tuples
int extractNthElement(struct Tuple *list, int size, int n) {
    // Return -1 if the index is out of bounds
    if (n < 0 || n >= size) {
        return -1;
    }
    // Return nth element
    return list[n].x;
}

int main() {
    // Example usage
    struct Tuple list[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    int size = sizeof(list) / sizeof(struct Tuple);
    int n = 2;
    int result = extractNthElement(list, size, n);
    printf("nth element: %d\n", result);
    return 0;
}