#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    size_t cap = 1048576;
    char *buffer = malloc(cap);
    if (!buffer) return 1;
    
    size_t len = fread(buffer, 1, cap - 1, stdin);
    buffer[len] = '\0';

    char *bracket = strrchr(buffer, ']');
    int k = 0;
    if (bracket) {
        char *k_ptr = bracket + 1;
        while (*k_ptr && !isdigit((unsigned char)*k_ptr)) {
            k_ptr++;
        }
        if (*k_ptr) {
            k = atoi(k_ptr);
        }
    }

    char *p = strchr(buffer, '[');
    if (!p) p = buffer;
    char *end = bracket ? bracket : buffer + len;

    printf("[");
    int list_comma = 0;
    
    while (p < end) {
        p = strchr(p, '(');
        if (!p || p >= end) break;
        p++;

        int temp[2000];
        int size = 0;
        
        char *q = strchr(p, ')');
        if (!q || q > end) break;

        char *num_p = p;
        while (num_p < q) {
            if (isdigit((unsigned char)*num_p) || (*num_p == '-' && isdigit((unsigned char)*(num_p+1)))) {
                temp[size++] = strtol(num_p, &num_p, 10);
            } else {
                num_p++;
            }
        }

        if (size != k) {
            if (list_comma) printf(", ");
            printf("(");
            for (int i = 0; i < size; i++) {
                printf("%d", temp[i]);
                if (i < size - 1) printf(", ");
            }
            if (size == 1) printf(",");
            printf(")");
            list_comma = 1;
        }
        p = q + 1;
    }
    
    printf("]\n");
    free(buffer);
    
    return 0;
}