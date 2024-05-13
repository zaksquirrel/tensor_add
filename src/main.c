#include "tensor_ops.h"
#include <time.h>

int 
main (int argc, char ** argv)
{
    int dimensions[3] = { 100, 100, 20 };
	
	struct mem_abs * ma0;
	struct tensor * t0;
		
	printf("Creationg memory abstraction\n");
	mem_abs_create(&ma0);
	printf("Memory abstraction created\n");
	
	printf("Checking initialized memory abstraction\n");
	printf("length = %ld base = %p\n", ma0->mem_length, ma0->mem); 

	printf("Creating tensor\n");
	tensor_create(&t0, 3, dimensions, ma0);
	printf("Tensor created\n");

	printf("Checking extended memory abstraction\n");
	printf("length = %ld base = %p\n", ma0->mem_length, ma0->mem); 

	printf("Testing mem...\n");
	for (int i = 0 ; i < ma0->mem_length ; ++i)
	{
		ma0->mem[i] = i * 10;
		printf("&mem[%d]=%p\tmem[%d] = %d\n", i, ma0->mem+i, i, ma0->mem[i]);
	}

	printf("Populating tensor\n");
	tensor_init(t0, dimensions);
	printf("Tensor populated\n");

	struct mem_abs * ma1;
	struct tensor * t1;
		
	printf("Creationg memory abstraction\n");
	mem_abs_create(&ma1);
	printf("Memory abstraction created\n");
	
	printf("Checking initialized memory abstraction\n");
	printf("length = %ld base = %p\n", ma1->mem_length, ma1->mem); 

	printf("Creating tensor\n");
	tensor_create(&t1, 3, dimensions, ma1);
	printf("Tensor created\n");

	printf("Checking extended memory abstraction\n");
	printf("length = %ld base = %p\n", ma1->mem_length, ma1->mem); 

	printf("Testing mem...\n");
	for (int i = 0 ; i < ma1->mem_length ; ++i)
	{
		ma1->mem[i] = i * 10;
		printf("&mem[%d]=%p\tmem[%d] = %d\n", i, ma1->mem+i, i, ma1->mem[i]);
	}

	printf("Populating tensor\n");
	tensor_init(t1, dimensions);
	printf("Tensor populated\n");

	float time1,time2,time;

	printf("Tensor addition\n");
	time1 = clock();
	tensor_add(t1, dimensions, t1);
	time2 = clock();
	printf("Tensor added\n");
	time=(float) (time2-time1)/CLOCKS_PER_SEC;

	printf("\ntime spent %f\n", time);
	

	printf("Destroying tensor\n");
	tensor_destroy(t1);
	printf("Tensor destroyed\n");
	
	printf("Destroying memory abstraction\n");
	mem_abs_destroy(ma1);
	printf("Memory abstraction destroyed\n");

    /**
     * Ex: How to access a particular point in a tensor
	 *  printf("Accessing point : ( 3, 2, 1 )\n");
	 *  int coords[3] = { 3, 2, 1 }; 
	 *  int * point;
	 *  int offset;
	 *  point = t1->base_addr;
	 *  offset = 0;
	 *  get_point_addr_recurs(t1, 0, coords, &offset, &point);
	 *  printf("&point = %p, point = %d\n", point, *point);
     */

	return 0;
}
