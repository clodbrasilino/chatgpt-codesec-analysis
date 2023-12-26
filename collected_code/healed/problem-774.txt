#include <stddef.h>
#include <regex.h>

int isValidEmail(const char *email) {
    const char *pattern = "^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+$";
    regex_t regex;
    int reti = regcomp(&regex, pattern, 0);

    if (reti) {
        return 0;
    }

    regmatch_t matchptr[1];
    reti = regexec(&regex, email, 0, matchptr, 0);
    regfree(&regex);

    if (!reti) {
        return 1;
    } else if (reti == REG_NOMATCH) {
        return 0;
    } else {
        return 0;
    }
}

int main() {
    const char* email = "test@example.com";
    int valid = isValidEmail(email);

    return 0;
}