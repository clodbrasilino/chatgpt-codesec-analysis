#if defined(__linux__) || defined(__APPLE__)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
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
    size_t out_size = 32;
    char *date_out = (char *)malloc(out_size * sizeof(char));

    if (date_out == NULL) {
        return 1;
    }

    memset(date_out, 0, out_size);

    if (convert_date(date_in, date_out, out_size) == 0) {
        printf("Converted date: %s\n", date_out);
    } else {
        printf("Error converting date.\n");
    }

    free(date_out);
    return 0;
}