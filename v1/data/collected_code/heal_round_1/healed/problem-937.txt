#include <stdio.h>

char most_common_character(const char string[]) {
    int count[256] = {0};
    int max_count = 0;
    char most_common = '\0';
    
    for (int i = 0; string[i] != '\0'; i++) {
        count[(unsigned char)string[i]]++;
        if (count[(unsigned char)string[i]] > max_count) {
            max_count = count[(unsigned char)string[i]];
            most_common = string[i];
        }
    }
    return most_common;
}

int main() {
    const char string[] = "hello world";
    char result = most_common_character(string);
    printf("Most common character: %c\n", result);
    
    return 0;
}