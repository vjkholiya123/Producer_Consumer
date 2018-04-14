# include <unistd.h>
# include <stdio.h>
# include <semaphore.h>
# include <pthread.h>
# include <stdlib.h>

int item;
int buffer_size;
int buffer[20];
sem_t empty_sema;
sem_t full_sema;
pthread_mutex_t mutex_lock;
void *thread_producer();
void *thread_consumer();
int main()
 {
	x:
	printf("\nEnter the size of the buffer (max 20): ");
	scanf("%d",&buffer_size);
	if(buffer_size<=20)
	{
	sem_init(&empty_sema,2,buffer_size);
	sem_init(&full_sema,2,0);
	int i;
	for(i=0;i<buffer_size;i++)
	{
		buffer[i]=0;
	}
	pthread_mutex_init(&mutex_lock,NULL);
	pthread_t thread1[buffer_size];
	pthread_t thread2[buffer_size];
	int m=0;
	for(m=0;m<buffer_size;m++)
	{
		pthread_create(&thread1[m],NULL,thread_producer,NULL);
		pthread_create(&thread2[m],NULL,thread_consumer,NULL);
	}
	
	for(m=0;m<buffer_size;m++)
	{
		pthread_join(thread1[m],NULL);
		pthread_join(thread2[m],NULL);
	}
	}
	else
	{
		printf("\nBuffer size exceeded the limit .\nPlease enter the buffer size again and <=20.\n");
		goto x;
	}

 }
void *thread_producer()
 {
	sem_wait ( &empty_sema );
	pthread_mutex_lock ( &mutex_lock );
	sleep(1);
	int i;
	for(i=0;buffer[i]!=0;i++)
	{
	}
	buffer[i] = rand()%99;
	printf("\nPRODUCER is producing the data which is :- %d .\n",buffer[i]);
	pthread_mutex_unlock ( &mutex_lock );
	sem_post ( &full_sema );
 }
void *thread_consumer()
 {
	sem_wait ( &full_sema );
	pthread_mutex_lock ( &mutex_lock );
	sleep(1);
	int i;
	for(i=15;buffer[i]==0;i--)
	{
	}
	printf("\n---Consumer is consuming the data from the buffer that is :- %d .\n",buffer[i]);
	buffer[i]=0;
	pthread_mutex_unlock ( &mutex_lock );
	sem_post ( &empty_sema );
 }
