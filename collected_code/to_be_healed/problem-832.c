#include <stdio.h>
#include <regex.h>

int extract_max_numeric_value(char* str) {
    regex_t regex;
    regmatch_t match;
    int status;

    // Compile the regular expression pattern
    status = regcomp(&regex, "[0-9]+", REG_EXTENDED);
    if (status != 0) {
        fprintf(stderr, "Error compiling regex pattern\n");
        return -1;
    }

    // Find the first match in the string
    /* Possible weaknesses found:
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    status = regexec(&regex, str, 1, &match, 0);
    if (status == 0) {
        // Extract the matched numeric value
        /* Possible weaknesses found:
         *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
         */
        char numeric_value[match.rm_eo - match.rm_so + 1];
        /* Possible weaknesses found:
         *  Cannot determine that 'numeric_value[0]' is initialized [premium-bughuntingUninit]
         */
        snprintf(numeric_value, match.rm_eo - match.rm_so + 1, "%.*s", match.rm_eo - match.rm_so, str + match.rm_so);

        // Convert the numeric value to integer
        /* Possible weaknesses found:
         *   Unless checked, the resulting number can exceed the expected range  (CWE-190). If source untrusted, check both minimum and maximum, even if the  input had no minus sign (large numbers can roll over into negative number;  consider saving to an unsigned value if that is intended).
         *  implicit declaration of function 'atoi' [-Wimplicit-function-declaration]
         */
        int max_value = atoi(numeric_value);

        // Loop through the string to find the maximum numeric value
        while (regexec(&regex, str + match.rm_eo, 1, &match, 0) == 0) {
            snprintf(numeric_value, match.rm_eo - match.rm_so + 1, "%.*s", match.rm_eo - match.rm_so, str + match.rm_so);
            /* Possible weaknesses found:
             *   Unless checked, the resulting number can exceed the expected range  (CWE-190). If source untrusted, check both minimum and maximum, even if the  input had no minus sign (large numbers can roll over into negative number;  consider saving to an unsigned value if that is intended).
             */
            int current_value = atoi(numeric_value);
            if (current_value > max_value) {
                max_value = current_value;
            }
        }

        // Free the regex memory
        regfree(&regex);

        return max_value;
    } else {
        fprintf(stderr, "No numeric value found in the string\n");
        regfree(&regex);
        return -1;
    }
}

int main() {
    char str[] = "The maximum numeric value is 1000 and the minimum is 10.";
    int max_value = extract_max_numeric_value(str);
    printf("Maximum numeric value: %d\n", max_value);
    return 0;
}