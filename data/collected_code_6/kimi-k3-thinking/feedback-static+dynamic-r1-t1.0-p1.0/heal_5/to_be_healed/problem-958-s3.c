#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define ROMAN_BUFFER_SIZE 32
#define INPUT_BUFFER_SIZE 64
#define MIN_ROMAN_VALUE 1
#define MAX_ROMAN_VALUE 3999
#define MAX_ROMAN_LENGTH 15

typedef struct {
    int value;
    const char *symbol;
    size_t symbol_len;
} RomanEntry;

_Static_assert(ROMAN_BUFFER_SIZE > MAX_ROMAN_LENGTH,
               "ROMAN_BUFFER_SIZE must exceed the maximum Roman numeral length");
_Static_assert(INPUT_BUFFER_SIZE >= 32,
               "INPUT_BUFFER_SIZE must hold the longest valid input line");

static int int_to_roman(int number, char *buffer, size_t buffer_size)
{
    static const RomanEntry table[] = {
        {1000, "M",  1U},
        { 900, "CM", 2U},
        { 500, "D",  1U},
        { 400, "CD", 2U},
        { 100, "C",  1U},
        {  90, "XC", 2U},
        {  50, "L",  1U},
        {  40, "XL", 2U},
        {  10, "X",  1U},
        {   9, "IX", 2U},
        {   5, "V",  1U},
        {   4, "IV", 2U},
        {   1, "I",  1U}
    };
    const size_t entry_count = sizeof(table) / sizeof(table[0]);
    size_t used = 0U;
    size_t i;
    int remaining;

    if (buffer == NULL || buffer_size == 0U)
    {
        return -1;
    }

    buffer[0] = '\0';

    if (number < MIN_ROMAN_VALUE || number > MAX_ROMAN_VALUE)
    {
        return -1;
    }

    if (buffer_size < (size_t)MAX_ROMAN_LENGTH + 1U)
    {
        return -1;
    }

    remaining = number;

    for (i = 0U; i < entry_count; i++)
    {
        while (remaining >= table[i].value)
        {
            if (table[i].symbol_len >= buffer_size - used)
            {
                buffer[0] = '\0';
                return -1;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buffer + used, table[i].symbol, table[i].symbol_len);
            used += table[i].symbol_len;
            buffer[used] = '\0';
            remaining -= table[i].value;
        }
    }

    buffer[used] = '\0';
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[ROMAN_BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE];
    size_t input_len;
    char *end;
    long number;

    if (printf("Enter an integer (1-3999): ") < 0 || fflush(stdout) != 0)
    {
        fprintf(stderr, "Error: failed to write prompt\n");
        return 1;
    }

    if (fgets(input, (int)sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);
    if (input_len == 0U)
    {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }

    if (input[input_len - 1U] == '\n')
    {
        input[input_len - 1U] = '\0';
    }
    else if (!feof(stdin))
    {
        fprintf(stderr, "Error: input too long\n");
        return 1;
    }

    errno = 0;
    number = strtol(input, &end, 10);
    if (end == input || errno == ERANGE || number > INT_MAX || number < INT_MIN)
    {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r')
    {
        end++;
    }

    if (*end != '\0')
    {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }

    if (int_to_roman((int)number, buffer, sizeof(buffer)) != 0)
    {
        fprintf(stderr, "Error: value must be between 1 and 3999\n");
        return 1;
    }

    if (printf("%ld -> %s\n", number, buffer) < 0)
    {
        fprintf(stderr, "Error: failed to write output\n");
        return 1;
    }

    return 0;
}