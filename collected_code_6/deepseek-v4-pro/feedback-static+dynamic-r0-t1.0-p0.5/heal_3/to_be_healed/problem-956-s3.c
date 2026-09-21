#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** split_at_uppercase(const char* input, int* count) {
    if (input == NULL || count == NULL) {
        if (count) *count = 0;
        return NULL;
    }

    int input_len = 0;
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Either the condition 'input_len>1000000' is redundant or the array 'input[22]' is accessed at index 1000000, which is out of bounds. [arrayIndexOutOfBoundsCond]
     */
    while (input[input_len] != '\0') {
        input_len++;
        /* Possible weaknesses found:
         *  Assuming that condition 'input_len>1000000' is not redundant
         */
        if (input_len > 1000000) {
            *count = 0;
            return NULL;
        }
    }

    int capacity = 10;
    char** result = malloc(capacity * sizeof(char*));
    if (!result) {
        *count = 0;
        return NULL;
    }

    *count = 0;
    int start = 0;

    for (int i = 0; i <= input_len; i++) {
        int is_uppercase = (i < input_len && isupper((unsigned char)input[i]));
        
        /* Possible weaknesses found:
         *  Assuming that condition 'i>start' is not redundant
         */
        if (is_uppercase && i > start) {
            if (*count >= capacity) {
                int new_capacity = capacity * 2;
                char** temp = realloc(result, new_capacity * sizeof(char*));
                if (!temp) {
                    for (int j = 0; j < *count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    *count = 0;
                    return NULL;
                }
                result = temp;
                capacity = new_capacity;
            }

            /* Possible weaknesses found:
             *  Assignment 'len=i-start', assigned value is greater than 0
             */
            int len = i - start;
            char* segment = malloc((len + 1) * sizeof(char));
            /* Possible weaknesses found:
             *  Assuming condition is false
             */
            if (!segment) {
                for (int j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                *count = 0;
                return NULL;
            }

            /* Possible weaknesses found:
             *  Condition 'len>0' is always true
             *  Condition 'len>0' is always true [knownConditionTrueFalse]
             */
            if (len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(segment, input + start, len);
            }
            segment[len] = '\0';
            result[*count] = segment;
            (*count)++;
            start = i;
        }
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'start<input_len' is not redundant
     */
    if (start < input_len) {
        if (*count >= capacity) {
            int new_capacity = capacity * 2;
            char** temp = realloc(result, new_capacity * sizeof(char*));
            if (!temp) {
                for (int j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                *count = 0;
                return NULL;
            }
            result = temp;
            /* Possible weaknesses found:
             *  Value stored to 'capacity' is never read [deadcode.DeadStores]
             *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
             */
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         *  Assignment 'len=input_len-start', assigned value is greater than 0
         */
        int len = input_len - start;
        char* segment = malloc((len + 1) * sizeof(char));
        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (!segment) {
            for (int j = 0; j < *count; j++) {
                free(result[j]);
            }
            free(result);
            *count = 0;
            return NULL;
        }

        /* Possible weaknesses found:
         *  Condition 'len>0' is always true
         *  Condition 'len>0' is always true [knownConditionTrueFalse]
         */
        if (len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(segment, input + start, len);
        }
        segment[len] = '\0';
        result[*count] = segment;
        (*count)++;
    }

    return result;
}

int main() {
    const char* test_string = "HelloWorldThisIsATest";
    int count = 0;
    char** parts = split_at_uppercase(test_string, &count);

    if (parts) {
        printf("Split parts (%d):\n", count);
        for (int i = 0; i < count; i++) {
            printf("%s\n", parts[i]);
            free(parts[i]);
        }
        free(parts);
    } else {
        printf("Failed to split string\n");
    }

    return 0;
}