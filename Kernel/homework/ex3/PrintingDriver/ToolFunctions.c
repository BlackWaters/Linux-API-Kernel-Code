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
    pgd_t *pgd;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *pte;

    DEBUG_PRINT("mm->pgd : %lx\n",current->mm->pgd);
    pgd = pgd_offset(current->mm, addr);
    DEBUG_PRINT("pgd : %lx\n",pgd);
    pud = pud_offset((p4d_t*)  pgd, addr);
    DEBUG_PRINT("pud : %lx\n",pud);
    pmd = pmd_offset(pud, addr);
    DEBUG_PRINT("pmd : %lx\n",pmd);
    pte = pte_offset_kernel(pmd, addr);
    DEBUG_PRINT("pte : %lx\n pte->pte : %lx\n",pte,pte->pte);

    unsigned long mask=0x000ffffffffff000UL;
    //DEBUG_PRINT("mask : %lx\n",mask);
    unsigned long offset=0x0000000000000fffUL & addr;
    //DEBUG_PRINT("offset : %lx\n",offset);
    unsigned long ret=offset | ((unsigned long) (pte->pte) & mask ) ;
    //DEBUG_PRINT("pte address : %lx\n", pte->pte & PAGE_MASK);
    return ret;
}
