#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'ProgrammingLanguage', got <no output>
  *  test case 0 failed: expected 'PythonProgram', got <no output>
  *  test case 1 failed: expected 'PythonLanguage', got <no output>
  */

char* snake_to_camel(char *snake_case) {
    char *src = snake_case;
    char *dest = snake_case;

    while (*src) {
        if (*src == '_') {
            if (*(src + 1)) {
                *dest++ = toupper(*(src + 1));
                src++;
            } else {
                /* Possible weaknesses found:
                 *  *dest is assigned
                 */
                *dest = '\0';
                break;
            }
        } else {
            *dest++ = *src;
        }
        src++;
    }
    /* Possible weaknesses found:
     *  *dest is overwritten
     *  Variable '*dest' is reassigned a value before the old one has been used. [redundantAssignment]
     */
    *dest = '\0';
    return snake_case;
}

int main() {
    char snake_case[] = "this_is_a_snake_case_string";
    printf("Original: %s\n", snake_case);
    printf("CamelCase: %s\n", snake_to_camel(snake_case));
    return 0;
}