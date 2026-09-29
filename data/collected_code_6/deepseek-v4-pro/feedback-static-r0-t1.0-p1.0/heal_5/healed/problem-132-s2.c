#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

char *tuple_to_string(const char *format, ...) {
    va_list args;
    va_list args_copy;
    
    if (format == NULL) {
        return NULL;
    }
    
    if (strchr(format, '%') != NULL) {
        const char *p = format;
        int has_specifier = 0;
        while (*p) {
            if (*p == '%') {
                p++;
                if (*p == '%') {
                    p++;
                    continue;
                }
                if (*p == 's' || *p == 'c' || *p == 'd' || *p == 'i' || 
                    *p == 'u' || *p == 'f' || *p == 'g' || *p == 'x' || 
                    *p == 'X' || *p == 'o' || *p == 'e' || *p == 'E' || 
                    *p == 'p' || *p == 'n') {
                    has_specifier = 1;
                    break;
                }
            }
            p++;
        }
        if (!has_specifier) {
            return NULL;
        }
    } else {
        return strdup(format);
    }
    
    va_start(args, format);
    va_copy(args_copy, args);
    
    int needed = vsnprintf(NULL, 0, format, args);
    va_end(args);
    
    if (needed < 0) {
        va_end(args_copy);
        return NULL;
    }
    
    char *buffer = malloc(needed + 1);
    if (!buffer) {
        va_end(args_copy);
        return NULL;
    }
    
    int written = vsnprintf(buffer, needed + 1, format, args_copy);
    va_end(args_copy);
    
    if (written < 0 || written > needed) {
        free(buffer);
        return NULL;
    }
    
    buffer[needed] = '\0';
    
    return buffer;
}

int main(void) {
    const char *format1 = "%s, %s, %s";
    char *result = tuple_to_string(format1, "42", "hello", "3.14");
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Error: Failed to convert tuple to string\n");
        return EXIT_FAILURE;
    }
    
    const char *format2 = "%s-%s-%s";
    result = tuple_to_string(format2, "apple", "banana", "cherry");
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Error: Failed to convert tuple to string\n");
        return EXIT_FAILURE;
    }
    
    const char *format3 = "%s|%s|%c|%s";
    result = tuple_to_string(format3, "100", "2.71828", 'Z', "end");
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Error: Failed to convert tuple to string\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}