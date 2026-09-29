#include <stdio.h>
#include <regex.h>

char* convertDateFormat(char *inputDate) {
    regex_t reg;
    regmatch_t match[4]; 
    static char outputDate[11]; 

    if (regcomp(&reg, "^([0-9]{4})-([0-9]{2})-([0-9]{2})$", REG_EXTENDED)) 
        return NULL;

    if (regexec(&reg, inputDate, 4, match, 0)) {
        regfree(&reg);
        return NULL;
    }

    snprintf(outputDate, sizeof(outputDate), "%.*s-%.*s-%.*s",
             (int)(match[3].rm_eo - match[3].rm_so), &inputDate[match[3].rm_so],
             (int)(match[2].rm_eo - match[2].rm_so), &inputDate[match[2].rm_so],
             (int)(match[1].rm_eo - match[1].rm_so), &inputDate[match[1].rm_so]
    );

    regfree(&reg);
    
    return outputDate;
}

int main() {
    char date[11] = "2022-12-31";
    char *convertedDate = convertDateFormat(date);

    if(convertedDate)
        printf("%s\n", convertedDate);
    else
        printf("Invalid date format\n");

    return 0;
}