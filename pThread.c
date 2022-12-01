/*pthread_t thread;

int pthread_create
	(pthread_t *thread, 
	 const pthread_attr_t *attr, 
	 void *(*start)(void *),
  	void *arg);
 
pthread_t pthread_self(void);  // ppid();

int pthread_exit(void *value_ptr);     // terminate

int pthread_join(pthread_t thread, void **value_ptr);  // parent will wait, or joined with parent

int pthread_detach(pthread_t thread);   // Don't affect parent process, it is removed from parent

====================================================
*/

//  How to compile pThread programs
// https://www.includehelp.com/c-programming-questions/compiling-program-with-pthread-library-linux.aspx
//=================================================================
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


/* this function is run by the thread */
void *inc_x(void *x_void_ptr)
{

	/* increment x to 100 */
	//pthread_t tid;
	//tid=pthread_self();
	
	int *x_ptr = (int *)x_void_ptr;
	sleep(10);
	while(++(*x_ptr) < 1000);
		printf("x increment finished\n");

	/* the function must return something - NULL will do */
	return NULL;

}




int main()
{

	int x = 0, y = 0,val,sum;

	/* show the initial values of x and y */
	printf("x: %d, y: %d\n", x, y);

	/* this variable is our reference to the thread */
	pthread_t inc_x_thread;
	//pthread_t inc_y_thread;

	/* create a thread which executes count_x(&x) */
	val = pthread_create(&inc_x_thread, NULL, inc_x, &x) ;
	if(val !=0) 
	{

		fprintf(stderr, "Error creating thread\n");
		return 1;

	}
	/*val = pthread_create(&inc_y_thread, NULL, inc_x, &x); 
	if(val !=0)
	{

		fprintf(stderr, "Error creating thread\n");
		return 1;

	}*/
	/* increment y to 100 in the first thread */
	while(++y < 100);

	printf("y increment finished\n");

	/* wait for the thread to finish */
	if(pthread_join(inc_x_thread, NULL)) 
	{

		fprintf(stderr, "Error joining thread\n");
		return 2;

	}

	sum=x+y;
	/* show the results - x is now 100 thanks to the thread */
	printf("x: %d, y: %d, sum : %d\n", x, y,sum);

	return 0;

}





