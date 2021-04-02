# City Glide

In the city of Medan, there are $N$ buildings numbered from $0$ to $N - 1$ from left to right. All buildings has **distinct heights**, with building $i$ having the height $H[i]$.

Pak Dengklek is a paraglider who can glide from building to building. In a single glide, Pak Dengklek can glide from the top of a building and land at the top of the closest building, either to the left or to the right, which height is lower than the building he is currently at. Formally, if Pak Dengklek is currently at building $x$, then he can glide to building $y$ if and only if any of these is satisfied:

- $y$ is the largest non-negative integer less than $x$ such that $H[y] < H[x]$; or
- $y$ is the smallest non-negative integer larger than $x$ such that $H[y] < H[x]$.

Pak Dengklek has $Q$ paragliding plans, each can be represented as four integers $A$, $B$, $C$, and $D$ ($A \le B$ and $C \le D$). For each plan, Pak Dengklek would like to know whether it is possible to start from some building $s$ ($A \le s \le B$) and end at any building $e$ ($C \le e \le D$). If it is possible, Pak Dengklek would like to know the minimum number of glides he needs for that plan.

## Implementation Details

You should implement the following procedure.

```
void init(int N, int Q, int[] H)
```

* $N$: the number of buildings.
* $Q$: the number of plans that Pak Dengklek has.
* $H$: an array of length $N$. For each $i$ ($0 \le i \le N - 1$), building $i$ has height $H[i]$.
* This procedure is called exactly once, before any calls to `minimum_jumps`.

```
int minimum_glides(int A, int B, int C, int D)
```

* $A$, $B$: the range of buildings that Pak Dengklek can start from.
* $C$, $D$: the range of buildings that Pak Dengklek must end with.
* This procedure should return the minimum number of glides to carry out the plan, or $-1$ if it is impossible to do so.
* This procedure is called exactly $Q$ times.

## Example

Consider the following call:

```
init(7, 3, [1, 3, 4, 2, 7, 6, 5])
```

There are $7$ buildings, and Pak Dengklek will ask you about $3$ plans.

After initialization has been done, consider the following call:

```
minimum_glides(2, 2, 0, 0)
```

This means Pak Dengklek plans to start at building $2$ and end at building $0$. One way to achieve the minimum number of glides is to first glide to building $4$, then glide to building $1$. Another way is to glide to building $1$, then glide to building $0$. Therefore, the procedure `minimum_glides` should return $2$.

Consider another possible call:

```
minimum_glides(3, 5, 0, 1)
```

This means Pak Dengklek plans to start at either building $3$, $4$, $5$ and end at either building $0$ or $1$. The only way to achieve the minimum number of glides is to start at building $3$, then glide to building $0$ using only one glide. Therefore, the procedure `minimum_glides` should return $1$.

Consider another possible call:

```
minimum_glides(0, 3, 4, 4)
```

This means Pak Dengklek plans to start at any building from $0$ to $3$ and end at building $4$. Since building $4$ is the tallest building, it is impossible to be reached from any building lower than it. Therefore, the procedure `minimum_glides` should return $-1$.

## Constraints

* $2 \le N \le 100\,000$.
* $1 \le H[i] \le N$ (for all $0 \le i \le N - 1$).
* $All the values of $H$ is distinct$.
* $0 \le A \le B \le N - 1$.
* $0 \le C \le D \le N - 1$.
* $B < C$ or $D < A$ (the start range and end range of each plan do not intersect).

## Subtasks

1. (? points) $H[i] < H[i + 1]$ (for all $0 \le i \le N - 2$).
1. (? points) $N \le 100$, $Q \le 100$.
1. (? points) $N \le 2000$, $Q \le 2000$.
1. (? points) $Q = 1$.
1. (? points) $A = B$, $C = D$.
1. (? points) $A = B$.
1. (? points) No additional constraints.

## Sample Grader

The sample grader reads the input in the following format:

* line $1$: $N \; Q$
* line $2$: $H[0] \; H[1] \; \ldots \; H[N - 1]$
* line $3 + i$ ($0 \le i \le Q - 1$): $A \; B \; C \; D$ for the $i$-th call of `minimum_glides`

The sample grader prints your answers in the following format:

* line $1 + i$ ($0 \le i \le Q - 1$): return value of the $i$-th call to `minimum_glides`
