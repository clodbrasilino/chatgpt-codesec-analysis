#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

typedef struct {
    int *values;
    size_t count;
} IntTuple;

void free_int_tuple(IntTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->values);
        tuple->values = NULL;
        tuple->count = 0;
    }
}

static int safe_str_copy(char *dest, size_t dest_size, const char *src, size_t src_len) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return -1;
    }
    
    if (src_len >= dest_size) {
        dest[0] = '\0';
        return -1;
    }
    
    size_t copy_len = src_len;
    if (copy_len > dest_size - 1) {
        dest[0] = '\0';
        return -1;
    }
    
    memcpy(dest, src, copy_len);
    dest[copy_len] = '\0';
    
    return 0;
}

int parse_tuple_string(const char *str, IntTuple *result) {
    if (str == NULL || result == NULL) {
        errno = EINVAL;
        return -1;
    }

    result->values = NULL;
    result->count = 0;

    size_t len = strnlen(str, 65536);
    if (len >= 65536 || len < 2) {
        errno = EINVAL;
        return -1;
    }

    if (str[0] != '(' || str[len - 1] != ')') {
        errno = EINVAL;
        return -1;
    }

    if (len == 2) {
        result->values = NULL;
        result->count = 0;
        return 0;
    }

    size_t start = 1;
    size_t end = len - 1;
    size_t capacity = 0;
    size_t count = 0;
    int *values = NULL;
    char *temp = NULL;
    size_t temp_size = 64;
    
    temp = (char *)malloc(temp_size);
    if (temp == NULL) {
        errno = ENOMEM;
        return -1;
    }
    temp[0] = '\0';

    while (start < end) {
        while (start < end && isspace((unsigned char)str[start])) {
            start++;
        }
        if (start >= end) {
            break;
        }

        if (str[start] == ',') {
            free(values);
            free(temp);
            errno = EINVAL;
            return -1;
        }

        size_t num_start = start;
        while (start < end && str[start] != ',') {
            start++;
        }
        size_t num_end = start;

        while (num_end > num_start && isspace((unsigned char)str[num_end - 1])) {
            num_end--;
        }

        if (num_end == num_start) {
            free(values);
            free(temp);
            errno = EINVAL;
            return -1;
        }

        size_t num_len = num_end - num_start;
        if (num_len + 1 > temp_size) {
            size_t new_temp_size = num_len + 1;
            if (new_temp_size < num_len + 1) {
                free(values);
                free(temp);
                errno = ENOMEM;
                return -1;
            }
            char *new_temp = (char *)realloc(temp, new_temp_size);
            if (new_temp == NULL) {
                free(values);
                free(temp);
                errno = ENOMEM;
                return -1;
            }
            temp = new_temp;
            temp_size = new_temp_size;
        }

        if (num_len >= temp_size) {
            free(values);
            free(temp);
            errno = EOVERFLOW;
            return -1;
        }
        
        if (safe_str_copy(temp, temp_size, str + num_start, num_len) != 0) {
            free(values);
            free(temp);
            errno = EINVAL;
            return -1;
        }

        char *endptr = NULL;
        errno = 0;
        long val = strtol(temp, &endptr, 10);
        if (errno != 0 || endptr == temp || *endptr != '\0' || val > INT_MAX || val < INT_MIN) {
            free(values);
            free(temp);
            errno = EINVAL;
            return -1;
        }

        if (count == capacity) {
            size_t new_capacity = (capacity == 0) ? 4 : capacity * 2;
            if (new_capacity > SIZE_MAX / sizeof(int)) {
                free(values);
                free(temp);
                errno = ENOMEM;
                return -1;
            }
            int *new_values = (int *)realloc(values, new_capacity * sizeof(int));
            if (new_values == NULL) {
                free(values);
                free(temp);
                errno = ENOMEM;
                return -1;
            }
            values = new_values;
            capacity = new_capacity;
        }

        values[count++] = (int)val;

        if (start < end) {
            if (str[start] == ',') {
                start++;
                if (start >= end) {
                    free(values);
                    free(temp);
                    errno = EINVAL;
                    return -1;
                }
            } else {
                free(values);
                free(temp);
                errno = EINVAL;
                return -1;
            }
        }
    }

    free(temp);
    result->values = values;
    result->count = count;
    return 0;
}

int main(void) {
    const char *test1 = "(1, 2, 3, 4, 5)";
    const char *test2 = "()";
    const char *test3 = "(10,20,30)";
    const char *test4 = "invalid";
    const char *test5 = "(1, 2, )";
    const char *test6 = "(1, abc, 3)";

    IntTuple tuple;
    
    if (parse_tuple_string(test1, &tuple) == 0) {
        printf("Test1: ");
        for (size_t i = 0; i < tuple.count; i++) {
            printf("%d ", tuple.values[i]);
        }
        printf("\n");
        free_int_tuple(&tuple);
    } else {
        printf("Test1 failed: %s\n", strerror(errno));
    }

    if (parse_tuple_string(test2, &tuple) == 0) {
        printf("Test2: count=%zu\n", tuple.count);
        free_int_tuple(&tuple);
    } else {
        printf("Test2 failed: %s\n", strerror(errno));
    }

    if (parse_tuple_string(test3, &tuple) == 0) {
        printf("Test3: ");
        for (size_t i = 0; i < tuple.count; i++) {
            printf("%d ", tuple.values[i]);
        }
        printf("\n");
        free_int_tuple(&tuple);
    } else {
        printf("Test3 failed: %s\n", strerror(errno));
    }

    if (parse_tuple_string(test4, &tuple) == 0) {
        printf("Test4: ");
        for (size_t i = 0; i < tuple.count; i++) {
            printf("%d ", tuple.values[i]);
        }
        printf("\n");
        free_int_tuple(&tuple);
    } else {
        printf("Test4 failed: %s\n", strerror(errno));
    }

    if (parse_tuple_string(test5, &tuple) == 0) {
        printf("Test5: ");
        for (size_t i = 0; i < tuple.count; i++) {
            printf("%d ", tuple.values[i]);
        }
        printf("\n");
        free_int_tuple(&tuple);
    } else {
        printf("Test5 failed: %s\n", strerror(errno));
    }

    if (parse_tuple_string(test6, &tuple) == 0) {
        printf("Test6: ");
        for (size_t i = 0; i < tuple.count; i++) {
            printf("%d ", tuple.values[i]);
        }
        printf("\n");
        free_int_tuple(&tuple);
    } else {
        printf("Test6 failed: %s\n", strerror(errno));
    }

    return 0;
}