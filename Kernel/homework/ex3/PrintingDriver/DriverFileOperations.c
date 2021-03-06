#include <linux/mm.h>
#include <linux/highmem.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <asm/atomic.h>
#include <linux/rwsem.h>
#include <asm/uaccess.h>
#include <asm/desc.h>
#include <asm/msr.h>
#include "DriverFileOperations.h"
#include "DriverMain.h"
#include "ToolFunctions.h"
#include <linux/sched.h>

unsigned long gdt_addr1,gdt_addr2;
char Ptr[20]="Hello World.";
/*
unsigned long ShowPyhsicADDR(unsigned long addr)
{
    pgd_t *pgd;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *pte;

    pgd = pgd_offset(current->mm,addr);

    pud = pud_offset(pgd,addr);
    
    pmd=pmd_offset(pud,addr);
    pte=pte_offset_kernel(pmd,addr);

    unsigned long offset=0x0000000000000fffUL & addr;
    unsigned long ret=offset+pte->pte;
    return ret;
}*/

int DriverOpen(struct inode *pslINode, struct file *pslFileStruct)
{
	DEBUG_PRINT(DEVICE_NAME ": open invoked, do nothing\n");
	return 0;
}

int DriverClose(struct inode *pslINode, struct file *pslFileStruct)
{
	DEBUG_PRINT(DEVICE_NAME ": close invoked, do nothing\n");
	return 0;
}

ssize_t DriverRead(struct file *pslFileStruct, char __user *pBuffer, size_t nCount, loff_t *pOffset)
{
	DEBUG_PRINT(DEVICE_NAME ": read invoked, do nothing\n");
	return 0;
}

ssize_t DriverWrite(struct file *pslFileStruct, const char __user *pBuffer, size_t nCount, loff_t *pOffset)
{
	unsigned long gdt_addr;
	unsigned short cs, ds, ss,gs;
	unsigned long desc;
	int i;
	unsigned int high, low;
	unsigned int high1, low1;
	char gdtr[10] = {0};
    DEBUG_PRINT( "paddress of string : %lx \n",ShowPyhsicADDR(&Ptr));


	DEBUG_PRINT(DEVICE_NAME ": write invoked, do nothing\n");
    DEBUG_PRINT("String val address: %x\n",&Ptr);


    unsigned long cr3;
    asm volatile("mov %%cr3, %0\n\t" : "=r" (cr3), "=m" (__force_order));


	asm volatile ("mov %%cs, %0 \n\t" : "=m"(cs));
	asm volatile ("mov %%ds, %0 \n\t" : "=m"(ds));
	asm volatile ("mov %%ss, %0 \n\t" : "=m"(ss));
    asm volatile ("mov %%gs ,%0 \n\t" : "=m"(gs));

	DEBUG_PRINT("cs: %x\n", cs);
	DEBUG_PRINT("ds: %x\n", ds);
	DEBUG_PRINT("ss: %x\n", ss);
    DEBUG_PRINT("gs: %x\n", gs);

	asm volatile ("sgdt %0\n\t" : "=m"(gdtr) : :);

	DEBUG_PRINT("gdtr is: \n");
	MEM_PRINT((unsigned long)gdtr, 10);

	gdt_addr = (*(unsigned long *)(gdtr + 2));

	DEBUG_PRINT(DEVICE_NAME " GDT: %lx:\n", gdt_addr);
	MEM_PRINT(gdt_addr, 8*16);

	for(i = 0; i < 16; i++)
	{
		asm volatile("movq %%gs:%P1, %0" : "=r"(desc) : "m"(*(((unsigned long *)(&gdt_page)) + i)));
		DEBUG_PRINT(DEVICE_NAME " GDT[%d]: %lx:\n", i, desc);
	}

	asm volatile ("mov $0xc0000101, %%ecx \n\t"
				  "rdmsr \n\t" : "=d"(high), "=a"(low) : : "%ecx", "memory");

	DEBUG_PRINT(DEVICE_NAME " gs base: 0x%x_%x\n", high, low);
	DEBUG_PRINT(DEVICE_NAME " gdt_page offset: %lx:\n", (unsigned long)(&gdt_page));

	rdmsr(MSR_GS_BASE, low1, high1);

	DEBUG_PRINT(DEVICE_NAME " gs base 1 : 0x%x_%x\n", high1, low1);
    gdt_addr1=gdt_addr;
    gdt_addr2=(((unsigned long)high1) << 32) | low;
    gdt_addr2+=((unsigned long) (&gdt_page))*8 ;
    
    //unsigned long Phy1=ShowPyhsicADDR(gdt_addr1);
	return 0;

}

long DriverIOControl(struct file *pslFileStruct, unsigned int uiCmd, unsigned long ulArg)
{
	DEBUG_PRINT(DEVICE_NAME ": ioctl invoked, do nothing\n");
    DEBUG_PRINT("GDT_ADDR1 : %lx\n",gdt_addr1);
    DEBUG_PRINT("GDT_ADDR2 : %lx\n",gdt_addr2);
    
    unsigned long phy_addr1=ShowPyhsicADDR(gdt_addr1);
    DEBUG_PRINT("Pyh_GDT_ADDR1 : %lx\n",phy_addr1);
    
    unsigned long phy_addr2=ShowPyhsicADDR(gdt_addr2);
    DEBUG_PRINT("Pyh_GDT_ADDR2 : %lx\n",phy_addr2);
	return 0;
}

int DriverMMap(struct file *pslFileStruct, struct vm_area_struct *pslVirtualMemoryArea)
{
	DEBUG_PRINT(DEVICE_NAME ": mmap invoked, do nothing\n");
	return 0;
}
