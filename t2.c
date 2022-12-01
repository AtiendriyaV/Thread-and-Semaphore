#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


/* this function is run by the thread */
void *inc_x(void *x_void_ptr)
{
	
	int *x_ptr = (int *)x_void_ptr;
	sleep(10);
	while(++(*x_ptr) < 500);
		printf("x increment finished\n");
	return NULL;

}

int main()
{

	int x = 0, y = 0,val,mul;

	/* show the initial values of x and y */
	printf("x: %d, y: %d\n", x, y);


	pthread_t inc_x_thread;
	//pthread_t inc_y_thread;

	/* create a thread which executes count_x(&x) */
	val = pthread_create(&inc_x_thread, NULL, inc_x, &x) ;
	if(val !=0) 
	{

		fprintf(stderr, "Error creating thread\n");
		return 1;

	}
	
	while(++y < 100);

	printf("y increment finished\n");

	/* wait for the thread to finish */
	if(pthread_join(inc_x_thread, NULL)) 
	{

		fprintf(stderr, "Error joining thread\n");
		return 2;

	}
         
        for(x=0;x<=5;++x)
        {
         for(y=0;y<x;++y)
         {
	   mul=x*y;
	   
	/* show the results - x is now 100 thanks to the thread */
	printf("x: %d, y: %d, sum : %d\n", x, y,mul);
    
         }
           }
         
         
	return 0;

}




