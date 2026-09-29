#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define TUPLE_SIZE 3

typedef struct {
    char *values[TUPLE_SIZE];
} StringTuple;

typedef struct {
    int values[TUPLE_SIZE];
} IntTuple;

int convert_string_tuple_to_int_tuple(const StringTuple *input, IntTuple *output) {
    if (input == NULL || output == NULL) {
        return -1;
    }

    for (size_t i = 0; i < TUPLE_SIZE; i++) {
        if (input->values[i] == NULL) {
            return -1;
        }

        char *endptr = NULL;
        errno = 0;
        
        long val = strtol(input->values[i], &endptr, 10);
        
        if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
            return -1;
        }
        
        if (endptr == input->values[i] || *endptr != '\0') {
            return -1;
        }
        
        output->values[i] = (int)val;
    }
    
    return 0;
}

int main(void) {
    StringTuple str_tuple = {
        .values = {"123", "456", "789"}
    };
    
    IntTuple int_tuple = {0};
    
    if (convert_string_tuple_to_int_tuple(&str_tuple, &int_tuple) != 0) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }
    
    printf("(%d, %d, %d)\n", 
           int_tuple.values[0], 
           int_tuple.values[1], 
           int_tuple.values[2]);
    
    return EXIT_SUCCESS;
}