#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NUM_LEN 32
#define MAX_NUMBERS 128
#define BUFFER_SIZE 1024

int move_numbers_to_string(const char *input, char *output, size_t output_size)
{
    char *numbers = NULL;
    char *remaining = NULL;
    size_t num_count = 0;
    size_t rem_len = 0;
    size_t i = 0;
    size_t input_len;
    size_t out_pos = 0;
    size_t j;
    int result = -1;

    if (input == NULL || output == NULL || output_size == 0)
        return -1;

    input_len = strnlen(input, BUFFER_SIZE);

    if (input_len >= BUFFER_SIZE)
        return -1;

    numbers = calloc(MAX_NUMBERS, MAX_NUM_LEN);
    if (numbers == NULL)
        return -1;

    remaining = calloc(BUFFER_SIZE, sizeof(char));
    if (remaining == NULL)
    {
        free(numbers);
        return -1;
    }

    output[0] = '\0';

    while (i < input_len)
    {
        if (isdigit((unsigned char)input[i]) ||
            ((input[i] == '-' || input[i] == '+') &&
             (i + 1 < input_len) && isdigit((unsigned char)input[i + 1]) &&
             (i == 0 || !isdigit((unsigned char)input[i - 1]))))
        {
            size_t num_len = 0;

            if (num_count >= MAX_NUMBERS)
                goto cleanup;

            if (input[i] == '-' || input[i] == '+')
            {
                if (num_len >= MAX_NUM_LEN - 1)
                    goto cleanup;
                numbers[num_count * MAX_NUM_LEN + num_len] = input[i];
                num_len++;
                i++;
            }

            while (i < input_len && (isdigit((unsigned char)input[i]) || input[i] == '.'))
            {
                if (num_len >= MAX_NUM_LEN - 1)
                    goto cleanup;
                numbers[num_count * MAX_NUM_LEN + num_len] = input[i];
                num_len++;
                i++;
            }

            numbers[num_count * MAX_NUM_LEN + num_len] = '\0';
            num_count++;
        }
        else
        {
            if (rem_len >= BUFFER_SIZE - 1)
                goto cleanup;
            remaining[rem_len] = input[i];
            rem_len++;
            i++;
        }
    }

    remaining[rem_len] = '\0';

    for (j = 0; j < num_count; j++)
    {
        size_t nlen = strnlen(numbers + j * MAX_NUM_LEN, MAX_NUM_LEN);
        if (nlen >= MAX_NUM_LEN)
            goto cleanup;
        if (nlen > output_size - out_pos - 1)
            goto cleanup;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(output + out_pos, numbers + j * MAX_NUM_LEN, nlen);
        out_pos += nlen;
        if (out_pos >= output_size - 1)
            goto cleanup;
        output[out_pos] = ' ';
        out_pos++;
    }

    if (rem_len > output_size - out_pos - 1)
        goto cleanup;

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output + out_pos, remaining, rem_len);
    out_pos += rem_len;
    if (out_pos >= output_size)
        goto cleanup;
    output[out_pos] = '\0';

    result = 0;

cleanup:
    free(numbers);
    free(remaining);
    return result;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    int result = EXIT_FAILURE;

    input = calloc(BUFFER_SIZE, sizeof(char));
    if (input == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    output = calloc(BUFFER_SIZE, sizeof(char));
    if (output == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");

    if (fgets(input, BUFFER_SIZE, stdin) == NULL)
    {
        fprintf(stderr, "Error reading input.\n");
        goto cleanup;
    }

    input[strcspn(input, "\n")] = '\0';

    if (move_numbers_to_string(input, output, BUFFER_SIZE) != 0)
    {
        fprintf(stderr, "Error: failed to process the string.\n");
        goto cleanup;
    }

    printf("Result: %s\n", output);
    result = EXIT_SUCCESS;

cleanup:
    free(input);
    free(output);
    return result;
}