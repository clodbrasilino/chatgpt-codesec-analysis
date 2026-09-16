#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *compress_char(char *input, char target) {
    if (input == NULL) return NULL;
    
    int len = strlen(input);
    char *output = (char *)malloc(len + 1);
    if (output == NULL) return NULL;
    
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (i > 0 && input[i] == target && input[i - 1] == target) {
            continue;
        }
        output[j++] = input[i];
    }
    output[j] = '\0';
    
    return output;
}

int main() {
    char input[] = "helloo woorlldd!!";
    char target = 'o';
    
    char *result = compress_char(input, target);
    if (result != NULL) {
        printf("Original: %s\n", input);
        printf("Compressed: %s\n", result);
        free(result);
    } else {
        printf("Failed to compress string.\n");
    }
    
    return 0;
}