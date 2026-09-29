#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_substrings(const char *str) {
    int count = 0;
    int freq[256] = {0};
    
    if (str == NULL) {
        return 0;
    }
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        freq[(unsigned char)str[i]]++;
    }
    
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            count += freq[i] * (freq[i] + 1) / 2;
        }
    }
    
    return count;
}

int main(void) {
    char input[1000];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    size_t newline_pos = strcspn(input, "\n");
    if (newline_pos < sizeof(input)) {
        input[newline_pos] = '\0';
    } else {
        input[sizeof(input) - 1] = '\0';
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    int result = count_substrings(input);
    printf("Number of substrings: %d\n", result);
    
    return 0;
}