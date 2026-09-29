#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_LENGTH 11

int convert_date_format(const char *input, char *output, size_t output_size) {
    if (input == NULL || output == NULL) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(input) != 10) {
        return -1;
    }
    
    if (input[4] != '-' || input[7] != '-') {
        return -1;
    }
    
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            continue;
        }
        if (input[i] < '0' || input[i] > '9') {
            return -1;
        }
    }
    
    if (output_size < DATE_LENGTH) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int year = atoi(input);
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int month = atoi(input + 5);
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int day = atoi(input + 8);
    
    if (month < 1 || month > 12) {
        return -1;
    }
    
    if (day < 1 || day > 31) {
        return -1;
    }
    
    snprintf(output, output_size, "%02d-%02d-%04d", day, month, year);
    
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_date[DATE_LENGTH];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output_date[DATE_LENGTH];
    
    printf("Enter date (yyyy-mm-dd): ");
    if (fgets(input_date, sizeof(input_date), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    input_date[strcspn(input_date, "\n")] = '\0';
    
    if (convert_date_format(input_date, output_date, sizeof(output_date)) != 0) {
        fprintf(stderr, "Invalid date format\n");
        return 1;
    }
    
    printf("Converted date: %s\n", output_date);
    
    return 0;
}