#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

static ll *dp;
static ll *dp_new;
static int *values;
static int num_values;
static ll min_val, max_val;

ll count_sequences(int length) {
    if (length <= 0) return 0;
    if (num_values == 0) return 0;
    
    min_val = values[0];
    max_val = values[0];
    for (int i = 1; i < num_values; i++) {
        if (values[i] < min_val) min_val = values[i];
        if (values[i] > max_val) max_val = values[i];
    }
    
    /* Possible weaknesses found:
     *  Assuming condition 'min_val>=0' is false
     */
    if (min_val >= 0) {
        ll result = 1;
        for (int i = 0; i < length; i++) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 4611686018427387904 * 4 cannot be represented in type 'll' (aka 'long long') (AFL crash: id:000000,sig:06,src:000008,time:12456,execs:5248,op:havoc,rep:3)
             */
            result *= num_values;
        }
        return result;
    }
    
    ll max_reach = 0;
    ll min_reach = 0;
    for (int i = 0; i < length; i++) {
        if (max_val > 0) max_reach += max_val;
        /* Possible weaknesses found:
         *  Condition 'min_val<0' is always true [knownConditionTrueFalse]
         *  Condition 'min_val<0' is always true
         */
        if (min_val < 0) min_reach += min_val;
    }
    
    ll offset = -min_reach;
    ll size = max_reach - min_reach + 1;
    
    if (size <= 0 || size > 100000000) return -1;
    
    dp = (ll *)calloc((size_t)size, sizeof(ll));
    dp_new = (ll *)calloc((size_t)size, sizeof(ll));
    if (dp == NULL || dp_new == NULL) {
        free(dp);
        free(dp_new);
        dp = NULL;
        dp_new = NULL;
        return -1;
    }
    
    dp[offset] = 1;
    
    for (int pos = 0; pos < length; pos++) {
        memset(dp_new, 0, (size_t)size * sizeof(ll));
        
        for (ll sum = 0; sum <= max_reach; sum++) {
            ll idx = sum + offset;
            if (idx < 0 || idx >= size) continue;
            if (dp[idx] == 0) continue;
            
            for (int v = 0; v < num_values; v++) {
                ll new_sum = sum + values[v];
                if (new_sum < 0) continue;
                if (new_sum > max_reach) continue;
                
                ll new_idx = new_sum + offset;
                if (new_idx >= 0 && new_idx < size) {
                    /* Possible weaknesses found:
                     * UBSan: signed integer overflow: 6063861390644594843 + 3975250549198072254 cannot be represented in type 'll' (aka 'long long') (AFL crash: id:000001,sig:06,src:000008,time:12882,execs:5356,op:havoc,rep:2)
                     * UBSan: signed integer overflow: 7057808179262681224 + 2946127768511332654 cannot be represented in type 'll' (aka 'long long') (AFL crash: id:000004,sig:06,src:000009,time:36971,execs:11531,op:havoc,rep:24)
                     */
                    dp_new[new_idx] += dp[idx];
                }
            }
        }
        
        ll *temp = dp;
        dp = dp_new;
        dp_new = temp;
    }
    
    ll total = 0;
    for (ll sum = 0; sum <= max_reach; sum++) {
        ll idx = sum + offset;
        if (idx >= 0 && idx < size) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 2683948844843011196 + 7624788253942790228 cannot be represented in type 'll' (aka 'long long') (AFL crash: id:000001,sig:06,src:000008,time:12882,execs:5356,op:havoc,rep:2)
             * UBSan: signed integer overflow: 5620373852622583763 + 3683590725552388792 cannot be represented in type 'll' (aka 'long long') (AFL crash: id:000003,sig:06,src:000009,time:30066,execs:10212,op:havoc,rep:2)
             * UBSan: signed integer overflow: 8771868364471143639 + 1288093645305579246 cannot be represented in type 'll' (aka 'long long') (AFL crash: id:000004,sig:06,src:000009,time:36971,execs:11531,op:havoc,rep:24)
             */
            total += dp[idx];
        }
    }
    
    free(dp);
    free(dp_new);
    dp = NULL;
    dp_new = NULL;
    
    return total;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000002,sig:06,src:000009,time:15122,execs:6133,op:havoc,rep:12; likely memory-safety defect
  */

int main(void) {
    int length;
    int n;
    
    if (scanf("%d", &length) != 1) return 1;
    if (scanf("%d", &n) != 1) return 1;
    
    if (n <= 0 || length <= 0) {
        printf("0\n");
        return 0;
    }
    
    values = (int *)malloc((size_t)n * sizeof(int));
    if (values == NULL) return 1;
    num_values = n;
    
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &values[i]) != 1) {
            free(values);
            values = NULL;
            return 1;
        }
    }
    
    ll result = count_sequences(length);
    printf("%lld\n", result);
    
    free(values);
    values = NULL;
    
    return 0;
}