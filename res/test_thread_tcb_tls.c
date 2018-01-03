


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
__thread int static_tls = 123;

void* new_thread_routine(void* param)
{
	static_tls = 6666;
}

int main(int argc, char **argv)
{
	static pthread_key_t thread_key1;  
	pthread_key_create (&thread_key1, NULL);  

	/* 测试一下 pthread_self 的返回值就是TCB地址 也就是 fs:0的值 */
	unsigned int b = 0;  
	asm volatile("movl %%fs:0,%0"  
		:"=r"(b)  /* output */      
		);
	printf ("0x%x, b:0x%x\n", (unsigned int)pthread_self(), b );

	pthread_t newthread;
	pthread_create(&newthread, NULL, new_thread_routine, NULL);

	usleep(1000);
	printf ("static_tls %d\n", static_tls );

	
}


