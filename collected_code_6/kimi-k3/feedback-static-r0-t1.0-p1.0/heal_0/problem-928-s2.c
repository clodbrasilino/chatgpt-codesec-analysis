#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DATE_LENGTH 10
#define BUFFER_SIZE 11

bool is_valid_date_format(const char *date) {
    if (date == NULL || strlen(date) != DATE_LENGTH) {
        return false;
    }
    
    if (date[4] != '-' || date[7] != '-') {
        return false;
    }
    
    for (int i = 0; i < DATE_LENGTH; i++) {
        if (i == 4 || i == 7) {
            continue;
        }
        if (date[i] < '0' || date[i] > '9') {
            return false;
        }
    }
    
    return true;
}

bool is_valid_date_values(int year, int month, int day) {
    if (month < 1 || month > 12) {
        return false;
    }
    
    if (day < 1 || day > 31) {
        return false;
    }
    
    if (year < 1) {
        return false;
    }
    
    return true;
}

int convert_date_format(const char *input_date, char *output_date, size_t output_size) {
    if (input_date == NULL || output_date == NULL) {
        return -1;
    }
    
    if (output_size < BUFFER_SIZE) {
        return -2;
    }
    
    if (!is_valid_date_format(input_date)) {
        return -3;
    }
    
    int year = (input_date[0] - '0') * 1000 + 
               (input_date[1] - '0') * 100 + 
               (input_date[2] - '0') * 10 + 
               (input_date[3] - '0');
    
    int month = (input_date[5] - '0') * 10 + (input_date[6] - '0');
    
    int day = (input_date[8] - '0') * 10 + (input_date[9] - '0');
    
    if (!is_valid_date_values(year, month, day)) {
        return -4;
    }
    
    int result = snprintf(output_date, output_size, "%02d-%02d-%04d", day, month, year);
    
    if (result < 0 || (size_t)result >= output_size) {
        return -5;
    }
    
    return 0;
}

int main(void) {
    char input_date[BUFFER_SIZE];
    char output_date[BUFFER_SIZE];
    
    printf("Enter date in yyyy-mm-dd format: ");
    
    if (fgets(input_date, sizeof(input_date), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strlen(input_date);
    if (len > 0 && input_date[len - 1] == '\n') {
        input_date[len - 1] = '\0';
    }
    
    int result = convert_date_format(input_date, output_date, sizeof(output_date));
    
    if (result == 0) {
        printf("Converted date (dd-mm-yyyy): %s\n", output_date);
    } else {
        switch (result) {
            case -1:
                fprintf(stderr, "Error: NULL pointer provided\n");
                break;
            case -2:
                fprintf(stderr, "Error: Output buffer too small\n");
                break;
            case -3:
                fprintf(stderr, "Error: Invalid date format. Expected yyyy-mm-dd\n");
                break;
            case -4:
                fprintf(stderr, "Error: Invalid date values\n");
                break;
            case -5:
                fprintf(stderr, "Error: Formatting error\n");
                break;
            default:
                fprintf(stderr, "Error: Unknown error\n");
                break;
        }
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}