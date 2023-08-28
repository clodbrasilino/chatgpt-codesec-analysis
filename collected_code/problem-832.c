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
    status = regexec(&regex, str, 1, &match, 0);
    if (status == 0) {
        // Extract the matched numeric value
        char numeric_value[match.rm_eo - match.rm_so + 1];
        snprintf(numeric_value, match.rm_eo - match.rm_so + 1, "%.*s", match.rm_eo - match.rm_so, str + match.rm_so);

        // Convert the numeric value to integer
        int max_value = atoi(numeric_value);

        // Loop through the string to find the maximum numeric value
        while (regexec(&regex, str + match.rm_eo, 1, &match, 0) == 0) {
            snprintf(numeric_value, match.rm_eo - match.rm_so + 1, "%.*s", match.rm_eo - match.rm_so, str + match.rm_so);
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