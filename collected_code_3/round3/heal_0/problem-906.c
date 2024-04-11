#include <stdio.h>
#include <string.h>
#include <regex.h>

void extract_date(char *url, char *year, char *month, char *day) {
    regex_t regex;
    regmatch_t matches[4];
    regcomp(&regex, "([0-9]{4})-([0-9]{2})-([0-9]{2})", REG_EXTENDED);

    if (regexec(&regex, url, 4, matches, 0) == 0) {
        int start = matches[1].rm_so;
        int end = matches[1].rm_eo;
        strncpy(year, url + start, end - start);

        start = matches[2].rm_so;
        end = matches[2].rm_eo;
        strncpy(month, url + start, end - start);

        start = matches[3].rm_so;
        end = matches[3].rm_eo;
        strncpy(day, url + start, end - start);
    }

    regfree(&regex);
}

int main() {
    char url[] = "https://www.example.com/2022/04/01/article.html";
    char year[5], month[3], day[3];

    extract_date(url, year, month, day);

    printf("Year: %s\n", year);
    printf("Month: %s\n", month);
    printf("Day: %s\n", day);

    return 0;
}