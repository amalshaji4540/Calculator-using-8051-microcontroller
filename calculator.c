#include<8051.h>

void _mcs51_genRAMCLEAR(void)
{
}



typedef struct{
  unsigned char scan;
  unsigned char ascii;
  unsigned char disp;
}s_keymap;

s_keymap keymap[] = {
  /*scan ascii disp*/
  { 0xb7, 1, 0x06 }, /*0 1 1*/
  { 0xd7, 2, 0x5B }, /*1 0 1*/
  { 0xe7, 3, 0x4F }, /*1 1 0*/
  { 0xbb, 4, 0x66 },
  { 0xdb, 5, 0x6D },
  { 0xeb, 6, 0x7D },
  { 0xbd, 7, 0x07 },
  { 0xdd, 8, 0x7F },
  { 0xed, 9, 0x6F },
  { 0xbe, '*', 0x77 },
  { 0xde, 0, 0x3F },
  { 0xee, '#', 0x7C },
};

void DELAY_ms(unsigned int ms_Count) //function used for getting delay
{
    unsigned int i, j;
    for (i = 0; i < ms_Count; i++) 
    {
        for (j = 0; j < 100; j++);
    }
}  

void display(unsigned char num[]) //fuction used for displaying the array of numbers
{

  {
    P3=0x00;
    P1=num[0];
    DELAY_ms(1);
    P3=0x0F;
    P1=num[1];
    DELAY_ms(1);
    P3=0xF0;
    P1=num[2];
    DELAY_ms(1);
    P3=0xFF;
    P1=num[3];
    DELAY_ms(1); 
  }
    
}

unsigned char inputnum(unsigned char check) // function used for inputing the number from keypad and the function will return the value from keyboard 
{
  unsigned char i;
  unsigned char num_to_display[4]={0xFF,0xFF,0xFF,0xFF};
  unsigned char temp_value[4]={0,0,0,0};
  unsigned char real_value[4]={0,0,0,0};
  unsigned char j=0;
  unsigned char number=0;
  while(1)
  {   
    P0 = 0xf0;
    while(P0 == 0xf0)
    {
       display(num_to_display); 
    }
    display(num_to_display); 
    for(i=0; i<sizeof(keymap)/sizeof(s_keymap); i++)
    {
        P0 = keymap[i].scan | 0xf0;
        if(P0 == keymap[i].scan) 
        {
            num_to_display[j] = ~(keymap[i].disp);
            temp_value[j] = keymap[i].ascii;
            if((temp_value[j]!='*')&&(temp_value[j]!='#'))
            {
            real_value[j]=keymap[i].ascii;
            }
            if((temp_value[j]=='*'&&check==1)||(temp_value[j]=='#'&&check==2))
            {
              number = real_value[0]+(10*real_value[1])+(100*real_value[2])+(1000*real_value[3]);
              return number;
            }
            if(j==3)
            {
                j=0;
            }
            else
            {
                j=j+1;
            }
        }
    } 
 }
}

unsigned char operationfinder(void)  // functin used for finding the operation
{   
    unsigned char op_to_diplay[4]={0xFF,0xFF,0xFF,0xFF},j=0,i=0,flag=0;
    while (1)
    {
        P0 = 0xf0;
        while(P0 == 0xf0)
        {
          display(op_to_diplay);   
        }
        {
            for(i=0; i<sizeof(keymap)/sizeof(s_keymap); i++)
            {
                P0 = keymap[i].scan | 0xf0;
                if(P0 == 0xbe) 
                {
                    flag=flag+1;
                    op_to_diplay[j] = ~(keymap[i].disp);
                    display(op_to_diplay);   
                    j=j+1;
                }
                if(P0==0xb7||P0==0xd7 ||P0== 0xe7 ||P0== 0xbb ||P0== 0xdb ||P0== 0xeb ||P0== 0xbd ||P0== 0xdd ||P0== 0xed ||P0== 0xde)
                {
                   return flag;
                }
            }
            
        }
    }
}

void add(unsigned char num1) //fuction used for addition
{
    unsigned char num2;
    unsigned char j;
    unsigned char result;
    unsigned char k,mod[4],dis[4]={0xFF,0xFF,0xFF,0xFF},temp;
    num2=inputnum(2);
    result = num1+num2;
    for(k=0;k<4;k++)
    {   
        temp=result;
        mod[k] = temp % 10;  
        for(j=0; j<sizeof(keymap)/sizeof(s_keymap); j++)
        {
            if(mod[k]== keymap[j].ascii) 
            {
                dis[k] = ~(keymap[j].disp);
            }
        }  
        result = result / 10;
    }
    while(1)
    {
    display(dis);
    }              
}

void sub(unsigned char num1)  //function used for sustraction
{
    unsigned char num2;
    unsigned char j;
    unsigned char result;
    unsigned char k,mod[4],dis[4]={0xFF,0xFF,0xFF,0xFF},temp;
    num2=inputnum(2);
    result = num1-num2;
    for(k=0;k<4;k++)
    {   
        temp=result;
        mod[k] = temp % 10;  
        for(j=0; j<sizeof(keymap)/sizeof(s_keymap); j++)
        {
            if(mod[k]== keymap[j].ascii) 
            {
                dis[k] = ~(keymap[j].disp);
            }
        }  
        result = result / 10;
    }
    while(1)
    {
    display(dis);
    }              
}

void mul(unsigned char num1) //function used for multiplication
{
    unsigned char num2;
    unsigned char j;
    unsigned char result;
    unsigned char k,mod[4],dis[4]={0xFF,0xFF,0xFF,0xFF},temp;
    num2=inputnum(2);
    result = num1*num2;
    for(k=0;k<4;k++)
    {   
        temp=result;
        mod[k] = temp % 10;  
        for(j=0; j<sizeof(keymap)/sizeof(s_keymap); j++)
        {
            if(mod[k]== keymap[j].ascii) 
            {
                dis[k] = ~(keymap[j].disp);
            }
        }  
        result = result / 10;
    }
    while(1)
    {
    display(dis);
    }              
}

void div(unsigned char num1)  //function used for division
{
    unsigned char num2;
    unsigned char j;
    unsigned char result;
    unsigned char k,mod[4],dis[4]={0xFF,0xFF,0xFF,0xFF},temp;
    num2=inputnum(2);
    result = num1/num2;
    for(k=0;k<4;k++)
    {   
        temp=result;
        mod[k] = temp % 10;  
        for(j=0; j<sizeof(keymap)/sizeof(s_keymap); j++)
        {
            if(mod[k]== keymap[j].ascii) 
            {
                dis[k] = ~(keymap[j].disp);
            }
        }  
        result = result / 10;
    }
    while(1)
    {
    display(dis);
    }              
}

void main(void) // main function
{
    unsigned char num1;
    unsigned char m=0;
    unsigned char flag=0;
    while(1)
    {
        num1=inputnum(1);
        flag=operationfinder();
        if(flag == 1)
        {
          add(num1);
        }
        else if(flag==2)
        {
          sub(num1);
        }
         else if(flag==3)
        {
          mul(num1);
        } 
        else
        {
          div(num1);
        }
    }
}
