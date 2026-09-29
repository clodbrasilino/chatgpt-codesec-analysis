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
    char *strings[MAX_STRINGS];
    int count = 0;
    int read_count = 0;
    char buffer[MAX_LENGTH];
    
    for (int i = 0; i < MAX_STRINGS; i++) {
        strings[i] = NULL;
    }
    
    printf("Enter number of strings (max %d): ", MAX_STRINGS);
    if (scanf("%d", &read_count) != 1 || read_count <= 0 || read_count > MAX_STRINGS) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    count = read_count;
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c == EOF) {
            break;
        }
    }
    
    for (int i = 0; i < count; i++) {
        printf("Enter string %d: ", i + 1);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            fprintf(stderr, "Error reading input\n");
            for (int j = 0; j < i; j++) {
                free(strings[j]);
                strings[j] = NULL;
            }
            return EXIT_FAILURE;
        }
        
        size_t len = strnlen(buffer, sizeof(buffer));
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        
        if (len == 0) {
            fprintf(stderr, "Invalid string length\n");
            for (int j = 0; j < i; j++) {
                free(strings[j]);
                strings[j] = NULL;
            }
            return EXIT_FAILURE;
        }
        
        strings[i] = malloc(len + 1);
        if (strings[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (int j = 0; j < i; j++) {
                free(strings[j]);
                strings[j] = NULL;
            }
            return EXIT_FAILURE;
        }
        
        memcpy(strings[i], buffer, len + 1);
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
    
    return EXIT_SUCCESS;
}