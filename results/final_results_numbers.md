## 1. Outcomes and rounds-to-detection-free (FINAL)
deepseek-v4-pro        dfs0= 1665 (57.0%) repaired= 1067 not_df= 190 | median rounds (repaired)=1, 1-round repairs=802
qwen-max               dfs0= 1545 (52.9%) repaired= 1225 not_df= 152 | median rounds (repaired)=1, 1-round repairs=892
glm-5.1                dfs0= 1322 (45.2%) repaired= 1359 not_df= 241 | median rounds (repaired)=2, 1-round repairs=530
kimi-k3                dfs0= 2035 (69.6%) repaired=  802 not_df=  85 | median rounds (repaired)=1, 1-round repairs=628
openai-gpt56-sol       dfs0= 2235 (76.5%) repaired=  649 not_df=  38 | median rounds (repaired)=2, 1-round repairs=299
claude-fable-5         dfs0= 2276 (77.9%) repaired=  614 not_df=  32 | median rounds (repaired)=1, 1-round repairs=559
gemini-3-pro           dfs0= 2185 (74.8%) repaired=  701 not_df=  36 | median rounds (repaired)=1, 1-round repairs=606
TOTAL dfs0=13263 repaired=6417 not_df=774 (n=20454)
rounds-to-detection-free distribution (repaired samples, all models): r1=4316, r2=1182, r3=373, r4=196, r5=129, r6=84, r7=44, r8=42, r9=29, r10=22

## 2. Channel comparison (unique model x basename, anywhere in chain)
deepseek-v4-pro        oracle=  9 AFL=139 both= 0 fuzz-only=139 oracle-only= 9
qwen-max               oracle= 19 AFL=171 both=12 fuzz-only=159 oracle-only= 7
glm-5.1                oracle=  3 AFL= 37 both= 0 fuzz-only= 37 oracle-only= 3
kimi-k3                oracle=  1 AFL=101 both= 0 fuzz-only=101 oracle-only= 1
openai-gpt56-sol       oracle=  1 AFL= 18 both= 0 fuzz-only= 18 oracle-only= 1
claude-fable-5         oracle=  0 AFL= 59 both= 0 fuzz-only= 59 oracle-only= 0
gemini-3-pro           oracle=  1 AFL= 78 both= 0 fuzz-only= 78 oracle-only= 1
TOTAL oracle=34 AFL=603 overlap=12 (1.9% of 625 detected programs) fuzz-only=591 (94.6%) oracle-only=22 (3.5%)

## 3. Fuzzable share at round 0
deepseek-v4-pro        fuzzable=856/2922 (29.3%)
qwen-max               fuzzable=793/2922 (27.1%)
glm-5.1                fuzzable=1117/2922 (38.2%)
kimi-k3                fuzzable=1140/2922 (39.0%)
openai-gpt56-sol       fuzzable=1807/2922 (61.8%)
claude-fable-5         fuzzable=1026/2922 (35.1%)
gemini-3-pro           fuzzable=631/2922 (21.6%)

## 4. Detection classes at round 0 (fuzz channel, attributed + signal-only)
   1087  signed integer overflow
     57  float->int conversion
     47  negation overflow
     21  left shift
     17  division by zero / FPE
      5  other: UBSan: variable length array bound evalu
      4  ASan: stack-overflow
      2  ASan: heap-buffer-overflow
      2  other: UBSan: shift exponent 64 is too large fo
      1  other: UBSan: shift exponent 1228654364 is too 
      1  other: UBSan: shift exponent 1535817954 is too 
      1  other: UBSan: shift exponent 444 is too large f
      1  other: UBSan: index -6 out of bounds for type '
      1  other: UBSan: index -4 out of bounds for type '
      1  other: UBSan: index -8 out of bounds for type '

## 5. Sanitizer-oracle classes (anywhere in chain, for complementarity)
      5  ASan: stack-buffer-overflow
      4  UBSan: signed integer overflow: 1139355592 + 1199545584 cann
      3  UBSan: variable length array bound evaluates to non-positive
      3  UBSan: left shift of 1 by 31 places cannot be represented in
      2  ASan: global-buffer-overflow
      2  ASan: BUS
      2  UBSan: signed integer overflow: 9223372036854775807 - -2 can
      2  UBSan: inf is outside the range of representable values of t
      2  UBSan: signed integer overflow: 46341 * 46341 cannot be repr
      2  UBSan: signed integer overflow: 1073741824 + 1139355592 cann
      2  UBSan: 3.48679e+09 is outside the range of representable val
      2  UBSan: signed integer overflow: -1275550393 * 32540576076138