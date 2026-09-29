#include <stdio.h>
#include <regex.h>

int isValidURL(char *url) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^((https?|ftp)://)?([a-z0-9]+([-.]{1}[a-z0-9]+)*\\.[a-z]{2,5}(:[0-9]{1,5})?(/.*)?)$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    reti = regexec(&regex, url, 0, NULL, 0);
    if (!reti) {
        return 1;
    } else if (reti == REG_NOMATCH) {
        return 0;
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 0;
    }

    regfree(&regex);
}

int main() {
    char url[100];
    printf("Enter a URL: ");
    scanf("%s", url);

    if (isValidURL(url)) {
        printf("URL is valid.\n");
    } else {
        printf("URL is not valid.\n");
    }

    return 0;
}