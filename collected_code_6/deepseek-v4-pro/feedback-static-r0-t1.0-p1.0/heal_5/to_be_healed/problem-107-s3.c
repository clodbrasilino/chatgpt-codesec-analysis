#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

#define INPUT_BUFFER_SIZE 101

int is_hex_number(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    
    const char *p = str;
    
    if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
        p += 2;
        if (*p == '\0') {
            return 0;
        }
    }
    
    while (*p != '\0') {
        if (!isxdigit((unsigned char)*p)) {
            return 0;
        }
        p++;
    }
    
    return 1;
}

int count_hex_numbers_in_range(const char *start, const char *end) {
    if (start == NULL || end == NULL) {
        return 0;
    }
    
    if (!is_hex_number(start) || !is_hex_number(end)) {
        return 0;
    }
    
    char *endptr_start = NULL;
    char *endptr_end = NULL;
    
    errno = 0;
    long start_val = strtol(start, &endptr_start, 16);
    if (errno == ERANGE || endptr_start == NULL || *endptr_start != '\0') {
        return 0;
    }
    
    errno = 0;
    long end_val = strtol(end, &endptr_end, 16);
    if (errno == ERANGE || endptr_end == NULL || *endptr_end != '\0') {
        return 0;
    }
    
    if (start_val > end_val) {
        return 0;
    }
    
    unsigned long diff = (unsigned long)(end_val - start_val);
    if (diff > (unsigned long)(INT_MAX - 1)) {
        return INT_MAX;
    }
    
    return (int)diff + 1;
}

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    if (str == NULL) {
        return 0;
    }
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

void safe_copy_string(char *dest, size_t dest_size, const char *src) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return;
    }
    
    size_t i;
    for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

void remove_trailing_newline(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return;
    }
    
    size_t len = safe_strlen(str, size);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int main(int argc, const char *argv[]) {
    char *start_buf = NULL;
    char *end_buf = NULL;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char start_stack[INPUT_BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char end_stack[INPUT_BUFFER_SIZE];
    
    if (argc == 3) {
        size_t len_start = safe_strlen(argv[1], INPUT_BUFFER_SIZE);
        size_t len_end = safe_strlen(argv[2], INPUT_BUFFER_SIZE);
        
        if (len_start >= INPUT_BUFFER_SIZE || len_end >= INPUT_BUFFER_SIZE) {
            printf("Input too long\n");
            return 1;
        }
        
        safe_copy_string(start_stack, INPUT_BUFFER_SIZE, argv[1]);
        safe_copy_string(end_stack, INPUT_BUFFER_SIZE, argv[2]);
        start_buf = start_stack;
        end_buf = end_stack;
    } else {
        start_buf = start_stack;
        end_buf = end_stack;
        
        printf("Enter start hexadecimal number: ");
        if (fgets(start_buf, INPUT_BUFFER_SIZE, stdin) == NULL) {
            return 1;
        }
        remove_trailing_newline(start_buf, INPUT_BUFFER_SIZE);
        
        printf("Enter end hexadecimal number: ");
        if (fgets(end_buf, INPUT_BUFFER_SIZE, stdin) == NULL) {
            return 1;
        }
        remove_trailing_newline(end_buf, INPUT_BUFFER_SIZE);
    }
    
    int count = count_hex_numbers_in_range(start_buf, end_buf);
    
    if (count == 0 && strcmp(start_buf, end_buf) != 0) {
        printf("Invalid input or range\n");
        return 1;
    }
    
    printf("Number of hexadecimal values in range [%s, %s]: %d\n", start_buf, end_buf, count);
    
    return 0;
}