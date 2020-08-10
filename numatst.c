#include <stdio.h>
#include <numa.h>
#include <numaif.h>

int main(){
	printf("NUMA - NON UNIFORME MEMORY ACCESS: TEST LIBRARY\n");
	/* testing functions of numalib */
	printf("%d\n",numa_num_configured_nodes());
	printf("%ld\n",sizeof(int));
	printf("Numa avaliable: %d\n",numa_available());

	/* here you should align ptr_to_check topage boundary */
	int your_address=313;
	void * ptr_to_check = &your_address;
	printf("VA: %p --- PA: %p\n",&your_address,ptr_to_check);
	int status[1];
	int ret_code;
	status[0]=-1;
	ret_code=move_pages(0 /*self memory*/,1,&ptr_to_check,NULL,status,0);
	printf("Memory at %p is at %d node (retcode %d)\n",ptr_to_check,status[0],ret_code);

	int *new_ptr = numa_alloc_onnode(sizeof(int),1);
	*new_ptr=404;
	/* is necessary to put a single value in the allocate space by this reason:
	   "All numa memory allocation policy only takes effect when a page is
            actually faulted into the address space of a process by accessing it.
            The numa_alloc_* functions take care of this automatically."
	*/
	ptr_to_check = new_ptr;
	printf("VA: %p --- PA: %p\n",new_ptr,ptr_to_check);
	status[0]=-1;
	ret_code=move_pages(0 /*self memory*/,1,&ptr_to_check,NULL,status,0);
	printf("Memory at %p is at %d node (retcode %d)\n",ptr_to_check,status[0],ret_code);
	/* ============================ */
	return 0;
}
