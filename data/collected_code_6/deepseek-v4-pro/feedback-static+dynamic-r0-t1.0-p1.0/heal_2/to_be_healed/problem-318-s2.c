#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>

int64_t maxVolume(int64_t S) {
    int64_t a = S / 3;
    int64_t b = (S - a) / 2;
    int64_t c = S - a - b;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 4099276460824344804 * 3074457345618258603 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:245,execs:142,op:havoc,rep:4)
     * UBSan: signed integer overflow: 3074457345618258602 * 3074457345618258602 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:245,execs:142,op:havoc,rep:4)
     * UBSan: signed integer overflow: 897779121776406 * 29962963 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:275,execs:155,op:havoc,rep:4)
     */
    return a * b * c;
}

int main(void) {
    int64_t sumSides;
    printf("Enter sum of sides: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64, &sumSides) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (sumSides < 3) {
        fprintf(stderr, "Sum must be at least 3\n");
        return 1;
    }
    int64_t volume = maxVolume(sumSides);
    printf("Maximum volume: %" PRId64 "\n", volume);
    return 0;
}