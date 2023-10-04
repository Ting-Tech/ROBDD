# ROBDD

Reads a single-output Boolean function in PLA format and outputs the corresponding ROBDD in pictorial DOT format.



## Requirement

- gcc/clang with C++17 supported
- CMake



## Build

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```



## Support Platforms

GCC/Clang



## Run

```bash
./main [input_pla] [output_dot]
```



## Feature

|          | Name            | Description                                              |
| :------: | --------------- | -------------------------------------------------------- |
| &#x2705; | Read file       | Read the content of the pla file.                        |
| &#x2705; | Handle commands | Handle the commands from read from the pla file.         |
| &#x2705; | ROBDD           | Reduce the Binary Decision Diagram.                      |
| &#x2705; | Output file     | Output the dot format file's ROBDD.                      |
| &#x2705; | Output picture  | Outputs the corresponding ROBDD in pictorial DOT format. |



## Test Result

### Case 1 (F = bcd + a'b + abcd' + a'c'd')

[example/case3](./example/case3)

#### Input PLA

``` pla
.i 4
.o 1
.ilb a b c d
.ob F
.p 4
-111 1
01-- 1
1110 1
0-00 1
.e
```

#### Output Dot

``` dot
digraph ROBDD {
	{rank=same 1}
	{rank=same 2 3}
	{rank=same 4 7}
	{rank=same 8}

	0[label=0, shape=box]
	1[label="a"]
	2[label="b"]
	3[label="b"]
	4[label="c"]
	7[label="c"]
	8[label="d"]
	16[label=1, shape=box]

	1->2[label=0, style=dotted]
	1->3[label=1, style=solid]
	2->4[label=0, style=dotted]
	2->16[label=1, style=solid]
	3->0[label=0, style=dotted]
	3->7[label=1, style=solid]
	4->8[label=0, style=dotted]
	4->0[label=1, style=solid]
	7->0[label=0, style=dotted]
	7->16[label=1, style=solid]
	8->16[label=0, style=dotted]
	8->0[label=1, style=solid]
}
```

#### Generated PNG

![case3](./assets/case3.png)



### Case 2 (F = bcd'e + a'bd + b'c'de + abcd'e' + a'c'd'e)
[example/case4](./example/case4)

#### Input PLA

``` pla
.i 5
.o 1
.ilb a b c d e
.ob F
.p 5
-1101 1
01--1 1
-0011 1
11100 1
0-001 1
.e
```

#### Output Dot

``` dot
digraph ROBDD {
	{rank=same 1}
	{rank=same 2 3}
	{rank=same 4 6 7}
	{rank=same 12 15}
	{rank=same 16}

	0[label=0, shape=box]
	1[label="a"]
	2[label="b"]
	3[label="b"]
	4[label="c"]
	6[label="c"]
	7[label="c"]
	12[label="d"]
	15[label="d"]
	16[label="e"]
	32[label=1, shape=box]

	1->2[label=0, style=dotted]
	1->3[label=1, style=solid]
	2->4[label=0, style=dotted]
	2->16[label=1, style=solid]
	3->6[label=0, style=dotted]
	3->7[label=1, style=solid]
	4->16[label=0, style=dotted]
	4->0[label=1, style=solid]
	6->12[label=0, style=dotted]
	6->0[label=1, style=solid]
	7->0[label=0, style=dotted]
	7->15[label=1, style=solid]
	12->0[label=0, style=dotted]
	12->16[label=1, style=solid]
	15->32[label=0, style=dotted]
	15->0[label=1, style=solid]
	16->0[label=0, style=dotted]
	16->32[label=1, style=solid]
}
```

#### Generated PNG

![case4](./assets/case4.png)



## Support

Email: allen0523win@gmail.com

Email: B11130225@mail.ntust.edu.tw  