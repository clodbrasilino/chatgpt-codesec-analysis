#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int sum_alternate_series(int n, long *result)
{
    long sum = 0;
    int current = n;

    if (result == NULL) {
        return -1;
    }

    if (n <= 0) {
        *result = 0;
        return 0;
    }

    while (current > 0) {
        if (sum > LONG_MAX - current) {
            return -2;
        }
        sum += current;
        
        if (current <= 2) {
            break;
        }
        current -= 2;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    char *input_buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read_len = 0;
    char *endptr = NULL;
    long input_value = 0;
    long result = 0;
    int status = 0;
    size_t len = 0;

    printf("Enter a positive integer: ");
    
    read_len = getline(&input_buffer, &buffer_size, stdin);
    if (read_len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input_buffer);
    if (len > 0 && input_buffer[len - 1] == '\n') {
        input_buffer[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        fprintf(stderr, "Invalid input: not a valid integer\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }

    errno = 0;
    input_value = strtol(input_buffer, &endptr, 10);

    if (errno == ERANGE || endptr == input_buffer) {
        fprintf(stderr, "Invalid input: not a valid integer\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }

    while (*endptr != '\0' && isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input: not a valid integer\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }

    if (input_value > INT_MAX || input_value < 0) {
        fprintf(stderr, "Input out of valid range\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }

    status = sum_alternate_series((int)input_value, &result);

    if (status == -1) {
        fprintf(stderr, "Internal error: invalid parameter\n");
        free(input_buffer);
        return EXIT_FAILURE;
    } else if (status == -2) {
        fprintf(stderr, "Arithmetic overflow occurred\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }

    printf("Sum: %ld\n", result);

    free(input_buffer);
    return EXIT_SUCCESS;
}