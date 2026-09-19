#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** increment_numeric_values(const char* input, int k, int* out_count) {
    if (!input || !out_count) {
        if (out_count) *out_count = 0;
        return NULL;
    }

    int count = 0;
    char* copy1 = (char*)malloc(strlen(input) + 1);
    if (!copy1) {
        *out_count = 0;
        return NULL;
    }
    strcpy(copy1, input);

    char* token = strtok(copy1, " \t\n");
    while (token) {
        count++;
        token = strtok(NULL, " \t\n");
    }
    free(copy1);

    *out_count = count;
    if (count == 0) {
        return NULL;
    }

    char** result = (char**)malloc(count * sizeof(char*));
    if (!result) {
        *out_count = 0;
        return NULL;
    }

    char* copy2 = (char*)malloc(strlen(input) + 1);
    if (!copy2) {
        free(result);
        *out_count = 0;
        return NULL;
    }
    strcpy(copy2, input);

    token = strtok(copy2, " \t\n");
    int i = 0;
    while (token && i < count) {
        int is_num = 1;
        int j = 0;
        
        if (token[0] == '-' || token[0] == '+') {
            j = 1;
        }
        
        if (token[j] == '\0') {
            is_num = 0;
        }
        
        for (; token[j] != '\0'; j++) {
            if (!isdigit((unsigned char)token[j])) {
                is_num = 0;
                break;
            }
        }

        if (is_num) {
            long long val = strtoll(token, NULL, 10);
            val += k;
            char buf[64];
            snprintf(buf, sizeof(buf), "%lld", val);
            result[i] = (char*)malloc(strlen(buf) + 1);
            if (result[i]) strcpy(result[i], buf);
        } else {
            result[i] = (char*)malloc(strlen(token) + 1);
            if (result[i]) strcpy(result[i], token);
        }

        i++;
        token = strtok(NULL, " \t\n");
    }

    free(copy2);
    return result;
}

int main(void) {
    int count = 0;
    char** res = increment_numeric_values("MSM 230 is 94 119 best 0", 10, &count);
    if (res) {
        printf("[");
        for (int i = 0; i < count; i++) {
            printf("'%s'", res[i]);
            if (i < count - 1) {
                printf(", ");
            }
            free(res[i]);
        }
        printf("]\n");
        free(res);
    } else {
        printf("[]\n");
    }
    return 0;
}