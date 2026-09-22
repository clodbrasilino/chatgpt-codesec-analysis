#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char input[10000];
    int len = 0;
    int c;
    while ((c = getchar()) != EOF) {
        if (len < 9999) {
            input[len++] = c;
        }
    }
    input[len] = '\0';

    char *start = strchr(input, '[');
    char *end = strrchr(input, ']');
    if (!start || !end || start > end) {
        return 0;
    }

    int k = atoi(end + 1);

    printf("[");
    int first = 1;
    char *p = start + 1;
    
    while (p < end) {
        if (*p == '(') {
            char *q = p + 1;
            int count = 0;
            int found_digit = 0;
            char *tmpp = p + 1;
            
            while (q < end && *q != ')') {
                q++;
            }
            
            while (tmpp < q) {
                if (isdigit((unsigned char)*tmpp) || *tmpp == '-') {
                    found_digit = 1;
                }
                if (*tmpp == ',') {
                    if (found_digit) {
                        count++;
                    }
                    found_digit = 0;
                }
                tmpp++;
            }
            if (found_digit) {
                count++;
            }
            
            if (count != k) {
                if (!first) {
                    printf(", ");
                }
                first = 0;
                for (char *c_ptr = p; c_ptr <= q; c_ptr++) {
                    putchar(*c_ptr);
                }
            }
            p = q + 1;
        } else {
            p++;
        }
    }
    printf("]\n");

    return 0;
}