#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#define ITER 100000
#define MAX 30

void *producer(void *arg);
void *consumer(void *arg);
void put();
int get();
int buffer[MAX];
int fill_cnt = 0;
int use_cnt = 0;
int x = 0;
sem_t m, fill, empty;

int main(){
	pthread_t tid1, tid2;
	sem_init(&m, 0, 1);
	sem_init(&fill, 0, 0);
	sem_init(&empty, 0, MAX);
	pthread_create(&tid1, NULL, producer, NULL);
	pthread_create(&tid2, NULL, consumer, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	if(x!=0)
		printf("BOOM! counter=%d\n",x);
	else 
		printf("OK counter=%d\n", x);
	sem_destroy(&m);
}

void *producer(void *arg){
int i, val;
for(i = 0; i<ITER; i++){
	sem_wait(&empty);
	sem_wait(&m);
	val = x;
	printf("%u: %d\n", (unsigned int)pthread_self(), val);
	put(val);
	x = val+1;
	sem_post(&m);
	sem_post(&fill);
}
return NULL;
}

void *consumer(void *arg){
int i, val;
for(i=0; i<ITER; i++){
	sem_wait(&fill);
	sem_wait(&m);
	val = x;
	printf("%u: %d\n", (unsigned int)pthread_self(), val);
        get();
	x = val-1;
        sem_post(&m);
	sem_post(&empty);
}
return NULL;
}

void put(int item){
	buffer[fill_cnt] = item;
	fill_cnt = (fill_cnt + 1)%MAX;
	return;
}

int get(){
	int tmp = buffer[use_cnt];
	use_cnt = (use_cnt + 1)%MAX;
	return tmp;
}
