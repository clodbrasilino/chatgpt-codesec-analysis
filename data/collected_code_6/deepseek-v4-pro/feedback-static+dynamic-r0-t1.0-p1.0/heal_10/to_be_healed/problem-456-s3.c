#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 100
#define MAX_LENGTH 256

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

void reverse_string(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return;
    }
    
    size_t len = safe_strlen(str, max_len);
    if (len <= 1) {
        return;
    }
    
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void reverse_strings(char **strings, int count) {
    if (strings == NULL || count <= 0) {
        return;
    }
    
    for (int i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            reverse_string(strings[i], MAX_LENGTH);
        }
    }
}

static void clear_input_buffer(void) {
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int read_input_line(char *buffer, size_t size) {
    if (buffer == NULL || size == 0) {
        return 0;
    }
    
    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return 0;
    }
    
    size_t len = safe_strlen(buffer, size);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == size - 1 && buffer[len - 1] != '\n') {
        clear_input_buffer();
        buffer[0] = '\0';
        return 0;
    }
    
    return 1;
}

void cleanup_strings(char **strings, int count) {
    if (strings == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(strings[i]);
        strings[i] = NULL;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *strings[MAX_STRINGS];
    int count = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_LENGTH];
    
    for (int i = 0; i < MAX_STRINGS; i++) {
        strings[i] = NULL;
    }
    
    printf("Enter number of strings (max %d): ", MAX_STRINGS);
    if (scanf("%2d", &count) != 1 || count <= 0 || count > MAX_STRINGS) {
        fprintf(stderr, "Invalid input\n");
        clear_input_buffer();
        return EXIT_FAILURE;
    }
    
    clear_input_buffer();
    
    for (int i = 0; i < count; i++) {
        printf("Enter string %d: ", i + 1);
        
        if (!read_input_line(buffer, sizeof(buffer))) {
            fprintf(stderr, "Error reading input or string too long\n");
            cleanup_strings(strings, i);
            return EXIT_FAILURE;
        }
        
        size_t len = safe_strlen(buffer, sizeof(buffer));
        if (len >= MAX_LENGTH) {
            fprintf(stderr, "String too long\n");
            cleanup_strings(strings, i);
            return EXIT_FAILURE;
        }
        
        strings[i] = malloc(len + 1);
        if (strings[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            cleanup_strings(strings, i);
            return EXIT_FAILURE;
        }
        
        size_t copy_len = len;
        if (copy_len >= MAX_LENGTH) {
            copy_len = MAX_LENGTH - 1;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(strings[i], buffer, copy_len);
        strings[i][copy_len] = '\0';
    }
    
    reverse_strings(strings, count);
    
    printf("\nReversed strings:\n");
    for (int i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            printf("%s\n", strings[i]);
        }
    }
    
    cleanup_strings(strings, count);
    
    return EXIT_SUCCESS;
}