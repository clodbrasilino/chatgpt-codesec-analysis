#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_NUM_LEN 32
#define MAX_NUMBERS 128
#define BUFFER_SIZE 1024

int move_numbers_to_string(const char *input, char *output, size_t output_size)
{
    char numbers[MAX_NUMBERS][MAX_NUM_LEN];
    char remaining[BUFFER_SIZE];
    size_t num_count = 0;
    size_t rem_len = 0;
    size_t i = 0;
    size_t input_len;
    size_t out_pos = 0;
    size_t j;

    if (input == NULL || output == NULL || output_size == 0)
        return -1;

    input_len = strlen(input);

    if (input_len >= BUFFER_SIZE)
        return -1;

    remaining[0] = '\0';
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
                return -1;

            if (input[i] == '-' || input[i] == '+')
            {
                numbers[num_count][num_len++] = input[i];
                i++;
            }

            while (i < input_len && (isdigit((unsigned char)input[i]) || input[i] == '.'))
            {
                if (num_len >= MAX_NUM_LEN - 1)
                    return -1;
                numbers[num_count][num_len++] = input[i];
                i++;
            }

            numbers[num_count][num_len] = '\0';
            num_count++;
        }
        else
        {
            if (rem_len >= BUFFER_SIZE - 1)
                return -1;
            remaining[rem_len++] = input[i];
            i++;
        }
    }

    remaining[rem_len] = '\0';

    for (j = 0; j < num_count; j++)
    {
        size_t nlen = strlen(numbers[j]);
        if (out_pos + nlen + 2 >= output_size)
            return -1;
        memcpy(output + out_pos, numbers[j], nlen);
        out_pos += nlen;
        output[out_pos++] = ' ';
    }

    if (out_pos + rem_len + 1 >= output_size)
        return -1;

    memcpy(output + out_pos, remaining, rem_len);
    out_pos += rem_len;
    output[out_pos] = '\0';

    return 0;
}

int main(void)
{
    char input[BUFFER_SIZE];
    char output[BUFFER_SIZE];

    printf("Enter a string: ");

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    if (move_numbers_to_string(input, output, sizeof(output)) != 0)
    {
        fprintf(stderr, "Error: failed to process the string.\n");
        return EXIT_FAILURE;
    }

    printf("Result: %s\n", output);

    return EXIT_SUCCESS;
}