#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

char *tuple_to_string(const char *format, ...) {
    va_list args;
    va_list args_copy;
    va_start(args, format);
    va_copy(args_copy, args);
    
    /* Possible weaknesses found:
     * Flawfinder vsnprintf: If format strings can be influenced by an attacker, they can be exploited, and note that sprintf variations do not always \0-terminate (CWE-134). Use a constant for the format specification. (risk 4, format)
     */
    int needed = vsnprintf(NULL, 0, format, args);
    va_end(args);
    
    if (needed < 0) {
        va_end(args_copy);
        return NULL;
    }
    
    size_t size = (size_t)needed + 1;
    char *buffer = malloc(size);
    if (!buffer) {
        va_end(args_copy);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder vsnprintf: If format strings can be influenced by an attacker, they can be exploited, and note that sprintf variations do not always \0-terminate (CWE-134). Use a constant for the format specification. (risk 4, format)
     */
    int written = vsnprintf(buffer, size, format, args_copy);
    va_end(args_copy);
    
    if (written < 0 || (size_t)written >= size) {
        free(buffer);
        return NULL;
    }
    
    return buffer;
}

int main(void) {
    char *result = tuple_to_string("%d, %s, %.2f", 42, "hello", 3.14159);
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Error: Failed to convert tuple to string\n");
        return EXIT_FAILURE;
    }
    
    result = tuple_to_string("%s-%s-%s", "apple", "banana", "cherry");
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Error: Failed to convert tuple to string\n");
        return EXIT_FAILURE;
    }
    
    result = tuple_to_string("%d|%f|%c|%s", 100, 2.71828, 'Z', "end");
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Error: Failed to convert tuple to string\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}