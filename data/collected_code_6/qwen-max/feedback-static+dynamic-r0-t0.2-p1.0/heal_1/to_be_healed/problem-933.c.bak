#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'google_assistant', got G_o_o_g_l_e_Assistant
  *  test case 2 failed: expected 'quad_core', got Q_u_a_d_Core
  *  test case 1 failed: expected 'chrome_cast', got C_h_r_o_m_e_Cast
  */

char *camel_to_snake(const char *input) {
    regex_t regex;
    regmatch_t matches[2];
    char *output = malloc(strlen(input) * 2 + 1);
    int output_index = 0;

    if (regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED) != 0) {
        /* Possible weaknesses found:
         *  Memory leak: output [memleak]
         */
        return NULL;
    }

    for (int i = 0; i < strlen(input); ++i) {
        if (regexec(&regex, input + i, 2, matches, 0) == 0) {
            output[output_index++] = input[i];
            output[output_index++] = '_';
            i += matches[1].rm_eo - matches[1].rm_so - 1;
        } else {
            output[output_index++] = input[i];
        }
    }

    output[output_index] = '\0';
    regfree(&regex);
    return output;
}

int main() {
    const char *input = "ThisIsCamelCase";
    char *output = camel_to_snake(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Error converting string.\n");
    }

    return 0;
}