#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define INPUT_BUFFER_SIZE 256

int calculate_profit(double amount, double *result)
{
    const double threshold = 1000.0;
    const double profit_rate = 0.15;

    if (result == NULL) {
        return -1;
    }

    if (amount < 0.0) {
        return -1;
    }

    if (amount > threshold) {
        *result = amount * profit_rate;
        return 1;
    }

    return 0;
}

int main(void)
{
    char input_buffer[INPUT_BUFFER_SIZE];
    char *end_ptr = NULL;
    double input_amount = 0.0;
    double profit_result = 0.0;
    int status = 0;
    size_t len = 0;
    int c = 0;

    printf("Enter amount: ");

    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(input_buffer, sizeof(input_buffer));

    if (len == sizeof(input_buffer)) {
        fprintf(stderr, "Error: Input too long\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return EXIT_FAILURE;
    }

    if (len > 0 && input_buffer[len - 1] == '\n') {
        input_buffer[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        fprintf(stderr, "Error: Empty input\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)input_buffer[i]) && 
            input_buffer[i] != '.' && 
            input_buffer[i] != '-' && 
            input_buffer[i] != '+' && 
            !isspace((unsigned char)input_buffer[i])) {
            fprintf(stderr, "Error: Invalid characters in input\n");
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    input_amount = strtod(input_buffer, &end_ptr);

    if (errno == ERANGE) {
        fprintf(stderr, "Error: Number out of range\n");
        return EXIT_FAILURE;
    }

    if (end_ptr == input_buffer) {
        fprintf(stderr, "Error: No digits found\n");
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end_ptr)) {
        end_ptr++;
    }

    if (*end_ptr != '\0') {
        fprintf(stderr, "Error: Invalid characters in input\n");
        return EXIT_FAILURE;
    }

    if (isinf(input_amount) || isnan(input_amount)) {
        fprintf(stderr, "Error: Invalid amount provided\n");
        return EXIT_FAILURE;
    }

    status = calculate_profit(input_amount, &profit_result);

    if (status == -1) {
        fprintf(stderr, "Error: Invalid amount provided\n");
        return EXIT_FAILURE;
    }

    if (status == 1) {
        printf("Profit amount: %.2f\n", profit_result);
    } else {
        printf("No profit applicable\n");
    }

    return EXIT_SUCCESS;
}