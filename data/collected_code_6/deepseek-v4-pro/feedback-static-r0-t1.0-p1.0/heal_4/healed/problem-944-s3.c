#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>

void print_numbers_with_positions(const char *str) {
    int i = 0;
    int in_number = 0;
    int start_pos = 0;
    
    while (str[i] != '\0') {
        if (isdigit((unsigned char)str[i])) {
            if (!in_number) {
                start_pos = i;
                in_number = 1;
            }
        } else {
            if (in_number) {
                printf("Number: ");
                for (int j = start_pos; j < i; j++) {
                    putchar(str[j]);
                }
                printf(", Position: %d\n", start_pos);
                in_number = 0;
            }
        }
        i++;
    }
    
    if (in_number) {
        printf("Number: ");
        for (int j = start_pos; j < i; j++) {
            putchar(str[j]);
        }
        printf(", Position: %d\n", start_pos);
    }
}

int main(void) {
    char input[1024];
    size_t pos = 0;
    int c;
    
    printf("Enter a string: ");
    
    while (pos < sizeof(input) - 1) {
        c = getchar();
        if (c == EOF || c == '\n') {
            break;
        }
        input[pos++] = (char)c;
    }
    input[pos] = '\0';
    
    if (c != '\n' && c != EOF) {
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    if (ferror(stdin)) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    print_numbers_with_positions(input);
    
    return 0;
}