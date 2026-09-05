#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* increment_string(const char* str, int k) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;

    while (i < len) {
        if (isdigit((unsigned char)str[i])) {
            long num = 0;
            /* Possible weaknesses found:
             *  Value stored to 'start' during its initialization is never read [deadcode.DeadStores]
             *  Variable 'start' is assigned a value that is never used. [unreadVariable]
             */
            size_t start = i;

            while (i < len && isdigit((unsigned char)str[i])) {
                num = num * 10 + (str[i] - '0');
                i++;
            }

            num += k;

            int written = snprintf(NULL, 0, "%ld", num);
            if (written <= 0) {
                free(result);
                return NULL;
            }

            char* temp = (char*)malloc(written + 1);
            if (temp == NULL) {
                free(result);
                return NULL;
            }

            snprintf(temp, written + 1, "%ld", num);

            char* new_result = (char*)realloc(result, j + written + 1);
            if (new_result == NULL) {
                free(temp);
                free(result);
                return NULL;
            }

            result = new_result;
            memcpy(result + j, temp, written);
            j += written;
            free(temp);
        } else {
            char* new_result = (char*)realloc(result, j + 2);
            if (new_result == NULL) {
                free(result);
                return NULL;
            }

            result = new_result;
            result[j++] = str[i++];
        }
    }

    result[j] = '\0';
    return result;
}

int main(void) {
    char* s1 = increment_string("abc123def45", 5);
    if (s1 != NULL) {
        printf("%s\n", s1);
        free(s1);
    }

    char* s2 = increment_string("no numbers here", 10);
    if (s2 != NULL) {
        printf("%s\n", s2);
        free(s2);
    }

    char* s3 = increment_string("99 bottles", 1);
    if (s3 != NULL) {
        printf("%s\n", s3);
        free(s3);
    }

    /* Possible weaknesses found:
     *  Variable 's4' can be declared as pointer to const [constVariablePointer]
     *  Assignment 's4=increment_string(NULL,5)', assigned value is 0
     *  Calling function 'increment_string' returns 0
     */
    char* s4 = increment_string(NULL, 5);
    /* Possible weaknesses found:
     *  Condition 's4==NULL' is always true [knownConditionTrueFalse]
     *  Condition 's4==NULL' is always true
     */
    if (s4 == NULL) {
        printf("NULL input handled\n");
    }

    return 0;
}