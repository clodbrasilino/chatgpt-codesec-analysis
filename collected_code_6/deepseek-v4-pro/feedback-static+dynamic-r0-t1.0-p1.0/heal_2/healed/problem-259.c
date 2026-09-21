#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

typedef struct {
    int *data;
    int size;
} Tuple;

static int safe_strtoi(const char *str, int *value) {
    char *endptr;
    long val;
    
    if (!str || !value) return 0;
    
    while (isspace((unsigned char)*str)) str++;
    
    if (*str == '\0') return 0;
    
    errno = 0;
    val = strtol(str, &endptr, 10);
    
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        return 0;
    }
    if (endptr == str) {
        return 0;
    }
    
    while (*endptr && isspace((unsigned char)*endptr)) endptr++;
    
    if (*endptr != '\0') return 0;
    
    *value = (int)val;
    return 1;
}

static int count_elements(const char *str) {
    int count = 0;
    const char *p = str;
    int in_element = 0;
    
    while (*p) {
        if (*p == ',') {
            count++;
            in_element = 0;
        } else if (!isspace((unsigned char)*p)) {
            in_element = 1;
        }
        p++;
    }
    
    if (in_element) count++;
    
    return count;
}

int parse_tuple(const char *str, Tuple *tuple) {
    if (!str || !tuple) return 0;
    
    int count = count_elements(str);
    
    if (count <= 0) return 0;
    
    tuple->size = count;
    tuple->data = (int *)malloc(tuple->size * sizeof(int));
    
    if (!tuple->data) {
        tuple->size = 0;
        return 0;
    }
    
    const char *p = str;
    size_t buffer_size = 64;
    char *buffer = (char *)malloc(buffer_size);
    
    if (!buffer) {
        free(tuple->data);
        tuple->data = NULL;
        tuple->size = 0;
        return 0;
    }
    
    for (int i = 0; i < tuple->size; i++) {
        size_t j = 0;
        
        while (*p && isspace((unsigned char)*p)) p++;
        
        while (*p && *p != ',') {
            if (j >= buffer_size - 1) {
                buffer_size *= 2;
                char *new_buffer = (char *)realloc(buffer, buffer_size);
                if (!new_buffer) {
                    free(buffer);
                    free(tuple->data);
                    tuple->data = NULL;
                    tuple->size = 0;
                    return 0;
                }
                buffer = new_buffer;
            }
            buffer[j++] = *p++;
        }
        
        buffer[j] = '\0';
        
        if (!safe_strtoi(buffer, &tuple->data[i])) {
            free(buffer);
            free(tuple->data);
            tuple->data = NULL;
            tuple->size = 0;
            return 0;
        }
        
        if (*p == ',') p++;
    }
    
    free(buffer);
    return 1;
}

void maximize_tuples(Tuple *t1, Tuple *t2) {
    if (!t1 || !t2 || !t1->data || !t2->data) return;
    
    int size = (t1->size < t2->size) ? t1->size : t2->size;
    
    for (int i = 0; i < size; i++) {
        if (t2->data[i] > t1->data[i]) {
            t1->data[i] = t2->data[i];
        }
    }
}

void print_tuple(const Tuple *tuple) {
    if (!tuple || !tuple->data) return;
    
    printf("(");
    for (int i = 0; i < tuple->size; i++) {
        printf("%d", tuple->data[i]);
        if (i < tuple->size - 1) printf(", ");
    }
    printf(")\n");
}

void free_tuple(Tuple *tuple) {
    if (!tuple) return;
    
    if (tuple->data) {
        free(tuple->data);
        tuple->data = NULL;
    }
    tuple->size = 0;
}

int main(void) {
    Tuple tuple1 = {NULL, 0};
    Tuple tuple2 = {NULL, 0};
    
    if (parse_tuple("1, 5, 3, 9", &tuple1) &&
        parse_tuple("2, 4, 8, 6", &tuple2)) {
        
        printf("Before maximization:\n");
        printf("Tuple 1: ");
        print_tuple(&tuple1);
        printf("Tuple 2: ");
        print_tuple(&tuple2);
        
        maximize_tuples(&tuple1, &tuple2);
        
        printf("\nAfter maximization:\n");
        printf("Tuple 1: ");
        print_tuple(&tuple1);
        printf("Tuple 2: ");
        print_tuple(&tuple2);
    }
    
    free_tuple(&tuple1);
    free_tuple(&tuple2);
    
    return 0;
}