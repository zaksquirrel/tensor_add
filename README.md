# tensor_add
This code implements in C the addition operation on parametrable tensors through recursion.

## file structure
In this repository you should find :
- the present _README.md_
- _src/_ which contains :
	- _main.c_ where the *main()* is 
	- _tensor_ops.c_ where the tensor functions are implemented
- _include/_ which contains :
	- _tensor\_ops.h_ where the tensor structures and functions are implemented
- a _Makefile_ to build the repo

## program structure
Currently a tensor is implented using two structures :
- *struct tensor* which contains a tensor parameters
- *struct mem_abs* which contains a tensor data
Accessing an element in the tensor is the same as accesing an element of *mem_abs*, 
with *tensor* being used to find its index (called *offset*).

## running through the tensor
As the goal is to be able to process variable "depth" tensors, the traditionnal way of doing so (nested for loops) is not applicable here.
Instead we run through the allocated *mem*, which is basically the flattened tensor data.
*tensor* is used to organize how data is stored and accessed.

To run through the tensor we can treat it as a tree .

### tree
Take a tensor _t_ of _n_ dimensions, with its dimensions length being _l_ = _{a,...,z}_ and 
its coordinates going from _{0,0,0,...}_ to _{l,l,l,...}_.

This structure can be seen as an ordered tree of depht _n_ with _l_ nodes at level _(n-x)_.
Each node on a given _x_ level corresponding to the coordinate of of the _xth_ dimension of the tensor.
We can then run through the whole tensor as if it were a tree, or find one particular element by going through one branch.

As such we can use *recursive* functions to navigate the tensor.

## Usage
``` bash
    make
    make test
```
# tensor_add
