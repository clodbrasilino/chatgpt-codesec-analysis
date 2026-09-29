#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

char find_max_occurrence(const char *str, size_t *max_count)
{
    size_t counts[UCHAR_MAX + 1] = {0};
    size_t i;
    unsigned char max_char = 0;
    size_t max = 0;

    if (str == NULL || *str == '\0') {
        if (max_count != NULL) {
            *max_count = 0;
        }
        return '\0';
    }

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        counts[c]++;
        if (counts[c] > max) {
            max = counts[c];
            max_char = c;
        }
    }

    if (max_count != NULL) {
        *max_count = max;
    }

    return (char)max_char;
}

int main(void)
{
    size_t buffer_size = 1024;
    char *buffer = malloc(buffer_size);
    size_t count = 0;
    char result;
    size_t len;

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter a string: ");
    
    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    while (len > 0 && buffer[len - 1] != '\n' && !feof(stdin)) {
        size_t new_size = buffer_size * 2;
        char *new_buffer = realloc(buffer, new_size);
        
        if (new_buffer == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            free(buffer);
            return 1;
        }
        
        buffer = new_buffer;
        buffer_size = new_size;
        
        if (fgets(buffer + len, (int)(buffer_size - len), stdin) == NULL) {
            break;
        }
        
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        len = strlen(buffer);
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = find_max_occurrence(buffer, &count);

    if (count > 0) {
        printf("Maximum occurring character: '%c' (appears %zu times)\n", result, count);
    } else {
        printf("String is empty\n");
    }

    free(buffer);
    return 0;
}