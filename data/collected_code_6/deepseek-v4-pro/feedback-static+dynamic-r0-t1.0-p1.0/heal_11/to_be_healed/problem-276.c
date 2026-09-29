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
    
    if (buffer == NULL || size == 0) {
        return false;
    }
    
    printf("%s", prompt);
    fflush(stdout);
    
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return false;
    }
    
    len = strnlen(buffer, size);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        bool truncated = false;
        if (len == size - 1 && buffer[size - 2] != '\0' && buffer[size - 2] != '\n') {
            truncated = true;
        }
        
        if (truncated) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            
            if (ferror(stdin)) {
                clearerr(stdin);
            }
            
            buffer[0] = '\0';
            return false;
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
    
    if (isinf(*value)) {
        return false;
    }
    
    return true;
}

int main(void) {
    double radius, height, volume;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE];
    
    if (!read_input_line("Enter radius: ", input, sizeof(input))) {
        printf("Error: Failed to read radius input.\n");
        return 1;
    }
    
    if (!parse_double(input, &radius)) {
        printf("Error: Invalid radius input.\n");
        return 1;
    }
    
    if (!read_input_line("Enter height: ", input, sizeof(input))) {
        printf("Error: Failed to read height input.\n");
        return 1;
    }
    
    if (!parse_double(input, &height)) {
        printf("Error: Invalid height input.\n");
        return 1;
    }
    
    volume = cylinder_volume(radius, height);
    
    if (volume < 0.0) {
        printf("Error: Radius and height must be positive values.\n");
        return 1;
    }
    
    printf("Volume of cylinder: %.2f\n", volume);
    
    return 0;
}