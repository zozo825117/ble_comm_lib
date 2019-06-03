#include "memory.h"
#include <string.h>
#if defined(NETSTACK_ROUTE)
#define MEMORY_POOL_MAX 100
#else
#define MEMORY_POOL_MAX 90
#endif
volatile u8 data memory_pool[MEMORY_POOL_MAX];//�ڴ��
u8 user_len; //��ʹ�ó���
/**
 * ���ܣ��ڴ��ʼ��
 * ��������
 * ���أ���
 */
void memory_init(void)
{
	memset(memory_pool,0,MEMORY_POOL_MAX);
	user_len=0;
}

/**
 * ���ܣ���̬�����ڴ�
 * ������ptr---�׵�ַ����
 * ������len---��С
 * ���أ��ɹ����� 0 �����򷵻� 1
 */
void  *memory_malloc(u8 len)
{
	if(MEMORY_POOL_MAX-user_len < len)
		return 0;
	user_len += len;
	return &memory_pool[user_len-len];
}


/**
 * ���ܣ��ڴ��ͷ�
 * ������ptr---�׵�ַ��len---��С
 * ���أ��ɹ����� 0 �����򷵻� 1
 */
u8 memory_free(void *ptr,u8 len)
{
	memset(ptr,0,len);
	user_len -=len;
	return 0;
}




