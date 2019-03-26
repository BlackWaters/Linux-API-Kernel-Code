#include <linux/mm.h>
#include <linux/highmem.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <asm/atomic.h>
#include <linux/rwsem.h>
#include <asm/uaccess.h>
#include "DriverFileOperations.h"
#include "DriverMain.h"
#include "ToolFunctions.h"
#include <linux/mutex.h>

//int cnt=0;
//DEFINE_MUTEX(mymutex);
DEFINE_PER_CPU(int,cnt);


int DriverOpen(struct inode *pslINode, struct file *pslFileStruct)
{ 
	//DEBUG_PRINT(DEVICE_NAME ": open invoked, do nothing\n");
	return 0;
}

int DriverClose(struct inode *pslINode, struct file *pslFileStruct)
{
	//DEBUG_PRINT(DEVICE_NAME ": close invoked, do nothing\n");
	return 0;
}

ssize_t DriverRead(struct file *pslFileStruct, char __user *pBuffer, size_t nCount, loff_t *pOffset)
{
	DEBUG_PRINT(DEVICE_NAME ": read invoked, do nothing\n");
	return 0;
}

ssize_t DriverWrite(struct file *pslFileStruct, const char __user *pBuffer, size_t nCount, loff_t *pOffset)
{
    printk(pBuffer);
	DEBUG_PRINT(DEVICE_NAME ": write invoked, do nothing\n");
	return 0;
}

long DriverIOControl(struct file *pslFileStruct, unsigned int uiCmd, unsigned long ulArg)
{
    //unsigned int a=(int) uiCmd,b=(int) ulArg,c;
    //c=a+b;
    //printk("The Answer is %u\n",c);
    //mutex_lock(&mymutex);
    DEBUG_PRINT("The uiCmd: %d\n",uiCmd);
    if (uiCmd==101)
    {
        int ret=0,i;
        for_each_online_cpu(i)
        {
            int ptr=per_cpu(cnt,i);
            ret+=ptr;
        }
        DEBUG_PRINT("The total cnt is : %d\n",ret);
        return ret;
    }
    else if (uiCmd==0)
    {
        int i;
        for_each_online_cpu(i)
        {
            int ptr=per_cpu(cnt,i);
            ptr=0;
        }
        DEBUG_PRINT("Clear cnt.\n");
    }
    else 
    {
        int ptr=get_cpu_var(cnt);
        ptr++;
        put_cpu_var(ptr);
        DEBUG_PRINT("Inc cnt success,cnt: %d\n",ptr); 
    }
	//DEBUG_PRINT(DEVICE_NAME ": ioctl invoked, do nothing\n");
    //mutex_unlock(&mymutex);
	return cnt;
}

int DriverMMap(struct file *pslFileStruct, struct vm_area_struct *pslVirtualMemoryArea)
{
	DEBUG_PRINT(DEVICE_NAME ": mmap invoked, do nothing\n");
	return 0;
}



