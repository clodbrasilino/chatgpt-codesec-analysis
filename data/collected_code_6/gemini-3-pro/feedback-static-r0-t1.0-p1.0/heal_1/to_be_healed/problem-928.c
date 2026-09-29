#include <stdio.h>
#include <string.h>

int convert_date(const char *input_date, char *output_date, size_t output_size) {
    if (input_date == NULL || output_date == NULL || output_size < 11) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(input_date) != 10) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char date_out[11];

    if (convert_date(date_in, date_out, sizeof(date_out)) == 0) {
        printf("Converted date: %s\n", date_out);
    } else {
        printf("Error converting date.\n");
    }

    return 0;
}