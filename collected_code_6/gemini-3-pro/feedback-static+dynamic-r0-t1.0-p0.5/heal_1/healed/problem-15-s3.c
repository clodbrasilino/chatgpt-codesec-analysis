#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** split_at_lowercase(const char* str, int* count) {
    if (!str || !count) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    size_t max_splits = len + 1;
    char** result = (char**)malloc(max_splits * sizeof(char*));
    if (!result) {
        return NULL;
    }

    int split_count = 0;
    size_t start = 0;

    for (size_t i = 0; i <= len; i++) {
        if (str[i] == '\0' || islower((unsigned char)str[i])) {
            size_t sub_len = i - start;
            if (sub_len > 0) {
                result[split_count] = (char*)malloc((sub_len + 1) * sizeof(char));
                if (!result[split_count]) {
                    for (int j = 0; j < split_count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                
                memcpy(result[split_count], str + start, sub_len);
                result[split_count][sub_len] = '\0';
                split_count++;
            }
            start = i + 1;
        }
    }

    *count = split_count;
    return result;
}

void free_splits(char** splits, int count) {
    if (!splits) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(splits[i]);
    }
    free(splits);
}

int main(void) {
    const char* test_str = "HELLOwORLDtESTING";
    int count = 0;

    char** splits = split_at_lowercase(test_str, &count);

    if (splits) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", splits[i]);
        }
        free_splits(splits, count);
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return 1;
    }

    return 0;
}