#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAMES 100
#define NAME_LENGTH 50
#define INPUT_BUFFER_SIZE 32

int sum_valid_name_lengths(char names[][NAME_LENGTH], int count) {
    int total = 0;
    
    for (int i = 0; i < count; i++) {
        if (names[i][0] != '\0' && !islower((unsigned char)names[i][0])) {
            size_t len = 0;
            while (len < NAME_LENGTH && names[i][len] != '\0') {
                len++;
            }
            total += (int)len;
        }
    }
    
    return total;
}

int safe_string_length(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return (int)len;
}

void clear_input_buffer(void) {
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int read_line(char *buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }
    
    int len = safe_string_length(buffer, size);
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        return 1;
    }
    
    if (len == (int)(size - 1) && buffer[len - 1] != '\0') {
        clear_input_buffer();
    }
    
    return 1;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char names[MAX_NAMES][NAME_LENGTH];
    int count = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[INPUT_BUFFER_SIZE];
    
    printf("Enter number of names: ");
    if (!read_line(input_buffer, sizeof(input_buffer))) {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (sscanf(input_buffer, "%d", &count) != 1) {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (count <= 0 || count > MAX_NAMES) {
        printf("Invalid count\n");
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < count; i++) {
        printf("Enter name %d: ", i + 1);
        if (!read_line(names[i], NAME_LENGTH)) {
            printf("Error reading input\n");
            return EXIT_FAILURE;
        }
    }
    
    int result = sum_valid_name_lengths(names, count);
    printf("Sum of lengths of valid names: %d\n", result);
    
    return EXIT_SUCCESS;
}