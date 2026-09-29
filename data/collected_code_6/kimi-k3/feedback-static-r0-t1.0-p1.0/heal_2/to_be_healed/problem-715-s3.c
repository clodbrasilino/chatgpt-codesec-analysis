#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

Tuple string_to_tuple(const char *str) {
    Tuple t = {NULL, 0};
    if (str == NULL) {
        return t;
    }
    
    size_t count = 0;
    const char *p = str;
    while (*p != '\0') {
        if (*p == ',') {
            count++;
        }
        p++;
    }
    if (p != str) {
        count++;
    }
    
    if (count == 0) {
        return t;
    }
    
    t.data = malloc(count * sizeof(int));
    if (t.data == NULL) {
        return t;
    }
    
    t.size = count;
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    char *copy = malloc(str_len + 1);
    if (copy == NULL) {
        free(t.data);
        t.data = NULL;
        t.size = 0;
        return t;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, str, str_len + 1);
    
    char *saveptr = NULL;
    char *token = strtok_r(copy, ",", &saveptr);
    size_t i = 0;
    while (token != NULL && i < t.size) {
        errno = 0;
        char *endptr;
        long val = strtol(token, &endptr, 10);
        
        if (errno == ERANGE || val > INT_MAX || val < INT_MIN || endptr == token || *endptr != '\0') {
            free(copy);
            free(t.data);
            t.data = NULL;
            t.size = 0;
            return t;
        }
        
        t.data[i] = (int)val;
        i++;
        token = strtok_r(NULL, ",", &saveptr);
    }
    
    free(copy);
    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->data);
        t->data = NULL;
        t->size = 0;
    }
}

int main(void) {
    const char *input = "1,2,3,4,5";
    Tuple t = string_to_tuple(input);
    
    if (t.data != NULL) {
        printf("Tuple: (");
        for (size_t i = 0; i < t.size; i++) {
            printf("%d", t.data[i]);
            if (i < t.size - 1) {
                printf(", ");
            }
        }
        printf(")\n");
        free_tuple(&t);
    } else {
        printf("Failed to create tuple\n");
    }
    
    return 0;
}