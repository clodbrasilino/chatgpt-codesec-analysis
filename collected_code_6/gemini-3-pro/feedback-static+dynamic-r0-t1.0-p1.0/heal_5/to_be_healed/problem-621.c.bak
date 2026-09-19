#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char str[8192];
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 0;
    }

    char k_line[256];
    if (fgets(k_line, sizeof(k_line), stdin) == NULL) {
        return 0;
    }
    int k = atoi(k_line);

    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
        len--;
    }

    char *start = str;
    if (len >= 2 && ((start[0] == '"' && start[len - 1] == '"') || (start[0] == '\'' && start[len - 1] == '\''))) {
        start[len - 1] = '\0';
        start++;
    }

    printf("[");
    int first = 1;
    char *token = strtok(start, " \t");
    while (token != NULL) {
        if (!first) {
            printf(", ");
        }
        first = 0;

        int is_num = 1;
        int i = 0;
        if (token[0] == '-') {
            i = 1;
        }
        if (token[i] == '\0') {
            is_num = 0;
        }
        for (; token[i] != '\0'; i++) {
            if (!isdigit((unsigned char)token[i])) {
                is_num = 0;
                break;
            }
        }

        if (is_num) {
            long val = atol(token);
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 9223372036854775807 + 8 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000000,time:4432,execs:1626,op:havoc,rep:6)
             */
            printf("'%ld'", val + k);
        } else {
            printf("'%s'", token);
        }

        token = strtok(NULL, " \t");
    }
    printf("]\n");

    return 0;
}