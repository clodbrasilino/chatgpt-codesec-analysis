#include <stdio.h>
#include <stdbool.h>

// Function to check if all bits are within range
bool checkBitsInRange(unsigned int num, unsigned int l_bound, unsigned int u_bound) {
    if (l_bound > u_bound) {
        return false;
    }

    for (unsigned int bit = 0; bit <= 31; bit++) {
        if ((num & (1 << bit)) && (bit < l_bound || bit > u_bound)) {
            return false;
        }
    }

    return true;
}

int main() {
    unsigned int num = 15; // Binary: 1111
    unsigned int l_bound = 0;
    unsigned int u_bound = 3;

    if(checkBitsInRange(num, l_bound, u_bound)) {
        printf("All bits are within [%u, %u]\n", l_bound, u_bound);
    } else {
        printf("Not all bits are within [%u, %u]\n", l_bound, u_bound);
    }

    return 0;
}