#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define BUFFER_SIZE 256

void remove_char(char *str, char ch) {
    if (str == NULL) {
        return;
    }
    
    char *read_ptr = str;
    char *write_ptr = str;
    
    while (*read_ptr != '\0') {
        if (*read_ptr != ch) {
            *write_ptr = *read_ptr;
            write_ptr++;
        }
        read_ptr++;
    }
    *write_ptr = '\0';
}

int main(void) {
    char buffer[BUFFER_SIZE];
    char ch;
    int c;
    size_t len;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    len = strcspn(buffer, "\n");
    buffer[len] = '\0';
    
    if (scanf(" %c", &ch) != 1) {
        return EXIT_FAILURE;
    }
    
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c == EOF) {
            break;
        }
    }
    
    if (c == EOF && ferror(stdin)) {
        return EXIT_FAILURE;
    }
    
    remove_char(buffer, ch);
    
    printf("%s\n", buffer);
    
    return EXIT_SUCCESS;
}