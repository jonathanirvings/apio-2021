# Box Lifting

A stack of $N$ boxes, numbered from $0$ to $N - 1$ from top to bottom, are initially located at coordinates $(0, 0)$.
Pak Dengklek would like to store these boxes in storage areas, which are located at coordinates $(t, M - t)$ for all $0 \le t \le M$.
Box $i$ needs to be stored at coordinates $(A[i], M - A[i])$.

A forklift is used to move the boxes around.
In one step, the forklift can:

1. Choose some coordinates $(x, y)$ that contains some boxes.
1. Choose some positive integer $k$ that is at most the number of boxes at $(x, y)$, then lift the $k$ topmost boxes from that coordinates.
1. Choose either coordinates $(x + 1, y)$ or $(x, y + 1)$ as the destination, given that the destination is a storage area **or** does not contain any boxes.
1. Put all the lifted boxes in the destination while preserving their orders.

Find the minimum number of steps needed to store all the boxes in their designated area.
Note that the stored boxes in each storage area do not need to follow any certain order.

## Implementation Detail

You should implement the following procedure:

```
int minimum_lifts(int N, int M, int[] A)
```

* $N$: the number of boxes.
* $M$: an integer where the storage areas are located at coordinates $(t, M - t)$ for all $0 \le t \le M$.
* $A$: an array of length $N$, where $(A[i], M - A[i])$ are the coordinates to store box $i$ at.
* This procedure should return the minimum number of steps required to store all the boxes.
* This procedure is called exactly once.

## Example

Consider the following call:

```
minimum_lifts(4, 3, [0, 2, 1, 0])
```

There are $4$ boxes that must be stored at $(0, 3)$, $(2, 1)$, $(1, 2)$, and $(0, 3)$ respectively.
One way to achieve the minimum number of steps is as follow:
1. Move all the boxes at $(0, 0)$ to $(0, 1)$.
1. Move the topmost box at $(0, 1)$ to $(0, 2)$
1. Move the $2$ topmost boxes at $(0, 1)$ to $(1, 1)$.
1. Move the the topmost box at $(1, 1)$ to $(2, 1)$.
1. Move the only box at $(1, 1)$ to $(1, 2)$.
1. Move the only box at $(0, 2)$ to $(0, 3)$.
1. Move the only box at $(0, 1)$ to $(0, 2)$.
1. Move the only box at $(0, 2)$ to $(0, 3)$.

Therefore, the procedure `minimum_lifts` should return $8$.

## Constraints

* $1 \le N \le 2000$
* $1 \le M \le 100\,000$
* $0 \le A[i] \le M$ (for all $0 \le i \le N - 1$)

## Subtasks

1. (9 points) $N, M \le 10$
1. (8 points) $N, M \le 20$
1. (7 points) $N, M \le 30$
1. (11 points) $A[i]$ is divisible by $M$ (for all $0 \le i \le N - 1$).
1. (14 points) $N = M + 1$, $A[i] = i$ (for all $0 \le i \le N - 1$)
1. (30 points) $N \le 200$
1. (21 points) No additional constraints.

## Sample Grader

The sample grader reads the input in the following format:

* line $1$: $N \; M$
* line $2$: $A[0] \; A[1] \; \ldots \; A[N - 1]$

The sample grader prints your answers in the following format:

* line $1$: return value of `minimum_lifts`
