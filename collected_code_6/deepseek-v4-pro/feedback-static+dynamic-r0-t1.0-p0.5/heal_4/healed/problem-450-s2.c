#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_strings(char **input_list, int list_size, int extract_size, int *output_count) {
    if (input_list == NULL || list_size <= 0 || extract_size <= 0 || output_count == NULL) {
        if (output_count != NULL) {
            *output_count = 0;
        }
        return NULL;
    }

    char **result = NULL;
    int count = 0;

    for (int i = 0; i < list_size; i++) {
        if (input_list[i] == NULL) {
            continue;
        }

        size_t len = strnlen(input_list[i], (size_t)extract_size);
        size_t copy_len = (len < (size_t)extract_size) ? len : (size_t)extract_size;

        char **temp = (char **)realloc(result, (size_t)(count + 1) * sizeof(char *));
        if (temp == NULL) {
            for (int j = 0; j < count; j++) {
                free(result[j]);
            }
            free(result);
            *output_count = 0;
            return NULL;
        }
        result = temp;

        char *new_str = (char *)malloc(copy_len + 1);
        if (new_str == NULL) {
            for (int j = 0; j < count; j++) {
                free(result[j]);
            }
            free(result);
            *output_count = 0;
            return NULL;
        }

        if (copy_len > 0) {
            memcpy(new_str, input_list[i], copy_len);
        }
        new_str[copy_len] = '\0';

        if (strlen(input_list[i]) >= (size_t)extract_size) {
            result[count] = new_str;
            count++;
        } else {
            free(new_str);
        }
    }

    if (count == 0) {
        free(result);
        *output_count = 0;
        return NULL;
    }

    *output_count = count;
    return result;
}

int main(void) {
    char *strings[] = {"Python", "list", "exercise", "practice", "solution"};
    int list_size = sizeof(strings) / sizeof(strings[0]);
    int extract_size = 8;
    int output_count = 0;

    char **extracted = extract_strings(strings, list_size, extract_size, &output_count);

    if (extracted != NULL) {
        printf("[");
        for (int i = 0; i < output_count; i++) {
            printf("'%s'", extracted[i]);
            if (i < output_count - 1) {
                printf(", ");
            }
            free(extracted[i]);
        }
        printf("]\n");
        free(extracted);
    } else {
        printf("[]\n");
    }

    return 0;
}