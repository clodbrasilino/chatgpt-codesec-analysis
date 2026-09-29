#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

static int is_valid_format_specifier(char c) {
    return (c == 's' || c == 'c' || c == 'd' || c == 'i' || 
            c == 'u' || c == 'f' || c == 'g' || c == 'x' || 
            c == 'X' || c == 'o' || c == 'e' || c == 'E' || 
            c == 'p' || c == 'n');
}

static int validate_format_string(const char *format) {
    const char *p = format;
    if (p == NULL) {
        return 0;
    }
    while (*p) {
        if (*p == '%') {
            p++;
            if (*p == '%') {
                p++;
                continue;
            }
            if (*p == '\0') {
                return 0;
            }
            if (is_valid_format_specifier(*p)) {
                return 1;
            }
            return 0;
        }
        p++;
    }
    return 0;
}

static int is_trusted_format(const char *format) {
    if (format == NULL) {
        return 0;
    }
    
    const char *p = format;
    while (*p) {
        if (*p == '%') {
            p++;
            if (*p == '%') {
                p++;
                continue;
            }
            if (*p == '\0') {
                return 0;
            }
            while (*p >= '0' && *p <= '9') p++;
            if (*p == '.') {
                p++;
                while (*p >= '0' && *p <= '9') p++;
            }
            if (*p == 'l' || *p == 'h') p++;
            if (*p == 'l') p++;
            if (!is_valid_format_specifier(*p)) {
                return 0;
            }
            p++;
            continue;
        }
        p++;
    }
    return 1;
}

char *tuple_to_string(const char *format, ...) {
    va_list args;
    va_list args_copy;
    
    if (format == NULL) {
        return NULL;
    }
    
    if (strchr(format, '%') == NULL) {
        return strdup(format);
    }
    
    if (!validate_format_string(format)) {
        return NULL;
    }
    
    if (!is_trusted_format(format)) {
        return NULL;
    }
    
    va_start(args, format);
    va_copy(args_copy, args);
    
    int needed = vsnprintf(NULL, 0, format, args);
    va_end(args);
    
    if (needed < 0) {
        va_end(args_copy);
        return NULL;
    }
    
    if (needed > INT_MAX - 1) {
        va_end(args_copy);
        return NULL;
    }
    
    size_t size = (size_t)needed + 1;
    
    char *buffer = malloc(size);
    if (!buffer) {
        va_end(args_copy);
        return NULL;
    }
    
    int written = vsnprintf(buffer, size, format, args_copy);
    va_end(args_copy);
    
    if (written < 0 || (size_t)written >= size) {
        free(buffer);
        return NULL;
    }
    
    buffer[size - 1] = '\0';
    
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