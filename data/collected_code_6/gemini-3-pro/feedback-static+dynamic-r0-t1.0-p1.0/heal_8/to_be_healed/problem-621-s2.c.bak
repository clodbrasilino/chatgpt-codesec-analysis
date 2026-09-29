#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* custom_strdup(const char* s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    char* copy = (char*)malloc(len + 1);
    if (copy) {
        strcpy(copy, s);
    }
    return copy;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['MSM', '240', 'is', '104', '129', 'best', '10'], got ["���"]
  *  test case 1 failed: expected ['Dart', '368', 'is', '100', '181', 'Super', '18'], got ["���"]
  *  test case 2 failed: expected ['Flutter', '484', 'is', '77', '129', 'Magnificent', '45'], got ["���"]
  */

char** increment_numeric_values(const char* input, int k, int* out_count) {
    if (!input || !out_count) {
        if (out_count) *out_count = 0;
        return NULL;
    }

    char* count_copy = custom_strdup(input);
    if (!count_copy) {
        *out_count = 0;
        return NULL;
    }

    int count = 0;
    char* token = strtok(count_copy, " \t\n");
    while (token) {
        count++;
        token = strtok(NULL, " \t\n");
    }
    free(count_copy);

    *out_count = count;
    if (count == 0) {
        return NULL;
    }

    char** result = (char**)malloc((count + 1) * sizeof(char*));
    if (!result) {
        *out_count = 0;
        return NULL;
    }

    char* process_copy = custom_strdup(input);
    if (!process_copy) {
        free(result);
        *out_count = 0;
        return NULL;
    }

    token = strtok(process_copy, " \t\n");
    int i = 0;
    while (token && i < count) {
        int is_num = 1;
        if (token[0] == '\0') {
            is_num = 0;
        } else {
            for (int j = 0; token[j] != '\0'; j++) {
                if (!isdigit((unsigned char)token[j])) {
                    if (j == 0 && (token[j] == '-' || token[j] == '+') && token[j + 1] != '\0') {
                        continue;
                    }
                    is_num = 0;
                    break;
                }
            }
        }

        if (is_num) {
            long long val = strtoll(token, NULL, 10);
            val += k;
            char buf[64];
            snprintf(buf, sizeof(buf), "%lld", val);
            result[i] = custom_strdup(buf);
        } else {
            result[i] = custom_strdup(token);
        }

        if (!result[i]) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            free(process_copy);
            *out_count = 0;
            return NULL;
        }

        i++;
        token = strtok(NULL, " \t\n");
    }
    result[count] = NULL;

    free(process_copy);
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