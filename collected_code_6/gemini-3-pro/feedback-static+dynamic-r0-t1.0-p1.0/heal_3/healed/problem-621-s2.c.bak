#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** increment_numeric_values(const char* input, int k, int* out_count) {
    if (!input || !out_count) return NULL;

    char** result = NULL;
    int count = 0;
    
    char* copy = strdup(input);
    if (!copy) return NULL;

    char* token = strtok(copy, " \t\n");
    while (token) {
        char** temp = realloc(result, sizeof(char*) * (count + 2));
        if (!temp) {
            for (int i = 0; i < count; i++) {
                free(result[i]);
            }
            free(result);
            free(copy);
            *out_count = 0;
            return NULL;
        }
        result = temp;
        
        int is_num = 1;
        if (token[0] == '\0') {
            is_num = 0;
        }
        for (int i = 0; token[i]; i++) {
            if (!isdigit((unsigned char)token[i]) && !(i == 0 && (token[i] == '-' || token[i] == '+') && token[i+1] != '\0')) {
                is_num = 0;
                break;
            }
        }
        
        if (is_num) {
            long long val = strtoll(token, NULL, 10);
            val += k;
            char buf[64];
            snprintf(buf, sizeof(buf), "%lld", val);
            result[count] = strdup(buf);
        } else {
            result[count] = strdup(token);
        }
        
        if (!result[count]) {
            for (int i = 0; i < count; i++) {
                free(result[i]);
            }
            free(result);
            free(copy);
            *out_count = 0;
            return NULL;
        }
        
        count++;
        result[count] = NULL;
        token = strtok(NULL, " \t\n");
    }
    
    free(copy);
    *out_count = count;
    
    if (count == 0) {
        free(result);
        return NULL;
    }
    
    return result;
}

int main(void) {
    int count = 0;
    char** res = increment_numeric_values("MSM 230 is 94 119 best 0", 10, &count);
    if (res) {
        for (int i = 0; i < count; i++) {
            printf("'%s' ", res[i]);
            free(res[i]);
        }
        printf("\n");
        free(res);
    }
    return 0;
}