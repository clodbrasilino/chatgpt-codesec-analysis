#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void extract_numbers(const char *str) {
    if (str == NULL) {
        fprintf(stderr, "Error: NULL string provided\n");
        return;
    }
    
    size_t len = strlen(str);
    size_t i = 0;
    
    while (i < len) {
        if (isdigit((unsigned char)str[i])) {
            size_t start = i;
            while (i < len && isdigit((unsigned char)str[i])) {
                i++;
            }
            printf("Number: %.*s, Position: %zu\n", (int)(i - start), str + start, start);
        } else {
            i++;
        }
    }
}

int main(void) {
    char input[256];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    extract_numbers(input);
    
    return EXIT_SUCCESS;
}