#if defined(__linux__) || defined(__APPLE__)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <string.h>

int convert_date(const char *input_date, char *output_date, size_t output_size) {
    if (input_date == NULL || output_date == NULL || output_size < 11) {
        return -1;
    }

    if (strnlen(input_date, 11) != 10) {
        return -1;
    }

    if (input_date[4] != '-' || input_date[7] != '-') {
        return -1;
    }

    output_date[0] = input_date[8];
    output_date[1] = input_date[9];
    output_date[2] = '-';
    output_date[3] = input_date[5];
    output_date[4] = input_date[6];
    output_date[5] = '-';
    output_date[6] = input_date[0];
    output_date[7] = input_date[1];
    output_date[8] = input_date[2];
    output_date[9] = input_date[3];
    output_date[10] = '\0';

    return 0;
}

int main(void) {
    const char *date_in = "2023-10-25";
    char date_out[32];

    memset(date_out, 0, sizeof(date_out));

    if (convert_date(date_in, date_out, sizeof(date_out)) == 0) {
        printf("Converted date: %s\n", date_out);
    } else {
        printf("Error converting date.\n");
    }

    return 0;
}