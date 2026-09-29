#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

#define INPUT_BUFFER_SIZE 256

int count_hexadecimal_numbers(long start, long end, long *count) {
    long i;
    long hex_count = 0;

    if (count == NULL) {
        return -1;
    }

    if (start > end) {
        return -1;
    }

    for (i = start; i <= end; i++) {
        if (i >= 0) {
            hex_count++;
        }
    }

    *count = hex_count;
    return 0;
}

static int read_long_input(const char *prompt, long *value) {
    char input_buffer[INPUT_BUFFER_SIZE];
    char *end_ptr;
    size_t len;
    long temp;

    if (value == NULL) {
        return -1;
    }

    printf("%s", prompt);
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return -1;
    }

    len = strlen(input_buffer);
    if (len > 0 && input_buffer[len - 1] == '\n') {
        input_buffer[len - 1] = '\0';
        len--;
    } else if (len == sizeof(input_buffer) - 1) {
        fprintf(stderr, "Input too long\n");
        return -1;
    }

    if (len == 0) {
        fprintf(stderr, "Empty input\n");
        return -1;
    }

    errno = 0;
    temp = strtol(input_buffer, &end_ptr, 10);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Value out of range\n");
        return -1;
    }
    
    if (end_ptr == input_buffer) {
        fprintf(stderr, "Invalid numeric input\n");
        return -1;
    }
    
    while (*end_ptr != '\0') {
        if (!isspace((unsigned char)*end_ptr)) {
            fprintf(stderr, "Invalid characters in input\n");
            return -1;
        }
        end_ptr++;
    }

    *value = temp;
    return 0;
}

int main(void) {
    long start, end, count;
    int result;

    if (read_long_input("Enter start of range: ", &start) != 0) {
        return EXIT_FAILURE;
    }

    if (read_long_input("Enter end of range: ", &end) != 0) {
        return EXIT_FAILURE;
    }

    result = count_hexadecimal_numbers(start, end, &count);
    if (result != 0) {
        fprintf(stderr, "Error: Invalid range or parameters\n");
        return EXIT_FAILURE;
    }

    printf("Count of hexadecimal numbers in range [%ld, %ld]: %ld\n", start, end, count);

    return EXIT_SUCCESS;
}