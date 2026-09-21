#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROMAN_BUFFER_SIZE 32
#define MIN_ROMAN_VALUE 1
#define MAX_ROMAN_VALUE 3999

#define ROMAN_ENTRY(val, str) { (val), (str), sizeof(str) - 1 }

typedef struct {
    int value;
    const char *numeral;
    size_t numeral_length;
} roman_numeral_entry;

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
    size_t j;
    size_t numeral_length;

    if (buffer == NULL || buffer_size == 0) {
        return -1;
    }

    buffer[0] = '\0';

    if (value < MIN_ROMAN_VALUE || value > MAX_ROMAN_VALUE) {
        return -1;
    }

    position = 0;
    table_size = sizeof(roman_table) / sizeof(roman_table[0]);

    for (i = 0; i < table_size; i++) {
        numeral_length = roman_table[i].numeral_length;
        while (value >= roman_table[i].value) {
            if (buffer_size - position <= numeral_length) {
                buffer[0] = '\0';
                return -1;
            }
            for (j = 0; j < numeral_length; j++) {
                buffer[position + j] = roman_table[i].numeral[j];
            }
            position += numeral_length;
            value -= roman_table[i].value;
        }
    }

    buffer[position] = '\0';
    return 0;
}

int main(void)
{
    char roman_buffer[ROMAN_BUFFER_SIZE];
    int number;
    int scan_result;
    int conversion_result;

    printf("Enter an integer (1-3999): ");
    fflush(stdout);

    scan_result = scanf("%d", &number);

    if (scan_result != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }

    conversion_result = int_to_roman(number, roman_buffer, sizeof(roman_buffer));

    if (conversion_result != 0) {
        fprintf(stderr, "Error: Number must be between 1 and 3999\n");
        return EXIT_FAILURE;
    }

    printf("Roman numeral: %s\n", roman_buffer);

    return EXIT_SUCCESS;
}