#include <stdio.h>

// Function to check if the given string is a binary string or not
int isBinaryString(const char *str) {
    // Iterate through each character of the string
    while (*str) {
        // If the character is not '0' or '1', return 0 (false)
        if (*str != '0' && *str != '1') {
            return 0;
        }
        // Move to the next character
        str++;
    }
    // If all characters are '0' or '1', return 1 (true)
    return 1;
}

int main() {
    // Example usage
    const char *binaryString = "101001";
    if (isBinaryString(binaryString)) {
        printf("The given string is a binary string.\n");
    } else {
        printf("The given string is not a binary string.\n");
    }

    return 0;
}