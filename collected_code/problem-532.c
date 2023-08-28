#include <stdio.h>
#include <string.h>

// Function to check if the two given strings are permutations of each other
int arePermutations(char* str1, char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    
    // If the lengths are not equal, they cannot be permutations
    if (len1 != len2) {
        return 0;
    }
    
    // Create a character count array to store the count of each character
    int count[256] = {0};
    
    // Increment the count array for characters in str1
    for (int i = 0; i < len1; i++) {
        count[str1[i]]++;
    }
    
    // Decrement the count array for characters in str2
    for (int i = 0; i < len2; i++) {
        count[str2[i]]--;
    }
    
    // If any count value in the array is non-zero, they are not permutations
    for (int i = 0; i < 256; i++) {
        if (count[i] != 0) {
            return 0;
        }
    }
    
    // If all count values are zero, they are permutations
    return 1;
}

int main() {
    char str1[] = "abcd";
    char str2[] = "dcba";
    
    if (arePermutations(str1, str2)) {
        printf("The strings are permutations of each other.\n");
    } else {
        printf("The strings are not permutations of each other.\n");
    }
    
    return 0;
}