#include <stdio.h>
#include <string.h>
#include <pcre.h>

#define MAX_MATCHES 30

void find_adverbs(char *str) {
    pcre *re;
    const char *error;
    int erroffset;
    int ovector[MAX_MATCHES];
    int rc, i;

    re = pcre_compile("\\b\\w+ly\\b", 0, &error, &erroffset, NULL);
    if (re == NULL) {
        printf("PCRE compilation failed at offset %d: %s\n", erroffset, error);
        return;
    }

    rc = pcre_exec(re, NULL, str, strlen(str), 0, 0, ovector, MAX_MATCHES);
    if (rc < 0) {
        printf("Match failed\n");
        return;
    }

    for(i = 0; i < rc; i++) {
        printf("Matched adverb: %.*s at position %d\n", ovector[2*i+1] - ovector[2*i], str + ovector[2*i], ovector[2*i]);
    }

    pcre_free(re);
}

int main() {
    char str[] = "He quickly ran towards the slowly moving train.";
    find_adverbs(str);
    return 0;
}