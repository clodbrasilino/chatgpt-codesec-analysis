#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** split_at_lowercase(const char* input, int* count) {
    if (!input || !count) return NULL;

    int length = 0;
    int num_parts = 0;
    
    while (input[length] != '\0') {
        if (islower((unsigned char)input[length])) {
            num_parts++;
        }
        length++;
    }
    
    char** result = (char**)malloc((num_parts + 2) * sizeof(char*));
    if (!result) return NULL;

    int part_index = 0;
    int start = 0;

    for (int i = 0; i < length; i++) {
        if (islower((unsigned char)input[i])) {
            int part_len = i - start;
            if (part_len < 0) part_len = 0; 

            result[part_index] = (char*)malloc((part_len + 1) * sizeof(char));
            if (!result[part_index]) {
                for (int j = 0; j < part_index; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            
            for (int k = 0; k < part_len; k++) {
                result[part_index][k] = input[start + k];
            }
            result[part_index][part_len] = '\0';
            part_index++;
            start = i + 1;
        }
    }

    int part_len = length - start;
    if (part_len < 0) part_len = 0;

    result[part_index] = (char*)malloc((part_len + 1) * sizeof(char));
    if (!result[part_index]) {
        for (int j = 0; j < part_index; j++) {
            free(result[j]);
        }
        free(result);
        return NULL;
    }
    
    for (int k = 0; k < part_len; k++) {
        result[part_index][k] = input[start + k];
    }
    result[part_index][part_len] = '\0';
    part_index++;
    
    result[part_index] = NULL;
    *count = part_index;

    return result;
}

int main(void) {
    const char* test_str = "HELLOwWORLDtTESTiYES";
    int count = 0;
    
    char** parts = split_at_lowercase(test_str, &count);
    
    if (parts) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", parts[i]);
            free(parts[i]);
        }
        free(parts);
    }
    
    return 0;
}