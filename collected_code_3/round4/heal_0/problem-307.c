#include <stdio.h>

// Define a tuple-like structure
struct Tuple {
    int a;
    int b;
};

// Function to get a colon of a tuple
struct Tuple getColon(int a, int b) {
    struct Tuple t;
    t.a = a;
    t.b = b;
    return t;
}

int main() {
    // Create a tuple
    struct Tuple t = getColon(5, 10);

    // Print the elements of the tuple
    printf("Tuple: (%d, %d)\n", t.a, t.b);

    return 0;
}