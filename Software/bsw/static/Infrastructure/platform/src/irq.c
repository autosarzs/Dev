


__asm
void irq_Enable(void)
{
    CPSIE i
}

__asm
void irq_Disable(void)
{
    CPSID i
}
