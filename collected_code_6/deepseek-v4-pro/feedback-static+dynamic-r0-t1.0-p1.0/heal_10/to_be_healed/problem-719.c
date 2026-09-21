#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool match_pattern(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    if (str[0] == '\0') {
        return false;
    }
    
    if (str[0] != 'a') {
        return false;
    }
    
    const char *ptr = str + 1;
    while (*ptr != '\0') {
        if (*ptr != 'b') {
            return false;
        }
        ptr++;
    }
    
    return true;
}

static void clear_input_buffer(void) {
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static size_t read_line(char *buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        return len;
    }
    
    if (len == size - 1 && buffer[len - 1] != '\n') {
        clear_input_buffer();
    }
    
    return len;
}

int main(void) {
    char *input = NULL;
    size_t bufsize = 0;
    ssize_t length;
    
    printf("Enter a string: ");
    length = getline(&input, &bufsize, stdin);
    
    if (length == -1) {
        free(input);
        return 1;
    }
    
    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
        length--;
    }
    
    if (length == 0) {
        free(input);
        return 1;
    }
    
    if (match_pattern(input)) {
        printf("Match\n");
    } else {
        printf("No match\n");
    }
    
    free(input);
    return 0;
}