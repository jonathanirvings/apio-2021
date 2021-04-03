# Counting Partition

Pak Dengklek have two arrays of $N$ integers, $A[0 \ldots N - 1]$ and $B[0 \ldots N - 1]$.
For given parameters $(X, Y)$ (where $X$ and $Y$ are positive integers), Pak Dengklek would like to split the array $A$ into a maximum number of partitions of consecutive elements, such that in each partition except the last one:

* Contains at least $B[Y - 1]$ elements.
* Integer $X$ appears at least $Y$ times.
* The last element is an integer $X$.

The last partition does not need to satisfy the above requirements.
The only requirement for the last partition is that it must contain at least one element.

For example, suppose $N = 6, A = [1, 1, 2, 2, 1, 1], B = [1, 3, 3, 4, 5, 6]$.

* For given parameters $(1, 1)$, Pak Dengklek can split $A$ into $4$ partitions: $[[1], [1], [2, 2, 1], [1]]$. Note that each partition, except the last, contains at least $B[0] = 1$ element, the integer $X = 1$ appears at least $Y = 1$ time, its last element is $X = 1$. Pak Dengklek cannot split $A$ into more than $4$ partitions.
* For given parameters $(1, 2)$, Pak Dengklek can split $A$ into $2$ partitions: $[[1, 1, 2, 2, 1], [1]$. Note that splitting $A$ to $[[1, 1], [2, 2, 1, 1]]$ is not valid as the first partition should contain at least $B[1] = 3$ elements.
* For given parameters $(2, 3)$, integer $X = 2$ should appear at least $Y = 3$ times in each partition except the last one. Since integer $2$ only appears $2$ times in $A$, Pak Dengklek cannot split $A$ into more than one partition.

Pak Dengklek have $Q$ parameters $(X, Y)$ and need your help to determine the maximum number of partitions of consecutive elements satisfying the conditions with the given parameters.

## Implementation Details

You should implement the following procedures:

```
void init(int N, int[] A, int[] B)
```

* $N$: the number of elements in the array $A$ and $B$.
* $A$: an array of size $N$.
* $B$: an array of size $N$.
* This procedure is called exactly once, before any calls to `count_partition`.

```
int count_partition(int X, int Y)
```

* $X, Y$: the parameters for splitting the array $A$.
* This procedure should return the maximum number of partitions of consecutive elements satisfying the conditions with the given parameters.
* This procedure is called exactly $Q$ times.

## Examples

### Example 1

Consider the following call:

```
init(6, [1, 1, 2, 2, 1, 1], [1, 3, 3, 4, 5, 6])
```

Let's say the grader calls `count_partition(1, 1)`. As described above, the call should return $4$.

Let's say the grader calls `count_partition(1, 2)`. As described above, the call should return $2$.

Let's say the grader calls `count_partition(2, 3)`. As described above, the call should return $1$.

### Example 2

Consider the following call:

```
init(4, [3, 1, 3, 3], [1, 1, 1, 1])
```

Let's say the grader calls `count_partition(1, 1)`. Pak Dengklek can split $A$ into $2$ partitions: $[[3, 1], [3, 3]]$. Therefore, the call should return $2$.

Let's say the grader calls `count_partition(2, 1)`. Since integer $2$ does not appear in $A$, Pak Dengklek cannot split $A$ into more than one partition. Therefore, the call should return $1$.

Let's say the grader calls `count_partition(3, 1)`. Pak Dengklek can split $A$ into $3$ partitions: $[[3], [1, 3], [3]]$. Therefore, the call should return $3$.


## Constraints

* $1 \le N \le 100\,000$
* $1 \le Q \le 100\,000$
* $1 \le A[i] \le 10^9$ (for all $0 \le i \le N - 1$)
* $1 \le B[i] \le N$ (for all $0 \le i \le N - 1$)
* $1 \le X \le 10^9$
* $1 \le Y \le N$

## Subtasks

1. (9 points) $B[i] = i + 1$ (for all $0 \le i \le N - 1$)
2. (14 points) $Q \le 5$
3. (22 points) $Y = 1$
4. (31 points) $X = 1$
5. (24 points) No additional constraints.

## Sample Grader

The sample grader reads the input in the following format:

* line $1$: $N \; Q$
* line $2$: $A[0] \; A[1] \; \ldots \; A[N - 1]$
* line $3$: $B[0] \; B[1] \; \ldots \; B[N - 1]$
* line $4 + i$ ($0 \le i \le Q - 1$): $X$ $Y$ for the $i$-th call to `count_partition`

The sample grader prints the result in the following format:

* line $1 + i $ ($0 \le i \le Q - 1$): return value of the $i$-th call to `count_partition`
