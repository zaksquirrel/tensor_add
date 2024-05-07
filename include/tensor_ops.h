#ifndef __TENSOR_OPS_H__
#define __TENSOR_OPS_H__

#define PRINT   0

#include <stdio.h>
#include <stdlib.h>

/* representation of the physical space where a tensor is stored
 *	- size_t	mem_length			: flattened tensor total length
 *	- int *		mem					: pointer to the first address of allocated memory
 */
struct mem_abs {
	size_t		mem_length;
	int *		mem;
};

/* a tensor dimensions and parameters
 *	- int *		base_addr			: first address of the allocated memory
 *	- size_t	nb_dims				: tensor number of dimensions 
 *	- struct *	dims				: parameters of one of the tensor dimension
 *		- uint	length				: length of the dimension
 *		- uint	stride				: memory "space" between two elements of the dimension
 */
struct tensor {
  int *			base_addr;
  size_t		nb_dims;
  struct dimension {
    unsigned int	length;
    unsigned int	stride;
  } * dims;
};

/* allocate and initialize a mem_abs struct
 *	- struct mem_abs **	ma			: pointer on struct pointer
 */
int mem_abs_create(struct mem_abs **);

/* free mem_abs struct
 *	- struct mem_abs *	ma			: struct pointer
 */
int mem_abs_destroy(struct mem_abs *);

/* reallocate mem_abs struct mem
 * called each time a dimension is added to a tensor
 *	- struct mem_abs *	ma			: struct pointer
 *	- size_t			size		: size of the new dimension	
 */
int mem_abs_grow(struct mem_abs *, size_t);

/* allocate and initialize tensor
 * add dimensions by incrementally calling mem_abs_grow() 
 *	- struct tensor **	t			: pointer on struct pointer
 *	- size_t			size		: number of tensor dimensions
 *	- int *			 	dimslength	: array of the tensor dimensions length
 *	- struct mem_abs *	ma			: pointer to struct
 */
int tensor_create(struct tensor **, size_t, int *, struct mem_abs *);

/* free abs struct
 *	- struct tensor *	t			: pointer to struct
 */
int tensor_destroy(struct tensor *);

/* get address of a point in the tensor using recursivity
 * ie. as if, if the tensor was a tree
 *	- struct tensor *	t			: pointer to struct
 *	- int				idx			: current level == current dimension
 *	- int *				coords		: coordinates of the target point
 *	- int *				offset		: memory offset of the target point
 *  - int **			addr		: pointer to the target point address
 */
void get_point_addr_recurs(struct tensor *, int, int *, int *, int **);

/* run through a tensor "row first" recursively - calls get_point_addr_recurs()
 *	- struct tensor *	t			: pointer to struct
 *	- int				idx			: current level == current dimension
 *	- int *				dim_size	: array of the tensor dimensions length
 *	- int *				coords		: current point coordnates
 */
void tensor_run_recurs_row_first(struct tensor *, int, int *, int *);

/* populate a tensor
 *	- struct tensor *	t			: pointer to struct
 *	- int *			 	dimensions	: array of the tensor dimensions length
 */
int tensor_init(struct tensor *, int *);

/* run through two tensors "row first" recursively and add each element - calls get_point_addr_recurs()
 *	- int				idx			: current level == current dimension
 *	- struct tensor *	A			: pointer to struct
 *	- int *				dim_A	: array of the tensor dimensions length
 *	- struct tensor *	B			: pointer to struct
 *	- int *				coords		: current point coordnates
 */
void
tensor_add_recurs_row_first(int, struct tensor *, int *, struct tensor *, int *);

/* contract two tensors
 *	- struct tensor *	A			: pointer to struct
 *	- int *			 	dim_A	    : array of the tensor dimensions length
 *	- struct tensor *	B			: pointer to struct
 */
int tensor_add(struct tensor *, int *, struct tensor *);
#endif // __TENSOR_OPS_H__
