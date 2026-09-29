#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

static void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    if (tuple->items != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
    }
    tuple->items = NULL;
    tuple->count = 0;
}

static char *trim_whitespace(char *str, size_t len) {
    char *end;
    
    if (str == NULL || len == 0) {
        return str;
    }
    
    while (len > 0 && isspace((unsigned char)*str)) {
        str++;
        len--;
    }
    
    if (len == 0) {
        return str;
    }
    
    end = str + len - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }
    end[1] = '\0';
    
    return str;
}

static char *safe_strdup(const char *src, size_t max_len) {
    size_t len;
    char *dst;
    
    if (src == NULL || max_len == 0) {
        return NULL;
    }
    
    len = strnlen(src, max_len);
    if (len == max_len && src[len] != '\0') {
        return NULL;
    }
    len++;
    
    if (len > max_len + 1) {
        return NULL;
    }
    
    dst = malloc(len);
    if (dst == NULL) {
        return NULL;
    }
    
    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(dst, src, len - 1);
        dst[len - 1] = '\0';
    }
    
    return dst;
}

int string_to_tuple(const char *input, Tuple *result) {
    char *buffer;
    char *token;
    char *saveptr;
    char **temp_items;
    size_t capacity = 10;
    size_t count = 0;
    size_t input_len;
    
    if (input == NULL || result == NULL) {
        return -1;
    }
    
    result->items = NULL;
    result->count = 0;
    
    input_len = strnlen(input, 4096);
    if (input_len == 4096 && input[input_len] != '\0') {
        return -1;
    }
    
    buffer = safe_strdup(input, 4096);
    if (buffer == NULL) {
        return -1;
    }
    
    temp_items = malloc(capacity * sizeof(char *));
    if (temp_items == NULL) {
        free(buffer);
        return -1;
    }
    
    token = strtok_r(buffer, ",", &saveptr);
    while (token != NULL) {
        size_t token_len = strnlen(token, 4096);
        const char *trimmed = trim_whitespace(token, token_len);
        
        if (count >= capacity) {
            char **new_items;
            capacity *= 2;
            new_items = realloc(temp_items, capacity * sizeof(char *));
            if (new_items == NULL) {
                for (size_t i = 0; i < count; i++) {
                    free(temp_items[i]);
                }
                free(temp_items);
                free(buffer);
                return -1;
            }
            temp_items = new_items;
        }
        
        temp_items[count] = safe_strdup(trimmed, 1024);
        if (temp_items[count] == NULL) {
            for (size_t i = 0; i < count; i++) {
                free(temp_items[i]);
            }
            free(temp_items);
            free(buffer);
            return -1;
        }
        count++;
        
        token = strtok_r(NULL, ",", &saveptr);
    }
    
    free(buffer);
    
    if (count == 0) {
        free(temp_items);
        result->items = NULL;
        result->count = 0;
        return 0;
    }
    
    result->items = temp_items;
    result->count = count;
    return 0;
}

int main(void) {
    const char *input = "apple, banana, cherry, date";
    Tuple tuple;
    int status;
    
    status = string_to_tuple(input, &tuple);
    if (status != 0) {
        fprintf(stderr, "Error converting string to tuple\n");
        return EXIT_FAILURE;
    }
    
    printf("(");
    for (size_t i = 0; i < tuple.count; i++) {
        printf("\"%s\"", tuple.items[i]);
        if (i < tuple.count - 1) {
            printf(", ");
        }
    }
    printf(")\n");
    
    free_tuple(&tuple);
    
    return EXIT_SUCCESS;
}