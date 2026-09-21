#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROMAN_NUMERAL_LENGTH 15
#define ROMAN_BUFFER_SIZE (MAX_ROMAN_NUMERAL_LENGTH + 2)
#define MIN_ROMAN_VALUE 1
#define MAX_ROMAN_VALUE 3999

#define ROMAN_ENTRY(val, str) { (val), (str) }

typedef struct {
    int value;
    const char *numeral;
} roman_numeral_entry;

_Static_assert(ROMAN_BUFFER_SIZE > MAX_ROMAN_NUMERAL_LENGTH,
               "roman buffer must exceed maximum possible numeral length");

int int_to_roman(int value, char *buffer, size_t buffer_size)
{
    static const roman_numeral_entry roman_table[] = {
        ROMAN_ENTRY(1000, "M"),
        ROMAN_ENTRY(900,  "CM"),
        ROMAN_ENTRY(500,  "D"),
        ROMAN_ENTRY(400,  "CD"),
        ROMAN_ENTRY(100,  "C"),
        ROMAN_ENTRY(90,   "XC"),
        ROMAN_ENTRY(50,   "L"),
        ROMAN_ENTRY(40,   "XL"),
        ROMAN_ENTRY(10,   "X"),
        ROMAN_ENTRY(9,    "IX"),
        ROMAN_ENTRY(5,    "V"),
        ROMAN_ENTRY(4,    "IV"),
        ROMAN_ENTRY(1,    "I")
    };

    size_t position;
    size_t table_size;
    size_t i;

    if (buffer == NULL || buffer_size == 0) {
        return -1;
    }

    if (buffer_size <= (size_t)MAX_ROMAN_NUMERAL_LENGTH) {
        buffer[0] = '\0';
        return -1;
    }

    buffer[0] = '\0';

    if (value < MIN_ROMAN_VALUE || value > MAX_ROMAN_VALUE) {
        return -1;
    }

    position = 0;
    table_size = sizeof(roman_table) / sizeof(roman_table[0]);

    for (i = 0; i < table_size && value > 0; i++) {
        while (value >= roman_table[i].value) {
            size_t remaining = buffer_size - position;
            int written = snprintf(buffer + position, remaining, "%s",
                                   roman_table[i].numeral);

            if (written < 0 || (size_t)written >= remaining) {
                buffer[0] = '\0';
                return -1;
            }

            position += (size_t)written;
            value -= roman_table[i].value;
        }
    }

    if (position >= buffer_size) {
        buffer[0] = '\0';
        return -1;
    }

    buffer[position] = '\0';
    return 0;
}

int main(void)
{
    char *roman_buffer = NULL;
    int number = 0;
    int scan_result;
    int conversion_result;

    roman_buffer = calloc(ROMAN_BUFFER_SIZE, sizeof(char));
    if (roman_buffer == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter an integer (1-3999): ");
    fflush(stdout);

    scan_result = scanf("%d", &number);

    if (scan_result != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        free(roman_buffer);
        roman_buffer = NULL;
        return EXIT_FAILURE;
    }

    if (number < MIN_ROMAN_VALUE || number > MAX_ROMAN_VALUE) {
        fprintf(stderr, "Error: Number must be between 1 and 3999\n");
        free(roman_buffer);
        roman_buffer = NULL;
        return EXIT_FAILURE;
    }

    conversion_result = int_to_roman(number, roman_buffer, ROMAN_BUFFER_SIZE);

    if (conversion_result != 0) {
        fprintf(stderr, "Error: Conversion failed\n");
        free(roman_buffer);
        roman_buffer = NULL;
        return EXIT_FAILURE;
    }

    printf("Roman numeral: %s\n", roman_buffer);

    free(roman_buffer);
    roman_buffer = NULL;

    return EXIT_SUCCESS;
}