


#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#include <stdio.h>        // for printf
#include <stdlib.h>        // for exit
#include <string.h>        // for bzero

#include <netinet/tcp.h>  // for SOL_TCP

#include <unistd.h> // for usleep

#include <pthread.h>

/* 静态TLB变量 */
__thread uintptr_t static_tls = 0x8888;

void* new_thread_routine(void* param)
{
	static_tls = 0x6666;
	printf ("new thread's static_tls %p\n", (void *)static_tls );
    return (void*)static_tls;
}

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

	pthread_t newthread;
	pthread_create(&newthread, NULL, new_thread_routine, NULL);

	pthread_join(newthread, &result);

	//usleep(1000);
	printf ("main thread's static_tls %p\n", (void *)static_tls );
	printf ("new  thread's static_tls %p\n", (void *)result );

	
}


