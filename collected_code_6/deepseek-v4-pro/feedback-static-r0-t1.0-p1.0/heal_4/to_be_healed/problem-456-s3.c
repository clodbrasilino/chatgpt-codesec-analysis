#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 100
#define MAX_LENGTH 256

static void reverse_string(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return;
    }
    
    size_t len = strnlen(str, max_len);
    if (len == 0 || len >= max_len) {
        return;
    }
    
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

static void reverse_strings(char **strings, int count) {
    if (strings == NULL || count <= 0) {
        return;
    }
    
    for (int i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            reverse_string(strings[i], MAX_LENGTH);
        }
    }
}

int main(void) {
    char **strings = NULL;
    int count = 0;
    int read_count = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_LENGTH + 1];
    
    strings = calloc(MAX_STRINGS, sizeof(char *));
    if (strings == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter number of strings (max %d): ", MAX_STRINGS);
    if (scanf("%d", &read_count) != 1 || read_count <= 0 || read_count > MAX_STRINGS) {
        fprintf(stderr, "Invalid input\n");
        free(strings);
        return EXIT_FAILURE;
    }
    count = read_count;
    
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF) {
    }
    
    for (int i = 0; i < count; i++) {
        printf("Enter string %d: ", i + 1);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            fprintf(stderr, "Error reading input\n");
            for (int j = 0; j < i; j++) {
                free(strings[j]);
                strings[j] = NULL;
            }
            free(strings);
            return EXIT_FAILURE;
        }
        
        size_t len = strnlen(buffer, sizeof(buffer));
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        
        if (len == 0 || len > MAX_LENGTH) {
            fprintf(stderr, "Invalid string length\n");
            for (int j = 0; j < i; j++) {
                free(strings[j]);
                strings[j] = NULL;
            }
            free(strings);
            return EXIT_FAILURE;
        }
        
        strings[i] = malloc(len + 1);
        if (strings[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (int j = 0; j < i; j++) {
                free(strings[j]);
                strings[j] = NULL;
            }
            free(strings);
            return EXIT_FAILURE;
        }
        
        if (len + 1 <= MAX_LENGTH + 1) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(strings[i], buffer, len + 1);
        } else {
            free(strings[i]);
            strings[i] = NULL;
        }
    }
    
    reverse_strings(strings, count);
    
    printf("\nReversed strings:\n");
    for (int i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            printf("%s\n", strings[i]);
        }
    }
    
    for (int i = 0; i < count; i++) {
        free(strings[i]);
        strings[i] = NULL;
    }
    free(strings);
    
    return EXIT_SUCCESS;
}