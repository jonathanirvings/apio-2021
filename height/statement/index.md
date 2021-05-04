# Height Restrictions

In the city of Makassar, $N$ buildings, numbered from $0$ to $N - 1$, are planned to be built with positive integer heights that are still to be determined.

The engineer in charge of the plan will gradually impose some restrictions on the height of the buildings.
Each restriction is represented by three integers $L$, $R$, and $H$ ($0 \le L \le R \le N - 1$), which means that the maximum height of the buildings numbered from $L$ to $R$ (inclusive) must be exactly $H$.
Formally, if $a[i]$ represents the height of building $i$, then $\max(a[L], a[L + 1], \ldots, a[R]) = H$ must be satisfied.

The engineer will impose a total of $Q$ restrictions.
Each time a new restriction is added, determine whether it is still possible to carry out the plan.
In other words, determine whether there exists a sequence of positive integers $a[0], a[1], \ldots, a[N - 1]$, where $a[i]$ is the height of building $i$, such that all the restrictions imposed so far are still satisfied.

## Implementation Details

You should implement the following procedures:

```
void init(int N)
```

* $N$: the number of buildings that are planned to be built.
* This procedure is called exactly once, before any calls to `add_restriction`.

```
int add_restriction(int L, int R, int H)
```

* $L$, $R$: the range of buildings that are imposed by the new restriction.
* $H$: the maximum height restriction that must be satisfied.
* This procedure should return $1$ if it is still possible to carry out the plan with all the restrictions added so far, or $0$ if it is impossible to do so.
* This procedure is called exactly $Q$ times.

## Example

Consider the following call:

```
init(7)
```

There are $7$ buildings that are planned to be built.
After initialization has been done, consider the following call:

```
add_restriction(1, 1, 5)
```

This means building $1$ must have a height of exactly $5$.
One possible sequence of building heights is $[10, 5, 1, 7, 4, 5, 5]$.
Therefore, the procedure `add_restriction` should return $1$.

Consider another possible call:

```
add_restriction(5, 6, 2)
```

This means the maximum height of buildings $5$ and $6$ must be exactly $2$.
One possible sequence of building heights is $[9, 5, 1, 8, 5, 2, 1]$.
Therefore, the procedure `add_restriction` should return $1$.

Consider another possible call:

```
add_restriction(0, 4, 7)
```

This means the maximum height of all buildings from $0$ to $4$ must be exactly $7$.
One possible sequence of building heights is $[7, 5, 7, 7, 7, 2, 2]$.
Therefore, the procedure `add_restriction` should return $1$.

Consider another possible call:

```
add_restriction(0, 6, 10)
```

This means the maximum height of all buildings must be exactly $10$.
Since every building was part of some restrictions where the maximum height is less than $10$, it is now impossible to satisfy the restrictions.
Therefore, the procedure `add_restriction` should return $0$.

Consider another possible call:

```
add_restriction(1, 1, 5)
```

This is actually the same as the first restriction.
As the plan was already impossible, any further additional restrictions will always be impossible.
Therefore, the procedure `add_restriction` should return $0$.

## Constraints

* $1 \le N, Q \le 100\,000$
* $0 \le L \le R \le N - 1$
* $1 \le H \le 10^9$

## Subtasks

1. (5 points) $L = R$
1. (9 points) $L = 0$
1. (13 points) $N, Q \le 2000$
1. (16 points) The value of $R - L$ is the same for all calls to `add_restriction`.
1. (31 points) $H \le 20$
1. (26 points) No additional constraints.

## Sample Grader

The sample grader reads the input in the following format:

* line $1$: $N \; Q$
* line $2 + i$ ($0 \le i \le Q - 1$): $L \; R \; H$ for the $i$-th call to `add_restriction`

The sample grader prints your answers in the following format:

* line $1 + i$ ($0 \le i \le Q - 1$): return value of the $i$-th call to `add_restriction`
