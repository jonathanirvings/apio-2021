# Rainforest Jumps

In the tropical rainforest of Sumatra, there are $N$ trees numbered from $0$ to $N - 1$ from left to right.
All trees has **distinct heights**, with tree $i$ having the height $H[i]$.

Pak Dengklek is training an orangutan to jump from tree to tree.
In a single jump, the orangutan can jump from the top of a tree to the top of the closest tree, either to the left or to the right, which height is higher than the tree she is currently at.
Formally, if the orangutan is currently at tree $x$, then he can jump to tree $y$ if and only if any of these is satisfied:

- $y$ is the largest non-negative integer smaller than $x$ such that $H[y] > H[x]$; or
- $y$ is the smallest non-negative integer larger than $x$ such that $H[y] > H[x]$.

Pak Dengklek has $Q$ jumping plans, each can be represented as four integers $A$, $B$, $C$, and $D$ ($A \le B < C \le D$).
For each plan, Pak Dengklek would like to know whether it is possible for the orangutan to start from some tree $s$ ($A \le s \le B$) and end at any tree $e$ ($C \le e \le D$).
If it is possible, Pak Dengklek would like to know the minimum number of jumps the orangutan needs for that plan.

## Implementation Details

You should implement the following procedure.

```
void init(int N, int[] H)
```

* $N$: the number of trees.
* $H$: an array of length $N$. For each $i$ ($0 \le i \le N - 1$), tree $i$ has height $H[i]$.
* This procedure is called exactly once, before any calls to `minimum_jumps`.

```
int minimum_jumps(int A, int B, int C, int D)
```

* $A$, $B$: the range of trees that the orangutan can start from.
* $C$, $D$: the range of trees that the orangutan must end with.
* This procedure should return the minimum number of jumps to carry out the plan, or $-1$ if it is impossible to do so.
* This procedure is called exactly $Q$ times.

## Example

Consider the following call:

```
init(7, [3, 2, 1, 6, 4, 5, 7])
```

After initialization has been done, consider the following call:

```
minimum_jumps(4, 4, 6, 6)
```

This means Pak Dengklek plans to start at building $4$ and end at building $6$.
One way to achieve the minimum number of jumps is to first jump to building $3$, then jump to building $6$.
Another way is to jump to tree $5$, then jump to tree $0$.
Therefore, the procedure `minimum_jumps` should return $2$.

Consider another possible call:

```
minimum_jumps(1, 3, 5, 6)
```

This means Pak Dengklek plans to start at any building from $1$ to $3$ and end at either tree $5$ or $6$.
The only way to achieve the minimum number of jumps is to start at tree $3$, then jump to building $6$ using only one jump.
Therefore, the procedure `minimum_jumps` should return $1$.

Consider another possible call:

```
minimum_jumps(0, 1, 2, 2)
```

This means Pak Dengklek plans to start at either tree $0$ or $1$ and end at tree $2$.
Since tree $2$ is the shortest tree, it is impossible to be reached from any tree taller than it.
Therefore, the procedure `minimum_jumps` should return $-1$.

## Constraints

* $2 \le N \le 100\,000$.
* $1 \le H[i] \le N$ (for all $0 \le i \le N - 1$).
* All the values of $H$ is distinct.
* $0 \le A \le B < C \le D \le N - 1$.

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
* line $3 + i$ ($0 \le i \le Q - 1$): $A \; B \; C \; D$ for the $i$-th call of `minimum_jumps`

The sample grader prints your answers in the following format:

* line $1 + i$ ($0 \le i \le Q - 1$): return value of the $i$-th call to `minimum_jumps`
