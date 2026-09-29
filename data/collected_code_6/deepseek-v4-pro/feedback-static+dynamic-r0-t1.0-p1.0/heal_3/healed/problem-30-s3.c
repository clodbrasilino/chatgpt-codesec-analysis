#include <stdio.h>
#include <string.h>

int count_substrings_same_start_end(const char *str) {
    int count = 0;
    int freq[256] = {0};
    size_t len = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    while (str[len] != '\0') {
        freq[(unsigned char)str[len]]++;
        len++;
    }
    
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            count += freq[i] * (freq[i] + 1) / 2;
        }
    }
    
    return count;
}

int main(void) {
    char input[1001];
    size_t input_len;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    input_len = strlen(input);
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
    }
    
    if (input_len >= sizeof(input) - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    if (input[0] == '\0') {
        printf("Total substrings: 0\n");
        return 0;
    }
    
    int result = count_substrings_same_start_end(input);
    printf("Total substrings: %d\n", result);
    
    return 0;
}