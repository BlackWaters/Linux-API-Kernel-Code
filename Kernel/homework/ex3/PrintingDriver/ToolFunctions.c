#include <linux/string.h>
#include <linux/sched.h>
#include "ToolFunctions.h"
#include <linux/mm.h>

void MEM_PRINT(unsigned long addr, unsigned long size)
{
	unsigned long i, j;
	char AddrBuf[64];
	char DataBuf[32];
	unsigned char *p = (unsigned char *)addr;

	for(i = 0; i < size; )
	{
		snprintf(AddrBuf, 64, "%lx:\t", (unsigned long)p);

		for(j = 0; j < 8; j++)
		{  
			if(i + j >= size)
				break;

			if(*(p+j) <= 0xf)
				snprintf(DataBuf + j * 3, 32 - j * 3, "0%x ", *(p+j));
			else
				snprintf(DataBuf + j * 3, 32 - j * 3, "%x ", *(p+j));
		}

		strcat(AddrBuf, DataBuf);

		printk("%s\n", AddrBuf);

		i = i + 8;
		p = p + 8;
	}
}

unsigned long ShowPyhsicADDR(unsigned long addr)
{
    p4d_t *pgd;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *pte;

    pgd = p4d_offset((current->mm)->pgd, addr);
    
    pud = pud_offset(pgd, addr);

    pmd = pmd_offset(pud, addr);

    pte = pte_offset_kernel(pmd, addr);

    unsigned long offset=0x0000000000000fffUL & addr;
    unsigned long ret=offset+pte->pte;
    return ret;
}
