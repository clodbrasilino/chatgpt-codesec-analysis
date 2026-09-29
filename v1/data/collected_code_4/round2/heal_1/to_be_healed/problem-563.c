#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

char* extract_quoted_string(const char* input_string) {
    if(input_string == NULL) {
        return NULL;
    }

    int len = strlen(input_string);
    char *output_string = malloc(BUFFER_SIZE);
    char *output_ptr = output_string;
    int inside_quote = 0;

    for (int i = 0; i < len; ++i) {
        if (input_string[i] == '\"') {
            inside_quote = !inside_quote;
            if (inside_quote == 0) {
                /* Possible weaknesses found:
                 *  dereference of possibly-NULL 'output_ptr' [CWE-690] [-Wanalyzer-possible-null-dereference]
                 */
                *output_ptr++ = ',';
            }
        } else if(inside_quote){
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'output_ptr' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            *output_ptr++ = input_string[i];
        }
    }

    if (output_ptr != output_string && *(output_ptr-1) == ',') output_ptr--;
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'output_ptr' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    *output_ptr = '\0';

    return output_string;
}

int main(void) {
    char* test_string = "This is a \"test\" and we are \"trying\" to extract the string between \"quotes\"!";
    char* extracted = extract_quoted_string(test_string);
    printf("Extracted strings are: %s\n", extracted);
    free(extracted);
    return 0;
}