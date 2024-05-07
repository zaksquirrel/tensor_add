#include "tensor_ops.h"

int
mem_abs_create(struct mem_abs ** ma)
{
	*ma = malloc(sizeof(struct mem_abs));
	(*ma)->mem = malloc(sizeof(int));
	(*ma)->mem_length = 1;
	printf("mem ptr during alloc = %p\n", (*ma)->mem);	

	return 0;
}

int
mem_abs_destroy(struct mem_abs * ma)
{
	free(ma->mem);
	free(ma);
	
	return 0;
}

int 
mem_abs_grow(struct mem_abs * ma, size_t size)
{
	ma->mem = realloc(ma->mem, (ma->mem_length * size * sizeof(int)));
	ma->mem_length *= size;
	printf("Memory abstraction extended\n");

	return 0;
}

int
tensor_create(struct tensor ** t, size_t size, int * dimslength, struct mem_abs * ma)
{
	int i; 
	*t = malloc(sizeof(struct tensor));
	
	(*t)-> nb_dims = size;
	(*t)-> dims = malloc(sizeof(struct dimension) * (*t)->nb_dims);

	for (i = 0 ; i < (*t)->nb_dims ; ++i) 
	{
		(*t)->dims[i].length = dimslength[i];
		(*t)->dims[i].stride = 1;							//memory contiguous	
		
		mem_abs_grow(ma, (size_t)dimslength[i]);
	}

	(*t)->base_addr = ma->mem; // &mem[0];
	printf("Created %ld dimensions tensor with base address = %p\n",
			(*t)->nb_dims, (*t)->base_addr);

	return 0;
}

int
tensor_destroy(struct tensor * t)
{
	free(t->dims);
	free(t);

	return 0;
}

void
get_point_addr_recurs(struct tensor * t, int idx, int * coords, int * offset, int ** addr)
{
	//printf("idx = %d coord = %d offset = %d\n", idx, coords[idx], *offset);
	
	if (idx >= t->nb_dims)
	{
		//printf("point mem offset = %d\n", *offset);
		*addr += *offset;
		//printf("point mem addr = %p\n", *addr);
		return;
	}
	else
	{	
		int i, temp;
		temp = coords[idx];
		//printf("temp = %d\n", temp);

		for (i = (idx+1) ; i < t->nb_dims ; ++i)
		{
			temp *= t->dims[i].length;
			//printf("ite %d temp = %d\n", i, temp);
		}
		(*offset) += temp;
		get_point_addr_recurs(t, (idx+1), coords, offset, addr);
	}
}

void
tensor_run_recurs_row_first(struct tensor * t, int idx, int * dim_size, int * coords)
{
	int i;
	
	if (idx >= t->nb_dims)
	{
		int * pt_addr; 
		int offset;
		pt_addr = t->base_addr;

		//printf("t->nb_dims = %ld\n", t->nb_dims);
		printf("point ( ");
		for (i = 0 ; i < t->nb_dims ; ++i) 
		{
			printf("%d ", coords[i]);
		}
			
		offset = 0;
		get_point_addr_recurs(t, 0, coords, &offset, &pt_addr);
		printf(") mem offset = %d\taddr = %p ", offset, pt_addr);	
		
		//init w/ val
		*pt_addr = offset;

		printf("value = %d\n", *pt_addr);

		return;
	}
	else
	{	
		for (i = 0 ; i < dim_size[idx] ; ++i)
		{
			coords[idx] = i;
			tensor_run_recurs_row_first(t, (idx+1), dim_size, coords);
		}
	}
}

int 
tensor_init(struct tensor * t, int * dimensions)
{
	printf("Starting initialization\n");

	int coords[t->nb_dims];
	
	printf("Starting recursivity\n");
	tensor_run_recurs_row_first(t, 0, dimensions, coords);
	printf("Recursivity over\n");

	return 0;
}

void
tensor_add_recurs_row_first(int idx, struct tensor * A, int * dim_A, struct tensor * B, int * coords)
{
	int i;
	
	if (idx >= A->nb_dims)
	{
		int * pA_addr; 
		int * pB_addr; 
		pA_addr = A->base_addr;
		pB_addr = B->base_addr;
		int offset;

		printf("point ( ");
		for (i = 0 ; i < A->nb_dims ; ++i) 
		{
			printf("%d ", coords[i]);
		}
			
		offset = 0;
		get_point_addr_recurs(B, 0, coords, &offset, &pB_addr);
		get_point_addr_recurs(A, 0, coords, &offset, &pA_addr);
		printf(") mem offset = %d\taddr = %p ", offset, pA_addr);	
		
		*pA_addr += *pB_addr;

		printf("value = %d\n", *pA_addr);

		return;
	}
	else
	{	
		for (i = 0 ; i < dim_A[idx] ; ++i)
		{
			coords[idx] = i;
			tensor_add_recurs_row_first((idx+1), A, dim_A, B, coords);
		}
	}
}
int 
tensor_add(struct tensor * A, int * dim_A, struct tensor * B)
{
	printf("Starting initialization\n");

	int coords[A->nb_dims];
	
	printf("Starting addition\n");
	tensor_add_recurs_row_first(0, A, dim_A, B, coords);
	printf("Addition over\n");

	return 0;
}
