#include <pthread.h>
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
pthread_cond_t empty;
pthread_cond_t fill;
pthread_mutex_t m;

int main(){
	pthread_t tid1, tid2;
	pthread_cond_init(&empty, NULL);
	pthread_cond_init(&fill, NULL);
	pthread_mutex_init(&m, NULL);
	pthread_create(&tid1, NULL, producer, NULL);
	pthread_create(&tid2, NULL, consumer, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	if(x!=0)
		printf("BOOM! counter=%d\n", x);
	else
		printf("OK counter=%d\n", x);

	pthread_cond_destroy(&empty);
	pthread_cond_destroy(&fill);
	pthread_mutex_destroy(&m);
}

/*thread routine*/
void * producer(void *arg){
int i, val;
for(i=0; i<ITER; i++){
	pthread_mutex_lock(&m);
	while (x==30)
		pthread_cond_wait(&empty, &m);
	val = x;
	printf("%u: %d\n", (unsigned int)pthread_self(), val);
	put(val);
	x = val+1;
	pthread_cond_signal(&fill);
	pthread_mutex_unlock(&m);
}
return NULL;
}

void *consumer(void *arg){
int i, val;
for(i=0; i<ITER; i++){
	pthread_mutex_lock(&m);
	while(x == 0)
		pthread_cond_wait(&fill, &m);	
	val = x;
	printf("%u: %d\n", (unsigned int)pthread_self(), val);
	get();
	x = val-1;
	pthread_cond_signal(&empty);
	pthread_mutex_unlock(&m);
}
return NULL;
}

void put(int item){
        buffer[fill_cnt] = item;
        fill_cnt = (fill_cnt+1)%MAX;
        return;
}

int get(){
        int tmp = buffer[use_cnt];
        use_cnt = (use_cnt + 1)%MAX;
        return tmp;
}

