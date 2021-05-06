# National Defence

The country of Toki has a territory with the shape of a rectangle.
The map of Toki can be represented in the Cartesian coordinate system.
Four corner points of the rectangle are at points $(0, 0)$, $(N, 0)$, $(N, M)$, and $(0, M)$.

Pak Dengklek as the Ministry of Defence of Toki wants to split the territory of the country into $K$ territorial defences numbered from $0$ to $K - 1$.
The following are the rules of each territory that Pak Dengklek wants.

* All territorial defences must be inside the territory of the country.
* A territorial defence has the shape of a rectangle, whose all corner points are lattice points and all sides are parallel to the $X$-axis or $Y$-axis.
* Territorial defence does not intersect but is allowed to touch at the corner points or sides of other territorial defences.

Pak Dengklek wants you to split the territory of the country with the rules above.
Other than that, Pak Dengklek wants territorial defence $i$ to have an area of $A[i]$.
You are allowed to disobey this request.
However, Pak Dengklek will be happier if you can assign the area of the territorial defence following the area that Pak Dengklek wants.

Suppose that territorial defence $i$ that you made has an area of $b_i$.
For every territorial defence $i$, Pak Dengklek's happiness value will increase by:

* $3$, if $b_i = A[i]$,
* $2$, if $b_i > A[i]$,
* $1$, if $0 < b_i < A[i]$,
* $0$, if you did not assign territorial defence $i$ any area.

Help Pak Dengklek to determine how to split the territorial defences such that Pak Dengklek's happiness is maximized!
If there exists more than one solution, output any of them.
You are allowed to exclude part of the Toki territory from any territorial defences.

## Implementation Details

This is an output-only task with partial scoring.
You are given $10$ input files.
For each input file, you should submit an output file with a split of the territorial defences.
For each output file, you will get points based on Pak Dengklek's happiness.

You are not supposed to submit any source code for this task.

## Input Format

Each input file describes the areas of the territorial defences that Pak Dengklek wants.
The format is as follows:

* line $1$: $N \; M \; K$
* line $2$: $A[0] \; A[1] \; \ldots \; A[K - 1]$

## Output Format

Each output file is in the following format:

* line $1 + i$ ($0 \le i \le K - 1$): four integers which are either
  * $x_1$, $x_2$, $y_1$, and $y_2$ ($x_1 < x_2$ and $y_1 < y_2$), which shows that the corner points of territorial defence $i$ is at points $(x_1, y_1)$, $(x_2, y_1)$, $(x_2, y_2)$, and $(x_1, y_2)$, or
  * $-1$, $-1$, $-1$, and $-1$, if you do not assign an area to territorial defence $i$.

## Example 1

Consider the following input:

```
4 5 3
8 9 3
```

possible valid output is:

```
0 4 0 2
0 3 2 5
3 4 2 5
```

This sample can be illustrated with the following image.
The numbers inside each rectangle in the image corresponds to each territorial defence.
Since all territorial defences have the same area as what Pak Dengklek wants, therefore Pak Dengklek's happiness value is $3 + 3 + 3 = 9$.

![](render/defence-1.png = 250x)

## Example 2

Consider the following input:

```
3 5 4
5 4 3 3
```

possible valid output is:

```
0 1 0 5
1 2 0 4
2 3 0 3
-1 -1 -1 -1
```

This sample can be illustrated with the following image.
The numbers inside each rectangle in the image correspond to territorial defences.
Note that in this sample output, territorial defence $3$ is not assigned with any area. Moreover, there is part of Toki territory that is not inside any territorial defences.
Pak Dengklek's happiness value for this sample is $3 + 3 + 3 + 0 = 9$.

![](render/defence-2.png = 250x)

## Constraints

* $1 \le N, M \le 10^9$
* $1 \le K \le 100\,000$
* $1 \le A[i] \le 10^9$ (for all $0 \le i \le K - 1$)
* $A[0] + A[1] + \ldots + A[K - 1] = N \times M$
* It is guaranteed that there exists a split which satifies all of Pak Dengklek's requests.

## Scoring

If your output for a test case is not valid, your score for that test case will be $0$.
Otherwise, if $x$ denotes Pak Dengklek's total happiness based on your territorial defences assignment, then your score will be:

| Condition | Point                            |
| --------- | -------------------------------- |
| $x = 3K$  | $10$                             |
| $x < 3K$  | $10 \left(\frac{x}{3K}\right)^2$ |

The specification for each test case is given below:

| Test case | $N$ | $M$ | $K$ | $A$                   |
| --------- | --- | --- | --- |:--------------------- |
| 01        | $5$ | $5$ | $5$ | $A = [4, 4, 4, 4, 9]$ |
| 02        | $6$ | $7$ | $8$ | $A = [2, 3, 4, 5, 6, 6, 7, 9]$ |
| 03        | $1$ | $10^9$ | $10^5$ | No specific constraints |
| 04        | $99999$ | $50000$ | $99999$ | $A[i] = i + 1$ (for all $0 \le i \le K - 1$) |
| 05        | $9973 \times 293$ | $99991 \times 311$ | $293 \times 311$ | $A_i = 9973 \times 99991$ (for all $0 \le i \le K - 1$) |
| 06        | $2$ | $10^9$ | $20$ | There are $10$ even values in $A$ and $10$ odd values in $A$|
| 07        | $2$ | $10000$ | $100$ | No specific constraints |
| 08        | $4681$ | $229383$ | $30$ | $A[i] = 2^i$ (for all $0 \le i \le K - 1$) |
| 09        | $46368$ | $28657$ | $23$ | $A[0] = 1$; $A[1] = 1$; $\sqrt{A[i]} = \sqrt{A[i-1]} + \sqrt{A[i-2]}$ (for all $2 \le i \le K - 1$) |
| 10        | $2000$ | $2000$ | $79191$ | $A_i \le 100$ (for all $0 \le i \le K - 1$); <br />The test case is generated such that a new element of $A$, with uniform probability distribution from its valid range, is created until the total sum of $A$ is $N \times M$ |
