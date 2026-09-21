#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <float.h>
#include <stdbool.h>
#include <limits.h>

#define INPUT_BUFFER_SIZE 256

double cylinder_volume(double radius, double height) {
    if (radius <= 0.0 || height <= 0.0) {
        return -1.0;
    }
    return M_PI * radius * radius * height;
}

static bool read_input_line(const char *prompt, char *buffer, size_t size) {
    size_t len;
    int c;
    
    if (buffer == NULL || size == 0) {
        return false;
    }
    
    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return false;
    }
    
    len = strnlen(buffer, size);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == size - 1) {
        if (buffer[size - 2] != '\0') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            if (ferror(stdin)) {
                clearerr(stdin);
            }
        }
    }
    
    return true;
}

static bool parse_double(const char *str, double *value) {
    char *endptr;
    
    if (str == NULL || value == NULL) {
        return false;
    }
    
    if (str[0] == '\0') {
        return false;
    }
    
    errno = 0;
    *value = strtod(str, &endptr);
    
    if (endptr == str || *endptr != '\0') {
        return false;
    }
    
    if (errno == ERANGE) {
        return false;
    }
    
    if (*value == HUGE_VAL || *value == -HUGE_VAL) {
        return false;
    }
    
    return true;
}

int main(void) {
    double radius, height, volume;
    char *input;
    size_t input_size = INPUT_BUFFER_SIZE;
    
    input = (char*)calloc(input_size, sizeof(char));
    if (input == NULL) {
        return 1;
    }
    
    if (!read_input_line("Enter radius: ", input, input_size)) {
        free(input);
        return 1;
    }
    
    if (!parse_double(input, &radius)) {
        printf("Error: Invalid radius input.\n");
        free(input);
        return 1;
    }
    
    if (!read_input_line("Enter height: ", input, input_size)) {
        free(input);
        return 1;
    }
    
    if (!parse_double(input, &height)) {
        printf("Error: Invalid height input.\n");
        free(input);
        return 1;
    }
    
    volume = cylinder_volume(radius, height);
    
    if (volume < 0.0) {
        printf("Error: Radius and height must be positive values.\n");
        free(input);
        return 1;
    }
    
    printf("Volume of cylinder: %.2f\n", volume);
    
    free(input);
    return 0;
}