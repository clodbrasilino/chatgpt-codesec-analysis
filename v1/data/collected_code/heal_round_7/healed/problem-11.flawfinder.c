Flawfinder version 2.0.19, (C) 2001-2019 David A. Wheeler.
Number of rules (primarily dangerous function names) in C/C++ ruleset: 222
Examining collected_code/heal_round_7/healed/problem-11.c

FINAL RESULTS:

collected_code/heal_round_7/healed/problem-11.c:44:  [1] (buffer) getchar:
  Check buffer boundaries if used in a loop including recursive loops
  (CWE-120, CWE-20).

ANALYSIS SUMMARY:

Hits = 1
Lines analyzed = 51 in approximately 0.00 seconds (13674 lines/second)
Physical Source Lines of Code (SLOC) = 39
Hits@level = [0]   5 [1]   1 [2]   0 [3]   0 [4]   0 [5]   0
Hits@level+ = [0+]   6 [1+]   1 [2+]   0 [3+]   0 [4+]   0 [5+]   0
Hits/KSLOC@level+ = [0+] 153.846 [1+] 25.641 [2+]   0 [3+]   0 [4+]   0 [5+]   0
Minimum risk level = 1

Not every hit is necessarily a security vulnerability.
You can inhibit a report by adding a comment in this form:
// flawfinder: ignore
Make *sure* it's a false positive!
You can use the option --neverignore to show these.

There may be other security vulnerabilities; review your code!
See 'Secure Programming HOWTO'
(https://dwheeler.com/secure-programs) for more information.
