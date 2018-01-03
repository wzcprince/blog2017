


#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#include <stdio.h>        // for printf
#include <stdlib.h>        // for exit
#include <string.h>        // for bzero

#include <netinet/tcp.h>  // for SOL_TCP

#include <unistd.h> // for usleep
#include <time.h> // for nanosleep

#include <pthread.h>
#include <errno.h>


/* 静态TLB变量 */
__thread uintptr_t static_tls = 0x8888;

void* new_thread_routine(void* param)
{
	static_tls = 0x6666;
	printf ("new thread's are running static_tls %p\n", (void *)static_tls );
    return (void*)static_tls;
}

void sleep_second(unsigned sec)
{
	//usleep(1000); // obsolete  https://linux.die.net/man/3/usleep
    struct timespec interval;
    interval.tv_sec = sec; // 秒
    interval.tv_nsec = 0; // nano 纳秒
    struct timespec remain = {0,0};
    
    while (-1 == nanosleep(&interval, &remain) && errno == EINTR)
    {
        printf ("nanosleep is interrupted by a signal handler\n");
        interval = remain;
    }
    
}

#define thread_count 10000
pthread_t arr_thread[thread_count];

int main(int argc, char **argv)
{
	static pthread_key_t thread_key1;
    void* result = NULL;
    
	pthread_key_create (&thread_key1, NULL);  

	/* 测试一下 pthread_self 的返回值就是TCB地址 也就是 fs:0 的值 */
	unsigned int b = 0;  
	asm volatile("movl %%fs:0,%0"  
		:"=r"(b)  /* output */      
		);
	printf ("pthread_self() == 0x%x\nfs:0 == 0x%x\n", (unsigned int)pthread_self(), b );

    for (int i = 0; i<thread_count; i++)
    {
        pthread_create(arr_thread + i, NULL, new_thread_routine, NULL);
    }
    
	printf ("main thread sleeping\n");
    sleep_second(15);

	printf ("main thread start pthread_join\n");
    
    for (int i = 0; i<thread_count; i++)
    {
        pthread_join(arr_thread[i], &result);
    }

	printf ("main thread end pthread_join\n");
    sleep_second(15);    
    
	printf ("main thread's static_tls %p\n", (void *)static_tls );
	printf ("new  thread's static_tls %p\n", (void *)result );

	
}


