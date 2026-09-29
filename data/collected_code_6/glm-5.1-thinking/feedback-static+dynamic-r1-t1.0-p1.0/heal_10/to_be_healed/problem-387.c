#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *read_line(void) {
    size_t capacity = 256;
    size_t length = 0;
    char *buffer = malloc(capacity);
    if (!buffer) {
        return NULL;
    }
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF && c != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            if (new_capacity < capacity) {
                free(buffer);
                return NULL;
            }
            char *new_buffer = realloc(buffer, new_capacity);
            if (!new_buffer) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }
        buffer[length++] = (char)c;
    }
    if (length + 1 >= capacity) {
        /* Possible weaknesses found:
         *  new_capacity is assigned 'capacity+1' here.
         */
        size_t new_capacity = capacity + 1;
        /* Possible weaknesses found:
         *  Condition 'new_capacity<capacity' is always false
         *  Condition 'new_capacity<capacity' is always false [knownConditionTrueFalse]
         */
        if (new_capacity < capacity) {
            free(buffer);
            return NULL;
        }
        char *new_buffer = realloc(buffer, new_capacity);
        if (!new_buffer) {
            free(buffer);
            return NULL;
        }
        buffer = new_buffer;
        /* Possible weaknesses found:
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         */
        capacity = new_capacity;
    }
    buffer[length] = '\0';
    return buffer;
}

int is_hex_even(const char *hex_str) {
    if (hex_str == NULL) {
        return -1;
    }
    const char *p = hex_str;
    while (isspace((unsigned char)*p)) {
        p++;
    }
    if (*p == '\0') {
        return -1;
    }
    if (p[0] == '0' && p[1] != '\0' && (p[1] == 'x' || p[1] == 'X')) {
        p += 2;
    }
    if (*p == '\0') {
        return -1;
    }
    const char *end_hex = NULL;
    while (*p) {
        if (!isxdigit((unsigned char)*p)) {
            break;
        }
        end_hex = p;
        p++;
    }
    while (isspace((unsigned char)*p)) {
        p++;
    }
    if (*p != '\0' || end_hex == NULL) {
        return -1;
    }
    char last = *end_hex;
    switch (last) {
        case '0': case '2': case '4': case '6': case '8':
        case 'a': case 'A': case 'c': case 'C': case 'e': case 'E':
            return 1;
        default:
            return 0;
    }
}

int main(void) {
    char *buffer = read_line();
    if (buffer == NULL) {
        return EXIT_FAILURE;
    }
    int result = is_hex_even(buffer);
    if (result == 1) {
        printf("Even\n");
    } else if (result == 0) {
        printf("Odd\n");
    } else {
        printf("Invalid\n");
    }
    free(buffer);
    return EXIT_SUCCESS;
}