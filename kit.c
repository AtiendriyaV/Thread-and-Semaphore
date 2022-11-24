#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>

int main(int argc, char *argv[])
{
	int len,val,i=0;
	int left,right,id;
	char buf[30];
	//a=0;
	//b=4;
	key_t k = 1012;	
 	struct  sembuf p1,p5,p2,p4;
	time_t t;
	
	if (argc !=4)
	{
		write(1,"Need Argument 1 : Cookingdish Name",35); write(1,"\n",1);
		write(1,"Need Argument 2 : Food available no.",32); write(1,"\n",1);
		write(1,"Need Argument 3 : Cooking Eating no.",33);	write(1,"\n",1);	
		exit(0);
	}	
	left=atoi(argv[2]);	
	right=atoi(argv[3]);
	p1.sem_num=left;  /* semaphore number */
	p1.sem_op=-1;   /* semaphore operation */
	p1.sem_flg=0;  /* operation flags */

	p5.sem_num=right;  /* semaphore number */
	p5.sem_op=-1;   /* semaphore operation */
 	p5.sem_flg=0;  /* operation flags */

	p2.sem_num=left;  /* semaphore number */
	p2.sem_op=+1;   /* semaphore operation */
	p2.sem_flg=0;  /* operation flags */

	p4.sem_num=right;  /* semaphore number */
	p4.sem_op=+1;   /* semaphore operation */
 	p4.sem_flg=0;  /* operation flags */



	id= semget(k, 5, IPC_CREAT|0777);
	
	if (id ==-1 )
	{
		write(1, "Create Error", 12);
		exit(0);
	}
	len=sprintf(buf,"Descriptor: %d",id);
	write(1,buf,len);

	while (1)
	{
		
		write(1, argv[1], sizeof(argv[1])+2 );
		write(1,"\n",1);
		write(1,"^^^^^^^^^^^^^^^",15);
		write(1,"=====COOKING====", 16);
		write(1,"\n",1);
			
		sleep(rand()%3);

		write(1,"=====HUNGRY=====", 16);
		write(1,"\n",1);
		
		sleep(rand()%3);
		
		val=semop(id,&p1,1);
		if (val == -1 )
		{
			write(1, "Food available Error", 16);
			exit(0);
		}
		write(1,"Taken Food available ", 20);
		write(1,"\n",1);
		//val= semctl(id,0, GETVAL, NULL);
		//len=sprintf(buf,"Sem 0 Before : %d",val);
		//write(1,buf,len);		
		//write(1,"\n", 1);

		
		sleep(rand()%3);	
		val=semop(id,&p5,1);
		write(1,"\n",1);
		if (val ==-1 )
		{
			write(1, "Cooking Eating Error", 16);
			exit(0);
		}
		write(1,"Taken Cooking Eating ", 20);
		write(1,"\n",1);
		//val= semctl(id,4, GETVAL,NULL);
		//len=sprintf(buf,"Sem 4 Before : %d",val);
		//write(1,buf,len);		
		//write(1,"\n", 1);		
		
		write(1,"====EATING=====", 16);
		write(1,"\n",1);
		time(&t);
		printf("%d Time at %s", i+1, ctime(&t));
		write(1,"\n",1);
		//len=sprintf(buf,"Descri:  %d",id);
		//write(1,"\n",1);
		//write(1,buf,len);	
		
		sleep(7);
		
		val=semop(id,&p2,1);
	 	if (val ==-1)
		{
			write(1, "Food available Error", 16);
			exit(0);
		}
		write(1,"Put down the Food available", 23);
		write(1,"\n",1);
		
		//val= semctl(id,0, GETVAL, NULL);
		//len=sprintf(buf,"Sem 0 After : %d",val);
		//write(1,buf,len);		
	        //write(1,"\n", 1);

		sleep(rand()%3);				
		val=semop(id,&p4,1);
	 	if (val == -1 )
		{
			write(1, "Cooking Eating Error", 16);
			exit(0);
		}
		write(1,"Hold the Cooking Eating", 24);
		write(1,"\n",1);
		//val= semctl(id,4, GETVAL, NULL);
		//len=sprintf(buf,"Sem 4 After : %d",val);
		//write(1,buf,len);		
		write(1,"\n", 1);
		i++;
		
	}
	
}
	
       
