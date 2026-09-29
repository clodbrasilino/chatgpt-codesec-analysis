#include <stdio.h>
#include <string.h>

int count_substrings_same_start_end(const char *str) {
    int count = 0;
    int freq[256] = {0};
    size_t len = strlen(str);
    
    for (size_t i = 0; i < len; i++) {
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
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input) == 0) {
        printf("Total substrings: 0\n");
        return 0;
    }
    
    int result = count_substrings_same_start_end(input);
    printf("Total substrings: %d\n", result);
    
    return 0;
}