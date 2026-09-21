#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#define MAX_INPUT_SIZE 4096

int count_same_position(const char *str) {
    int count = 0;
    size_t i;
    
    if (str == NULL) {
        return 0;
    }
    
    for (i = 0; i < MAX_INPUT_SIZE && str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            char lower = tolower((unsigned char)str[i]);
            if ((int)(lower - 'a') == (int)i) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    char buffer[MAX_INPUT_SIZE];
    
    printf("Enter a string: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    size_t input_len = strlen(buffer);
    if (input_len > 0 && buffer[input_len - 1] == '\n') {
        buffer[input_len - 1] = '\0';
        input_len--;
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        if (ferror(stdin)) {
            clearerr(stdin);
        }
    }
    
    int result = count_same_position(buffer);
    printf("%d\n", result);
    
    return 0;
}