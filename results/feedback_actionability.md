# Feedback actionability: do the channels differ in how usable their feedback is?

## The construct, stated precisely

User hypothesis (refined): *one channel's findings may be easier for the
model to understand and act on, so the repair loop converts that
channel's feedback into a passing repair faster.* Operationally we
measure **feedback actionability** as:

1. **Per-round fix rate (hazard)**: among programs still flagged at
   round r-1, the share that reach a pass at round r -- computed within
   each single-channel arm, where the injected feedback is pure.
2. **Rounds-to-fix** among repaired programs.
3. **What each channel flags**: volume and persistence of the flagged
   population on identical round-0 code.

Instrument: the single-channel arms. The dynamic-only cells import the
round-0 code of the static-only cells (gen_source), so both arms
repair the SAME 4,200 programs (7 models x 600) with pure feedback.
Caveat that travels with every number: each arm's "pass" is its own
gate's criterion (static-clean vs dynamic-clean), and actionability is
entangled with the defect classes each channel finds.

## 1. Per-finding actionability is COMPARABLE

Pooled per-round fix rate (7 models, flagged programs, 5-round
horizon):

| Arm | r1 | r2 | r3 | r4 | r5 |
|---|---|---|---|---|---|
| static-only | 1,041/2,362 = **44.1%** | 23.2% | 9.7% | 7.2% | 5.9% |
| dynamic-only | 126/301 = **41.9%** | 8.0% | 5.6% | 5.9% | 1.4% |

Round-1 fix rates are statistically indistinguishable in magnitude
(44.1% vs 41.9%); median rounds-to-fix is 1.0 in both arms (mean 1.58
vs 1.42). **The model uses either channel's feedback about equally
well per finding.** The simple version of the hypothesis -- "one
channel's feedback is better understood" -- is not supported.

## 2. The channels differ in WHAT they flag, not in usability

Round-0 flag cross-tab on identical code (4,200 programs, 7 models):

| | dynamically flagged | dynamically clean |
|---|---:|---:|
| **statically flagged** | 227 (5.4%) | **2,135 (50.8%)** |
| **statically clean** | 74 (1.8%) | 1,764 (42.0%) |

- Static feedback flags **7.8x more programs** (2,362 vs 301) and its
  hazard decays slowly (44 -> 23 -> 10 -> 7 -> 6%): a long tail of
  persistent static findings that the loop never fully clears.
- **50.8% of all programs are statically flagged but dynamically
  clean at generation.** Under dynamic-only feedback these pass
  immediately; under static-only feedback they consume rounds, and
  only 72.1% (1,540/2,135) are cleared within the horizon.

## 3. So the pass-rate gap is a SELECTION effect, not an actionability effect

The dynamic-only arm's 95-99% pass (gate-usage ablation, comparison A)
is driven by its criterion rarely being triggered (only 7.2% of
programs dynamically flagged) plus quick fixes of the few flagged
ones -- not by better-understood feedback. On the 227 programs flagged
by BOTH channels, the static-only loop reaches its own criterion more
often than the dynamic-only loop reaches its (69.6% vs 55.5%) --
though these remain different criteria (static-clean vs dynamic-clean)
and the findings differ, so this comparison is suggestive, not
controlled.

## 4. Connection to the false-positive tension

The persistent static tail is the repair-loop manifestation of the
static-vs-dynamic detection asymmetry (RQ2 execution denominator):
static findings -- largely quality/lexical per the gate-configuration
disclosure -- keep the loop running without terminating, while the
dynamic channel's rare findings are mostly one-shot fixable. "Which
channel's feedback the LLM understands better" is the wrong question;
the data says the channels differ in **what and how much they flag**,
and the static channel's criterion is the one the loop struggles to
satisfy.

## What the cross-evaluation adds (in progress)

The common-criterion question -- "does static-clean imply
dynamic-clean, and vice versa?" -- requires evaluating the missing
channel on each arm's final code:
- static analyzers on the dynamic-only arm's final versions (cheap);
- tests + sanitizer oracle on the static-only arm's final versions
  (the 1,540 static-passed programs are the critical set: if many are
  dynamically dirty, the static gate's termination gives false
  closure).
Fuzzing scope for the latter is a separate decision (AFL++ on ~4,200
finals is hours of compute; tests+oracle is the fast core).


## Plain-language summary: are the detections on the same problems?

No. On identical round-0 code (4,200 programs, 7 models), the channels
flag largely different subsets:

| per 100 programs | |
|---|---|
| 42 | neither channel flags -- both loops terminate immediately |
| 51 | ONLY static flags -- dynamic loop passes instantly; static loop burns rounds, clears 72% in 5 rounds |
| 2 | only dynamic flags |
| 5 | both flag |

Static flagged 2,362 programs, dynamic 301; overlap 227 (9.6% of
static's set). Asymmetry: ~75% of dynamically-flagged programs are
also statically flagged, but only ~10% of statically-flagged programs
are dynamically flagged -- static findings are largely invisible to
the dynamic channel (quality/lexical issues, not behavioral failures).

Consequences:
1. Dynamic-only's high pass rate (95-99%) reflects a gate that rarely
   triggers (7% of programs) plus quick fixes -- not better feedback.
2. Static-only's lower pass rate (70-84%) reflects a gate that
   triggers on half the programs and keeps re-triggering (slow hazard
   decay: 44/23/10/7/6%) -- a persistent tail of findings the models
   do not fully clear.
3. Per-finding actionability is equal (round-1 fix rate 44% vs 42%,
   median 1 round both arms). The right question is not "which
   feedback does the LLM understand better" but "which criterion is
   satisfiable": static casts a wide net with an uncleared residue;
   dynamic casts a narrow net with quickly-fixed catches.
