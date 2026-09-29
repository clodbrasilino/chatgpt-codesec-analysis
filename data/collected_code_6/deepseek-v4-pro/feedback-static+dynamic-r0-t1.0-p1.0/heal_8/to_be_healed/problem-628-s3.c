#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'I%20love%20Coding', got <no output>
  *  test case 1 failed: expected 'I%20am%20a%20Programmer', got <no output>
  *  test case 0 failed: expected 'My%20Name%20is%20Dawood', got <no output>
  */

char *replace_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = 0;
    size_t space_count = 0;
    
    while (str[len] != '\0') {
        if (str[len] == ' ') {
            space_count++;
        }
        len++;
        if (len > SIZE_MAX / 3) {
            return NULL;
        }
    }
    
    if (len > (SIZE_MAX - 1) / 3) {
        return NULL;
    }
    
    size_t new_len = len + (space_count * 2);
    
    if (new_len >= SIZE_MAX) {
        return NULL;
    }
    
    char *result = (char *)malloc(new_len + 1);
    
    if (result == NULL) {
        return NULL;
    }
    
    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ') {
            result[j++] = '%';
            result[j++] = '2';
            result[j++] = '0';
        } else {
            result[j++] = str[i];
        }
    }
    
    result[j] = '\0';
    return result;
}

int main(void) {
    const char *test_str1 = "My Name is Dawood";
    const char *test_str2 = "I am a Programmer";
    const char *test_str3 = "I love Coding";
    
    char *replaced1 = replace_spaces(test_str1);
    char *replaced2 = replace_spaces(test_str2);
    char *replaced3 = replace_spaces(test_str3);
    
    if (replaced1 != NULL) {
        printf("%s\n", replaced1);
        free(replaced1);
    }
    
    if (replaced2 != NULL) {
        printf("%s\n", replaced2);
        free(replaced2);
    }
    
    if (replaced3 != NULL) {
        printf("%s\n", replaced3);
        free(replaced3);
    }
    
    return 0;
}