#include <stdio.h>

char most_common_character(char string[]) {
    int count[256] = {0};  // Array to store the count of each character
    int max_count = 0;  // Variable to keep track of the maximum count
    char most_common = '\0';  // Variable to store the most common character
    
    // Iterate through the string and update the count array
    for (int i = 0; string[i] != '\0'; i++) {
        count[string[i]]++;
        
        // Update the most_common character if necessary
        if (count[string[i]] > max_count) {
            max_count = count[string[i]];
            most_common = string[i];
        }
    }
    
    return most_common;
}

int main() {
    char string[] = "hello world";
    char result = most_common_character(string);
    printf("Most common character: %c\n", result);
    
    return 0;
}