#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

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

int main(void) {
    char input_buffer[256];
    char *end_ptr;
    long start, end, count;
    int result;

    printf("Enter start of range: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    start = strtol(input_buffer, &end_ptr, 10);
    if (errno != 0 || end_ptr == input_buffer || (*end_ptr != '\n' && *end_ptr != '\0')) {
        fprintf(stderr, "Invalid input for start value\n");
        return EXIT_FAILURE;
    }

    printf("Enter end of range: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = strtol(input_buffer, &end_ptr, 10);
    if (errno != 0 || end_ptr == input_buffer || (*end_ptr != '\n' && *end_ptr != '\0')) {
        fprintf(stderr, "Invalid input for end value\n");
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