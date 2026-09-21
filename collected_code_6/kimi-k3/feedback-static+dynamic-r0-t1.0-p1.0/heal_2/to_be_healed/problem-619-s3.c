#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_NUM_LEN 32
#define MAX_NUMBERS 128
#define BUFFER_SIZE 1024

int move_numbers_to_string(const char *input, char *output, size_t output_size)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char numbers[MAX_NUMBERS][MAX_NUM_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char remaining[BUFFER_SIZE];
    size_t num_count = 0;
    size_t rem_len = 0;
    size_t i = 0;
    size_t input_len = 0;
    size_t out_pos = 0;
    size_t j;

    if (input == NULL || output == NULL || output_size == 0)
        return -1;

    while (input_len < BUFFER_SIZE && input[input_len] != '\0')
        input_len++;

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
                if (num_len >= MAX_NUM_LEN - 1)
                    return -1;
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

            if (num_len >= MAX_NUM_LEN)
                return -1;
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

    if (rem_len >= BUFFER_SIZE)
        return -1;
    remaining[rem_len] = '\0';

    for (j = 0; j < num_count; j++)
    {
        size_t nlen = 0;
        while (nlen < MAX_NUM_LEN && numbers[j][nlen] != '\0')
            nlen++;

        if (nlen >= MAX_NUM_LEN)
            return -1;

        /* Possible weaknesses found:
         *  Assuming that condition 'out_pos+nlen+2>=output_size' is not redundant
         */
        if (out_pos + nlen + 2 >= output_size)
            return -1;

        /* Possible weaknesses found:
         *  Condition 'out_pos+nlen>output_size' is always false
         *  Condition 'out_pos+nlen>output_size' is always false [knownConditionTrueFalse]
         */
        if (out_pos + nlen > output_size)
            return -1;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(output + out_pos, numbers[j], nlen);
        out_pos += nlen;

        if (out_pos >= output_size - 1)
            return -1;
        output[out_pos++] = ' ';
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'out_pos+rem_len+1>=output_size' is not redundant
     */
    if (out_pos + rem_len + 1 >= output_size)
        return -1;

    /* Possible weaknesses found:
     *  Condition 'out_pos+rem_len>output_size' is always false [knownConditionTrueFalse]
     *  Condition 'out_pos+rem_len>output_size' is always false
     */
    if (out_pos + rem_len > output_size)
        return -1;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output + out_pos, remaining, rem_len);
    out_pos += rem_len;

    if (out_pos >= output_size)
        return -1;
    output[out_pos] = '\0';

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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