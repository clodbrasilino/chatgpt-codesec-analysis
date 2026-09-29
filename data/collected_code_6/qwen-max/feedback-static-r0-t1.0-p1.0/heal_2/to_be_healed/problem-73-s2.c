#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int split_string(const char *input, const char *delimiters, char ***result) {
    regex_t regex;
    regmatch_t match[1];
    size_t nmatch = 1;
    char *str;
    char **parts = NULL;
    int count = 0, part_idx = 0;

    if (regcomp(&regex, delimiters, REG_EXTENDED | REG_NEWLINE) != 0) {
        return -1;
    }

    str = strdup(input);
    if (str == NULL) {
        regfree(&regex);
        return -1;
    }

    while (1) {
        int status = regexec(&regex, str, nmatch, match, 0);
        if (status != 0) break;

        /* Possible weaknesses found:
         *  Common realloc mistake: 'parts' nulled but not freed upon failure [memleakOnRealloc]
         */
        parts = realloc(parts, (count + 2) * sizeof(char*));
        /* Possible weaknesses found:
         *  Assuming that condition 'parts==NULL' is not redundant
         */
        if (parts == NULL) {
            free(str);
            regfree(&regex);
            /* Possible weaknesses found:
             *  Condition 'parts!=NULL' is always false
             *  Condition 'parts!=NULL' is always false [knownConditionTrueFalse]
             */
            if (parts != NULL) free(parts);
            return -1;
        }
        
        if (match[0].rm_so > 0) {
            parts[part_idx] = strndup(str, match[0].rm_so);
            part_idx++;
            count++;
        }

        str += match[0].rm_eo;
    }

    if (*str != '\0') {
        /* Possible weaknesses found:
         *  Common realloc mistake: 'parts' nulled but not freed upon failure [memleakOnRealloc]
         */
        parts = realloc(parts, (count + 1) * sizeof(char*));
        /* Possible weaknesses found:
         *  Assuming that condition 'parts==NULL' is not redundant
         */
        if (parts == NULL) {
            free(str);
            regfree(&regex);
            /* Possible weaknesses found:
             *  Condition 'parts!=NULL' is always false
             *  Condition 'parts!=NULL' is always false [knownConditionTrueFalse]
             */
            if (parts != NULL) free(parts);
            return -1;
        }
        
        parts[part_idx] = strdup(str);
        /* Possible weaknesses found:
         *  Variable 'part_idx' is assigned a value that is never used. [unreadVariable]
         */
        part_idx++;
        count++;
    }

    /* Possible weaknesses found:
     *  Common realloc mistake: 'parts' nulled but not freed upon failure [memleakOnRealloc]
     */
    parts = realloc(parts, (count + 1) * sizeof(char*));
    /* Possible weaknesses found:
     *  Assuming that condition 'parts==NULL' is not redundant
     */
    if (parts == NULL) {
        free(str);
        regfree(&regex);
        /* Possible weaknesses found:
         *  Condition 'parts!=NULL' is always false
         *  Condition 'parts!=NULL' is always false [knownConditionTrueFalse]
         */
        if (parts != NULL) free(parts);
        return -1;
    }
    
    parts[count] = NULL;
    *result = parts;

    free(str);
    regfree(&regex);
    return count;
}

int main() {
    const char *input = "This,is a test;split string:with multiple,delimiters";
    const char *delimiters = ",|;|:|\\s+";
    char **result = NULL;
    int count = split_string(input, delimiters, &result);

    if (count >= 0) {
        for (int i = 0; result[i] != NULL; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    } else {
        fprintf(stderr, "Split failed\n");
    }

    return 0;
}