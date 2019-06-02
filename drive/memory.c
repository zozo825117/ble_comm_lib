#include "memory.h"
#include <string.h>
#if defined(NETSTACK_ROUTE)
#define MEMORY_POOL_MAX 100
#else
#define MEMORY_POOL_MAX 90
#endif
volatile u8 data memory_pool[MEMORY_POOL_MAX];//内存池
u8 user_len; //已使用长度
/**
 * 功能：内存初始化
 * 参数：无
 * 返回：无
 */
void memory_init(void)
{
	memset(memory_pool,0,MEMORY_POOL_MAX);
	user_len=0;
}

/**
 * 功能：动态分配内存
 * 参数：ptr---首地址变量
 * 参数：len---大小
 * 返回：成功返回 0 ，否则返回 1
 */
void  *memory_malloc(u8 len)
{
	if(MEMORY_POOL_MAX-user_len < len)
		return 0;
	user_len += len;
	return &memory_pool[user_len-len];
}


/**
 * 功能：内存释放
 * 参数：ptr---首地址，len---大小
 * 返回：成功返回 0 ，否则返回 1
 */
u8 memory_free(void *ptr,u8 len)
{
	memset(ptr,0,len);
	user_len -=len;
	return 0;
}




