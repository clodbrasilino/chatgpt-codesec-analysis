#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'log10'
  */

typedef struct {
    int a;
    int b;
} Tuple;

char* flatten_tuple_list(Tuple* list, size_t count) {
    if (list == NULL && count > 0) {
        return NULL;
    }

    size_t capacity = 64;
    char* buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    size_t length = 0;
    buffer[0] = '\0';

    for (size_t i = 0; i < count; i++) {
        int a_val = list[i].a;
        int b_val = list[i].b;
        int written;

        size_t required = sizeof("(, )") - 1;
        /* Possible weaknesses found:
         *  call to undeclared library function 'log10' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <math.h> or explicitly provide a declaration for 'log10'
         *  implicit declaration of function 'log10' [-Wimplicit-function-declaration]
         */
        if (a_val == INT_MIN) required += 11; else required += (a_val <= 0) + (a_val > 0 ? (int)log10(abs(a_val)) + 1 : 0);
        if (b_val == INT_MIN) required += 11; else required += (b_val <= 0) + (b_val > 0 ? (int)log10(abs(b_val)) + 1 : 0);
        if (i > 0) required += sizeof(", ") - 1;
        
        size_t temp_size = required + 1;
        char* temp = malloc(temp_size);
        if (temp == NULL) {
            free(buffer);
            return NULL;
        }

        if (i == 0) {
            written = snprintf(temp, temp_size, "(%d, %d)", a_val, b_val);
        } else {
            written = snprintf(temp, temp_size, ", (%d, %d)", a_val, b_val);
        }

        if (written < 0) {
            free(temp);
            free(buffer);
            return NULL;
        }

        size_t temp_len = (size_t)written;
        if (temp_len >= temp_size) {
            temp_len = temp_size - 1;
        }

        if (length + temp_len + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            while (length + temp_len + 1 >= new_capacity) {
                new_capacity *= 2;
            }
            if (new_capacity <= capacity) {
                free(temp);
                free(buffer);
                return NULL;
            }
            char* new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(temp);
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }

        if (length + temp_len <= capacity) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buffer + length, temp, temp_len);
        } else {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buffer + length, temp, capacity - length);
        }
        buffer[length + temp_len] = '\0';
        length += temp_len;
        
        free(temp);
    }

    char* result = realloc(buffer, length + 1);
    if (result != NULL) {
        buffer = result;
    }

    return buffer;
}

int main(void) {
    Tuple list[] = {{1, 2}, {3, 4}, {5, 6}};
    size_t count = sizeof(list) / sizeof(list[0]);

    char* flattened = flatten_tuple_list(list, count);
    if (flattened == NULL) {
        return 1;
    }

    printf("%s\n", flattened);

    free(flattened);
    flattened = NULL;

    return 0;
}