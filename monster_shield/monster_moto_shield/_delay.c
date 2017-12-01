void delay_us(unsigned int us)
{
    unsigned int i;

    while(us--)
    {
      asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
      asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
      asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
      asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
      asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
      asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
      asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
      asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
      //asm("nop\n");
    }
}

void delay_ms(unsigned int ms)
{
    unsigned int i;

    while(ms--)
    {
        for(i=0;i<999;i++)
        {
         asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
         asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
         asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
         asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
         asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
         asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
         asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
         asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");asm("nop\n");
         asm("nop\n");asm("nop\n");
        }
    }
}

