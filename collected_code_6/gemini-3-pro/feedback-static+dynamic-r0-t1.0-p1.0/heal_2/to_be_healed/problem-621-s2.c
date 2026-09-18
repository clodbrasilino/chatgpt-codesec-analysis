#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['Flutter', '484', 'is', '77', '129', 'Magnificent', '45'], got ["��"]
  *  test case 0 failed: expected ['MSM', '240', 'is', '104', '129', 'best', '10'], got null
  *  test case 1 failed: expected ['Dart', '368', 'is', '100', '181', 'Super', '18'], got null
  */

char** increment_numeric_values(const char* input, int k, int* out_count) {
    if (!input || !out_count) return NULL;

    char** result = NULL;
    int count = 0;
    
    char* copy = strdup(input);
    if (!copy) return NULL;

    char* token = strtok(copy, " \t\n");
    while (token) {
        /* Possible weaknesses found:
         *  Common realloc mistake: 'result' nulled but not freed upon failure [memleakOnRealloc]
         */
        result = realloc(result, sizeof(char*) * (count + 1));
        
        int is_num = 1;
        for (int i = 0; token[i]; i++) {
            if (!isdigit((unsigned char)token[i]) && !(i == 0 && (token[i] == '-' || token[i] == '+'))) {
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
        
        count++;
        token = strtok(NULL, " \t\n");
    }
    
    free(copy);
    *out_count = count;
    return result;
}

int main(void) {
    return 0;
}