#include<avr/io.h>
#define F_CPU 8000000
#include<util/delay.h>
#define lcd PORTB
#include<lcd.h>
#include <avr/interrupt.h>	

#define pin1 PA0
#define pin2 PA1
#define pin3 PA2
#define pin4 PA3
#define pin5 PA4
#define pin6 PA5
#define pin7 PA6
#define pin8 PC6
#define pin9 PC5
#define pin10 PC4
#define pin11 PC3
#define pin12 PC2
#define pin13 PC1
#define pin14 PC0

int function,state=0,idtt=0;

int working_7420[2]={0,0};
int working_7421[2]={0,0};
int working_7425[2]={0,0};
int working_7411[3]={0,0,0};
int working_7410[3]={0,0,0};
int working_7427[3]={0,0,0};
int working_7400[4]={0,0,0,0};
int working_7486[4]={0,0,0,0};
int working_7402[4]={0,0,0,0};
int working_7408[4]={0,0,0,0};
int working_7432[4]={0,0,0,0};

int checkFourInput();
int checkThreeInput();
int checkTwoInput();

void checkFourNAND_1();
void checkFourAND_1();
void checkFourNOR_1();
void checkThreeAND_1();
void checkThreeNAND_1();
void checkThreeNOR_1();
void checkTwoNAND_1();
void checkTwoXOR_1();
void checkTwoNOR_1();
void checkTwoAND_1();
void checkTwoOR_1();

int checkFourNAND_2(int pin_1,int pin_2,int pin_3,int pin_4,int pin_5);
int checkFourAND_2(int pin_1,int pin_2,int pin_3,int pin_4,int pin_5);
int checkFourNOR_2(int pin_1,int pin_2,int pin_3,int pin_4,int pin_5);
int checkThreeAND_2(int pin_1,int pin_2,int pin_3,int pin_4);
int checkThreeNAND_2(int pin_1,int pin_2,int pin_3,int pin_4);
int checkThreeNOR_2(int pin_1,int pin_2,int pin_3,int pin_4);
int checkTwoNAND_2(int pin_1,int pin_2,int pin_3);
int checkTwoXOR_2(int pin_1,int pin_2,int pin_3);
int checkTwoNOR_2(int pin_1,int pin_2,int pin_3);
int checkTwoAND_2(int pin_1,int pin_2,int pin_3);
int checkTwoOR_2(int pin_1,int pin_2,int pin_3);

void commonfour(char str_1[],char str_2[],int p[]);
void commonthree(char str_1[],char str_2[],int p[]);
void commontwo(char str_1[],char str_2[],int p[]);

ISR(INT0_vect)
{
	function=1;
	state=1;
}
ISR(INT1_vect)
{
	function=2;
	state=1;
}	

int main()
{
	DDRD=0;
	PORTD=0xff;
	DDRB=0xff;
	DDRC=0xff;
	DDRA=0xff;
	lcd_begin();
	GICR=((1<<INT0) + (1<<INT1));
	MCUCR=0b01010000;
	sei();
	lcd_cmd(0x80);
	lcd_string("WELCOME TO");
	lcd_cmd(0xc0);
	lcd_string("AlphA's ICTESTER");
	_delay_ms(1500);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_string("TEST PROCESS");
	lcd_cmd(0xc0);
	lcd_string("STARTING...");
	_delay_ms(1500);
	lcd_cmd(0x80);
	lcd_cmd(0x01);
	lcd_string("STARTED");
	_delay_ms(1000);
	lcd_cmd(0x01);
	while(1)
	{
		int check=0;
		check=checkFourInput();
		if(check==1)
		{	
			if(idtt==0)
			{
				lcd_cmd(0x80);
				lcd_string("PRESS");
				lcd_cmd(0xc1);
				lcd_string("IDENTIFY/TEST");
				idtt=1;
			}
			continue;
		}
		check=checkThreeInput();
		if(check==1)
		{
			if(idtt==0)
			{
				lcd_cmd(0x80);
				lcd_string("PRESS");
				lcd_cmd(0xc1);
				lcd_string("IDENTIFY/TEST");
				idtt=1;
			}
			continue;
		}
		check=checkTwoInput();
		if(check==1)
		{
			if(idtt==0)
			{
				lcd_cmd(0x80);
				lcd_string("PRESS");
				lcd_cmd(0xc1);
				lcd_string("IDENTIFY/TEST");
				idtt=1;
			}
			continue;
		}
		lcd_cmd(0x80);
		lcd_string("There seems");
		lcd_cmd(0xc0);
		lcd_string("to be a problem");
	}
}

int checkFourInput()
{
	checkFourNAND_1();
	if(working_7420[0]==1 || working_7420[1]==1)
	{
		commonfour("IC 7420 (4 i/p)","Dual-NAND Gate",working_7420);
		return 1;
	}
	checkFourAND_1();
	if(working_7421[0]==1 || working_7421[1]==1)
	{
		commonfour("IC 7421 (4 i/p)","Dual-AND Gate",working_7421);
		return 1;
	}
	checkFourNOR_1();
	if(working_7425[0]==1 || working_7425[1]==1)
	{
		commonfour("IC 7425 (4 i/p)","Dual-NOR Gate",working_7425);
		return 1;
	}
	return 0;
}
int checkThreeInput()
{
	checkThreeAND_1();
	if(working_7411[0]==1 || working_7411[1]==1 || working_7411[2]==1)
	{
		commonthree("IC 7411 (3 i/p)","Tri-AND Gate",working_7411);
		return 1;
	}
	checkThreeNAND_1();
	if(working_7410[0]==1 || working_7410[1]==1 || working_7410[2]==1)
	{
		commonthree("IC 7410 (3 i/p)","Tri-NAND Gate",working_7410);
		return 1;
	}
	checkThreeNOR_1();
	if(working_7427[0]==1 || working_7427[1]==1 || working_7427[2]==1)
	{
		commonthree("IC 7427 (3 i/p)","Tri-NOR Gate",working_7427);
		return 1;
	}
	return 0;
}
int checkTwoInput()
{
	checkTwoNAND_1();
	if(working_7400[0]==1 || working_7400[1]==1 || working_7400[2]==1 || working_7400[3]==1)
	{
		commontwo("IC 7400 (2 i/p)","Quad-NAND Gate",working_7400);
		return 1;
	}
	checkTwoXOR_1();
	if(working_7486[0]==1 || working_7486[1]==1 || working_7486[2]==1 || working_7486[3]==1)
	{
		commontwo("IC 7486 (2 i/p)","Quad-XOR Gate",working_7486);
		return 1;
	}
	checkTwoNOR_1();
	if(working_7402[0]==1 || working_7402[1]==1 || working_7402[2]==1 || working_7402[3]==1)
	{
		commontwo("IC 7402 (2 i/p)","Quad-NOR Gate",working_7402);
		return 1;
	}
	checkTwoAND_1();
	if(working_7408[0]==1 || working_7408[1]==1 || working_7408[2]==1 || working_7408[3]==1)
	{
		commontwo("IC 7408 (2 i/p)","Quad-AND Gate",working_7408);
		return 1;
	}
	checkTwoOR_1();
	if(working_7432[0]==1 || working_7432[1]==1 || working_7432[2]==1 || working_7432[3]==1)
	{
		commontwo("IC 7432 (2 i/p)","Quad-OR Gate",working_7432);
		return 1;
	}
	return 0;
}

void checkFourNAND_1()
{
	int gate1=checkFourNAND_2(pin1,pin2,pin4,pin5,pin6); 
	int gate2=checkFourNAND_2(pin13,pin12,pin10,pin9,pin8); 
	if(gate1==1)
	{ 
		working_7420[0]=1; 
	} 
	if(gate2==1)
	{
		working_7420[1]=1;
	}
}
void checkFourAND_1()
{
	int gate1=checkFourAND_2(pin1,pin2,pin4,pin5,pin6); 
	int gate2=checkFourAND_2(pin13,pin12,pin10,pin9,pin8); 
	if(gate1==1)
	{ 
		working_7421[0]=1; 
	} 
	if(gate2==1)
	{
		working_7421[1]=1;
	}
}
void checkFourNOR_1()
{
	int gate1=checkFourNOR_2(pin1,pin2,pin4,pin5,pin6); 
	int gate2=checkFourNOR_2(pin13,pin12,pin10,pin9,pin8); 
	if(gate1==1)
	{ 
		working_7425[0]=1; 
	} 
	if(gate2==1)
	{
		working_7425[1]=1;
	}
}
void checkThreeAND_1()
{
	int gate1=checkThreeAND_2(pin1,pin2,pin13,pin12); 
	int gate2=checkThreeAND_2(pin3,pin4,pin5,pin6);
	int gate3=checkThreeAND_2(pin11,pin10,pin9,pin8);
	if(gate1==1)
	{ 
		working_7411[0]=1; 
	} 
	if(gate2==1)
	{
		working_7411[1]=1;
	}
	if(gate3==1)
	{
		working_7411[2]=1;
	}
}
void checkThreeNAND_1()
{
	int gate1=checkThreeNAND_2(pin1,pin2,pin13,pin12); 
	int gate2=checkThreeNAND_2(pin3,pin4,pin5,pin6);
	int gate3=checkThreeNAND_2(pin11,pin10,pin9,pin8);
	if(gate1==1)
	{ 
		working_7410[0]=1; 
	} 
	if(gate2==1)
	{
		working_7410[1]=1;
	}
	if(gate3==1)
	{
		working_7410[2]=1;
	}
}
void checkThreeNOR_1()
{
	int gate1=checkThreeNOR_2(pin1,pin2,pin13,pin12); 
	int gate2=checkThreeNOR_2(pin3,pin4,pin5,pin6);
	int gate3=checkThreeNOR_2(pin11,pin10,pin9,pin8);
	if(gate1==1)
	{ 
		working_7427[0]=1; 
	} 
	if(gate2==1)
	{
		working_7427[1]=1;
	}
	if(gate3==1)
	{
		working_7427[2]=1;
	}
}
void checkTwoNAND_1()
{
	int gate1=checkTwoNAND_2(pin1,pin2,pin3); 
	int gate2=checkTwoNAND_2(pin4,pin5,pin6);
	int gate3=checkTwoNAND_2(pin10,pin9,pin8);
	int gate4=checkTwoNAND_2(pin13,pin12,pin11);
	if(gate1==1)
	{ 
		working_7400[0]=1; 
	} 
	if(gate2==1)
	{
		working_7400[1]=1;
	}
	if(gate3==1)
	{
		working_7400[2]=1;
	}
	if(gate4==1)
	{
		working_7400[3]=1;
	}
}
void checkTwoXOR_1()
{
	int gate1=checkTwoXOR_2(pin1,pin2,pin3); 
	int gate2=checkTwoXOR_2(pin4,pin5,pin6);
	int gate3=checkTwoXOR_2(pin10,pin9,pin8);
	int gate4=checkTwoXOR_2(pin13,pin12,pin11);
	if(gate1==1)
	{ 
		working_7486[0]=1; 
	} 
	if(gate2==1)
	{
		working_7486[1]=1;
	}
	if(gate3==1)
	{
		working_7486[2]=1;
	}
	if(gate4==1)
	{
		working_7486[3]=1;
	}
}
void checkTwoNOR_1()
{
	int gate1=checkTwoNOR_2(pin3,pin2,pin1); 
	int gate2=checkTwoNOR_2(pin6,pin5,pin4);
	int gate3=checkTwoNOR_2(pin8,pin9,pin10);
	int gate4=checkTwoNOR_2(pin11,pin12,pin13);
	if(gate1==1)
	{ 
		working_7402[0]=1; 
	} 
	if(gate2==1)
	{
		working_7402[1]=1;
	}
	if(gate3==1)
	{
		working_7402[2]=1;
	}
	if(gate4==1)
	{
		working_7402[3]=1;
	}
}
void checkTwoAND_1()
{
	int gate1=checkTwoAND_2(pin1,pin2,pin3); 
	int gate2=checkTwoAND_2(pin4,pin5,pin6);
	int gate3=checkTwoAND_2(pin10,pin9,pin8);
	int gate4=checkTwoAND_2(pin13,pin12,pin11);
	if(gate1==1)
	{ 
		working_7408[0]=1; 
	} 
	if(gate2==1)
	{
		working_7408[1]=1;
	}
	if(gate3==1)
	{
		working_7408[2]=1;
	}
	if(gate4==1)
	{
		working_7408[3]=1;
	}
}
void checkTwoOR_1()
{
	int gate1=checkTwoAND_2(pin1,pin2,pin3); 
	int gate2=checkTwoAND_2(pin4,pin5,pin6);
	int gate3=checkTwoAND_2(pin10,pin9,pin8);
	int gate4=checkTwoAND_2(pin13,pin12,pin11);
	if(gate1==1)
	{ 
		working_7432[0]=1; 
	} 
	if(gate2==1)
	{
		working_7432[1]=1;
	}
	if(gate3==1)
	{
		working_7432[2]=1;
	}
	if(gate4==1)
	{
		working_7432[3]=1;
	}
}

int checkFourNAND_2(int pin_1,int pin_2,int pin_3,int pin_4,int pin_5)
{
	int result[16]={};
	if(pin_5==pin6)
	{	
		DDRA=0;
		DDRA=((1<<pin_1)|(1<<pin_2)|(1<<pin_3)|(1<<pin_4)|(0<<pin_5));
		for(int z=0;z<15;z++)
			result[z]=32;
		result[15]=0;
	} 

	else if(pin_5==pin8)
	{
		DDRC=0;
		DDRC=((1<<pin_1)|(1<<pin_2)|(1<<pin_3)|(1<<pin_4)|(0<<pin_5));
		for(int z=0;z<15;z++)
			result[z]=64;
		result[15]=0;
	}
	int i=0;
	for(i=0;i<16;i++)
	{
		int bit1=(i&8)>>3;
		int bit2=(i&4)>>2;
		int bit3=(i&2)>>1;
		int bit4=(i&1);
		if(pin_5==pin6)
		{
			PORTA=((bit1<<pin_1) + (bit2<<pin_2) + (bit3<<pin_3) + (bit4<<pin_4));
			_delay_ms(10);
			if((PINA&(1<<pin_5))!=result[i])
			{
				break;
			}
		}

		else if(pin_5==pin8)
		{
			PORTC=((bit1<<pin_1) + (bit2<<pin_2) + (bit3<<pin_3) + (bit4<<pin_4));
			_delay_ms(10);
			if((PINC&(1<<pin_5))!=result[i])
			{
				break;
			}
		}
	}
	if(i==16)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int checkFourAND_2(int pin_1,int pin_2,int pin_3,int pin_4,int pin_5)
{
	int result[16]={};
	if(pin_5==pin6)
	{	
		DDRA=0;
		DDRA=((1<<pin_1)|(1<<pin_2)|(1<<pin_3)|(1<<pin_4)|(0<<pin_5));
		for(int z=0;z<15;z++)
			result[z]=0;
		result[15]=32;
	} 

	else if(pin_5==pin8)
	{
		DDRC=0;
		DDRC=((1<<pin_1)|(1<<pin_2)|(1<<pin_3)|(1<<pin_4)|(0<<pin_5));
		for(int z=0;z<15;z++)
			result[z]=0;
		result[15]=64;
	}
	int i=0;
	for(i=0;i<16;i++)
	{
		int bit1=(i&8)>>3;
		int bit2=(i&4)>>2;
		int bit3=(i&2)>>1;
		int bit4=(i&1);
		if(pin_5==pin6)
		{
			PORTA=((bit1<<pin_1) + (bit2<<pin_2) + (bit3<<pin_3) + (bit4<<pin_4));
			_delay_ms(10);
			if((PINA&(1<<pin_5))!=result[i])
			{
				break;
			}
		}

		else if(pin_5==pin8)
		{
			PORTC=((bit1<<pin_1) + (bit2<<pin_2) + (bit3<<pin_3) + (bit4<<pin_4));
			_delay_ms(10);
			if((PINC&(1<<pin_5))!=result[i])
			{
				break;
			}
		}
	}
	if(i==16)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int checkFourNOR_2(int pin_1,int pin_2,int pin_3,int pin_4,int pin_5)
{
	int result[16]={};
	if(pin_5==pin6)
	{	
		DDRA=0;
		DDRA=((1<<pin_1)|(1<<pin_2)|(1<<pin_3)|(1<<pin_4)|(0<<pin_5));
		result[0]=32;
		for(int z=1;z<16;z++)
			result[z]=0;
		
	} 

	else if(pin_5==pin8)
	{
		DDRC=0;
		DDRC=((1<<pin_1)|(1<<pin_2)|(1<<pin_3)|(1<<pin_4)|(0<<pin_5));
		result[0]=64;
		for(int z=1;z<16;z++)
			result[z]=0;
		
	}
	int i=0;
	for(i=0;i<16;i++)
	{
		int bit1=(i&8)>>3;
		int bit2=(i&4)>>2;
		int bit3=(i&2)>>1;
		int bit4=(i&1);
		if(pin_5==pin6)
		{
			PORTA=((bit1<<pin_1) + (bit2<<pin_2) + (bit3<<pin_3) + (bit4<<pin_4) + (1<<pin3));
			_delay_ms(10);
			if((PINA&(1<<pin_5))!=result[i])
			{
				break;
			}
		}

		else if(pin_5==pin8)
		{
			PORTC=((bit1<<pin_1) + (bit2<<pin_2) + (bit3<<pin_3) + (bit4<<pin_4) + (1<<pin3));
			_delay_ms(10);
			if((PINC&(1<<pin_5))!=result[i])
			{
				break;
			}
		}
	}
	if(i==8)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int checkThreeAND_2(int pin_1,int pin_2,int pin_3,int pin_4)
{
	int result[8]={};
	if(pin_4==pin12)
	{	
		DDRA=0;
		DDRC=0;
		DDRA=((1<<pin_1)|(1<<pin_2));
		DDRC=((1<<pin_3)|(0<<pin_4));
		for(int z=0;z<7;z++)
			result[z]=0;
		result[7]=4;
	} 
	else if(pin_4==pin6)
	{
		DDRA=0;
		DDRA=((1<<pin_1)|(1<<pin_2)|(1<<pin_3)|(0<<pin_4));
		for(int z=0;z<7;z++)
			result[z]=0;
		result[7]=32;
	}
	else if(pin_4==pin8)
	{
		DDRC=0;
		DDRC=((1<<pin_1)|(1<<pin_2)|(1<<pin_3)|(0<<pin_4));
		for(int z=0;z<7;z++)
			result[z]=0;
		result[7]=64;
	}
	int i=0;
	for(i=0;i<8;i++)
	{
		int bit1=(i&4)>>2;
		int bit2=(i&2)>>1;
		int bit3=(i&1);
		if(pin_4==pin12)
		{
			PORTA=((bit1<<pin_1) + (bit2<<pin_2));
			PORTC=(bit3<<pin_3);
			_delay_ms(10);
			if((PINC&(1<<pin_4))!=result[i])
			{
				break;
			}
		}

		else if(pin_4==pin6)
		{
			PORTA=((bit1<<pin_1) + (bit2<<pin_2) + (bit3<<pin_3));
			_delay_ms(10);
			if((PINA&(1<<pin_4))!=result[i])
			{
				break;
			}
		}
		else if(pin_4==pin8)
		{
			PORTC=((bit1<<pin_1) + (bit2<<pin_2) + (bit3<<pin_3));
			_delay_ms(10);
			if((PINC&(1<<pin_4))!=result[i])
			{
				break;
			}
		}
	}
	if(i==8)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int checkThreeNAND_2(int pin_1,int pin_2,int pin_3,int pin_4)
{
	int result[8]={};
	if(pin_4==pin12)
	{	
		DDRA=0;
		DDRC=0;
		DDRA=((1<<pin_1)|(1<<pin_2));
		DDRC=((1<<pin_3)|(0<<pin_4));
		for(int z=0;z<7;z++)
			result[z]=4;
		result[7]=0;
	} 
	else if(pin_4==pin6)
	{
		DDRA=0;
		DDRA=((1<<pin_1)|(1<<pin_2)|(1<<pin_3)|(0<<pin_4));
		for(int z=0;z<7;z++)
			result[z]=32;
		result[7]=0;
	}
	else if(pin_4==pin8)
	{
		DDRC=0;
		DDRC=((1<<pin_1)|(1<<pin_2)|(1<<pin_3)|(0<<pin_4));
		for(int z=0;z<7;z++)
			result[z]=64;
		result[7]=0;
	}
	int i=0;
	for(i=0;i<8;i++)
	{	
		int bit1=(i&4)>>2;
		int bit2=(i&2)>>1;
		int bit3=(i&1);
		if(pin_4==pin12)
		{
			PORTA=((bit1<<pin_1) + (bit2<<pin_2));
			PORTC=(bit3<<pin_3);
			_delay_ms(10);
			if((PINC&(1<<pin_4))!=result[i])
			{
				
				break;
			}
		}

		else if(pin_4==pin6)
		{
			PORTA=((bit1<<pin_1) + (bit2<<pin_2) + (bit3<<pin_3));
			_delay_ms(10);
			if((PINA&(1<<pin_4))!=result[i])
			{
				break;
			}
		}
		else if(pin_4==pin8)
		{
			PORTC=((bit1<<pin_1) + (bit2<<pin_2) + (bit3<<pin_3));
			_delay_ms(10);
			if((PINC&(1<<pin_4))!=result[i])
			{
				break;
			}
		}
	}
	if(i==8)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int checkThreeNOR_2(int pin_1,int pin_2,int pin_3,int pin_4)
{
	int result[8]={};
	if(pin_4==pin12)
	{	
		DDRA=0;
		DDRC=0;
		DDRA=((1<<pin_1)|(1<<pin_2));
		DDRC=((1<<pin_3)|(0<<pin_4));
		result[0]=4;
		for(int z=1;z<8;z++)
			result[z]=0;
		
	} 
	else if(pin_4==pin6)
	{
		DDRA=0;
		DDRA=((1<<pin_1)|(1<<pin_2)|(1<<pin_3)|(0<<pin_4));
		result[0]=32;
		for(int z=1;z<8;z++)
			result[z]=0;
		
	}
	else if(pin_4==pin8)
	{
		DDRC=0;
		DDRC=((1<<pin_1)|(1<<pin_2)|(1<<pin_3)|(0<<pin_4));
		result[0]=64;
		for(int z=1;z<8;z++)
			result[z]=0;
		
	}
	int i=0;
	for(i=0;i<8;i++)
	{
		int bit1=(i&4)>>2;
		int bit2=(i&2)>>1;
		int bit3=(i&1);
		if(pin_4==pin12)
		{
			PORTA=((bit1<<pin_1) + (bit2<<pin_2));
			PORTC=(bit3<<pin_3);
			_delay_ms(10);
			if((PINC&(1<<pin_4))!=result[i])
			{
				break;
			}
		}

		else if(pin_4==pin6)
		{
			PORTA=((bit1<<pin_1) + (bit2<<pin_2) + (bit3<<pin_3));
			_delay_ms(10);
			if((PINA&(1<<pin_4))!=result[i])
			{
				break;
			}
		}
		else if(pin_4==pin8)
		{
			PORTC=((bit1<<pin_1) + (bit2<<pin_2) + (bit3<<pin_3));
			_delay_ms(10);
			if((PINC&(1<<pin_4))!=result[i])
			{
				break;
			}
		}
	}
	if(i==8)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int checkTwoNAND_2(int pin_1,int pin_2,int pin_3)
{
	int result[4]={};
	if(pin_3==pin3)
	{	
		DDRA=0;
		DDRA=((1<<pin_1)|(1<<pin_2)|(0<<pin_3));
		for(int z=0;z<3;z++)
			result[z]=4;
		result[3]=0;
	} 
	else if(pin_3==pin6)
	{	
		DDRA=0;
		DDRA=((1<<pin_1)|(1<<pin_2)|(0<<pin_3));
		for(int z=0;z<3;z++)
			result[z]=32;
		result[3]=0;
	}
	else if(pin_3==pin8)
	{	
		DDRC=0;
		DDRC=((1<<pin_1)|(1<<pin_2)|(0<<pin_3));
		for(int z=0;z<3;z++)
			result[z]=64;
		result[3]=0;
	}
	else if(pin_3==pin11)
	{	
		DDRC=0;
		DDRC=((1<<pin_1)|(1<<pin_2)|(0<<pin_3));
		for(int z=0;z<3;z++)
			result[z]=8;
		result[3]=0;
	}
	int i=0;
	for(i=0;i<4;i++)
	{
		int bit1=(i&2)>>1;
		int bit2=(i&1);
		if(pin_3==pin3)
		{
			PORTA=((bit1<<pin_1) + (bit2<<pin_2));
			_delay_ms(10);
			if((PINA&(1<<pin_3))!=result[i])
			{
				break;
			}
		}
		else if(pin_3==pin6)
		{
			PORTA=((bit1<<pin_1) + (bit2<<pin_2));
			_delay_ms(10);
			if((PINA&(1<<pin_3))!=result[i])
			{
				break;
			}
		}
		else if(pin_3==pin8)
		{
			PORTC=((bit1<<pin_1) + (bit2<<pin_2));
			_delay_ms(10);
			if((PINC&(1<<pin_3))!=result[i])
			{
				break;
			}
		}
		else if(pin_3==pin11)
		{
			PORTC=((bit1<<pin_1) + (bit2<<pin_2));
			_delay_ms(10);
			if((PINC&(1<<pin_3))!=result[i])
			{
				break;
			}
		}
	}
	if(i==4)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int checkTwoXOR_2(int pin_1,int pin_2,int pin_3)
{
	int result[4]={};
	if(pin_3==pin3)
	{	
		DDRA=0;
		DDRA=((1<<pin_1)|(1<<pin_2)|(0<<pin_3));
		result[0]=0;
		for(int z=1;z<3;z++)
			result[z]=4;
		result[3]=0;
	} 
	else if(pin_3==pin6)
	{	
		DDRA=0;
		DDRA=((1<<pin_1)|(1<<pin_2)|(0<<pin_3));
		result[0]=0;
		for(int z=1;z<3;z++)
			result[z]=32;
		result[3]=0;
	}
	else if(pin_3==pin8)
	{	
		DDRC=0;
		DDRC=((1<<pin_1)|(1<<pin_2)|(0<<pin_3));
		result[0]=0;
		for(int z=1;z<3;z++)
			result[z]=64;
		result[3]=0;
	}
	else if(pin_3==pin11)
	{	
		DDRC=0;
		DDRC=((1<<pin_1)|(1<<pin_2)|(0<<pin_3));
		result[0]=0;
		for(int z=1;z<3;z++)
			result[z]=8;
		result[3]=0;
	}
	int i=0;
	for(i=0;i<4;i++)
	{
		int bit1=(i&2)>>1;
		int bit2=(i&1);
		if(pin_3==pin3)
		{
			PORTA=((bit1<<pin_1) + (bit2<<pin_2));
			_delay_ms(10);
			if((PINA&(1<<pin_3))!=result[i])
			{
				break;
			}
		}
		else if(pin_3==pin6)
		{
			PORTA=((bit1<<pin_1) + (bit2<<pin_2));
			_delay_ms(10);
			if((PINA&(1<<pin_3))!=result[i])
			{
				break;
			}
		}
		else if(pin_3==pin8)
		{
			PORTC=((bit1<<pin_1) + (bit2<<pin_2));
			_delay_ms(10);
			if((PINC&(1<<pin_3))!=result[i])
			{
				break;
			}
		}
		else if(pin_3==pin11)
		{
			PORTC=((bit1<<pin_1) + (bit2<<pin_2));
			_delay_ms(10);
			if((PINC&(1<<pin_3))!=result[i])
			{
				break;
			}
		}
	}
	if(i==4)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int checkTwoNOR_2(int pin_1,int pin_2,int pin_3)
{
	int result[4]={};
	if(pin_3==pin1)
	{	
		DDRA=0;
		DDRA=((1<<pin_1)|(1<<pin_2)|(0<<pin_3));
		result[0]=1;
		for(int z=1;z<4;z++)
			result[z]=0;
	} 
	else if(pin_3==pin4)
	{	
		DDRA=0;
		DDRA=((1<<pin_1)|(1<<pin_2)|(0<<pin_3));
		result[0]=8;
		for(int z=1;z<4;z++)
			result[z]=0;
	}
	else if(pin_3==pin10)
	{	
		DDRC=0;
		DDRC=((1<<pin_1)|(1<<pin_2)|(0<<pin_3));
		result[0]=16;
		for(int z=1;z<4;z++)
			result[z]=0;
	}
	else if(pin_3==pin13)
	{	
		DDRC=0;
		DDRC=((1<<pin_1)|(1<<pin_2)|(0<<pin_3));
		result[0]=2;
		for(int z=1;z<4;z++)
			result[z]=0;
	}
	int i=0;
	for(i=0;i<4;i++)
	{
		int bit1=(i&2)>>1;
		int bit2=(i&1);
		if(pin_3==pin1)
		{
			PORTA=((bit1<<pin_1) + (bit2<<pin_2));
			_delay_ms(10);
			if((PINA&(1<<pin_3))!=result[i])
			{
				break;
			}
		}
		else if(pin_3==pin4)
		{
			PORTA=((bit1<<pin_1) + (bit2<<pin_2));
			_delay_ms(10);
			if((PINA&(1<<pin_3))!=result[i])
			{
				break;
			}
		}
		else if(pin_3==pin10)
		{
			PORTC=((bit1<<pin_1) + (bit2<<pin_2));
			_delay_ms(10);
			if((PINC&(1<<pin_3))!=result[i])
			{
				break;
			}
		}
		else if(pin_3==pin13)
		{
			PORTC=((bit1<<pin_1) + (bit2<<pin_2));
			_delay_ms(10);
			if((PINC&(1<<pin_3))!=result[i])
			{
				break;
			}
		}
	}
	if(i==4)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int checkTwoAND_2(int pin_1,int pin_2,int pin_3)
{
	int result[4]={};
	if(pin_3==pin3)
	{	
		DDRA=0;
		DDRA=((1<<pin_1)|(1<<pin_2)|(0<<pin_3));
		for(int z=0;z<3;z++)
			result[z]=0;
		result[3]=4;
	} 
	else if(pin_3==pin6)
	{	
		DDRA=0;
		DDRA=((1<<pin_1)|(1<<pin_2)|(0<<pin_3));
		for(int z=0;z<3;z++)
			result[z]=0;
		result[3]=32;
	}
	else if(pin_3==pin8)
	{	
		DDRC=0;
		DDRC=((1<<pin_1)|(1<<pin_2)|(0<<pin_3));
		for(int z=0;z<3;z++)
			result[z]=0;
		result[3]=64;
	}
	else if(pin_3==pin11)
	{	
		DDRC=0;
		DDRC=((1<<pin_1)|(1<<pin_2)|(0<<pin_3));
		for(int z=0;z<3;z++)
			result[z]=0;
		result[3]=8;
	}
	int i=0;
	for(i=0;i<4;i++)
	{
		int bit1=(i&2)>>1;
		int bit2=(i&1);
		if(pin_3==pin3)
		{
			PORTA=((bit1<<pin_1) + (bit2<<pin_2));
			_delay_ms(10);
			if((PINA&(1<<pin_3))!=result[i])
			{
				break;
			}
		}
		else if(pin_3==pin6)
		{
			PORTA=((bit1<<pin_1) + (bit2<<pin_2));
			_delay_ms(10);
			if((PINA&(1<<pin_3))!=result[i])
			{
				break;
			}
		}
		else if(pin_3==pin8)
		{
			PORTC=((bit1<<pin_1) + (bit2<<pin_2));
			_delay_ms(10);
			if((PINC&(1<<pin_3))!=result[i])
			{
				break;
			}
		}
		else if(pin_3==pin11)
		{
			PORTC=((bit1<<pin_1) + (bit2<<pin_2));
			_delay_ms(10);
			if((PINC&(1<<pin_3))!=result[i])
			{
				break;
			}
		}
	}
	if(i==4)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int checkTwoOR_2(int pin_1,int pin_2,int pin_3)
{
	int result[4]={};
	if(pin_3==pin3)
	{	
		DDRA=0;
		DDRA=((1<<pin_1)|(1<<pin_2)|(0<<pin_3));
		result[0]=0;
		for(int z=1;z<4;z++)
			result[z]=4;
		
	} 
	else if(pin_3==pin6)
	{	
		DDRA=0;
		DDRA=((1<<pin_1)|(1<<pin_2)|(0<<pin_3));
		result[0]=0;
		for(int z=1;z<4;z++)
			result[z]=32;
	}
	else if(pin_3==pin8)
	{	
		DDRC=0;
		DDRC=((1<<pin_1)|(1<<pin_2)|(0<<pin_3));
		result[0]=0;
		for(int z=1;z<4;z++)
			result[z]=64;
	}
	else if(pin_3==pin11)
	{	
		DDRC=0;
		DDRC=((1<<pin_1)|(1<<pin_2)|(0<<pin_3));
		result[0]=0;
		for(int z=1;z<4;z++)
			result[z]=8;
	}
	int i=0;
	for(i=0;i<4;i++)
	{
		int bit1=(i&2)>>1;
		int bit2=(i&1);
		if(pin_3==pin3)
		{
			PORTA=((bit1<<pin_1) + (bit2<<pin_2));
			_delay_ms(10);
			if((PINA&(1<<pin_3))!=result[i])
			{
				break;
			}
		}
		else if(pin_3==pin6)
		{
			PORTA=((bit1<<pin_1) + (bit2<<pin_2));
			_delay_ms(10);
			if((PINA&(1<<pin_3))!=result[i])
			{
				break;
			}
		}
		else if(pin_3==pin8)
		{
			PORTC=((bit1<<pin_1) + (bit2<<pin_2));
			_delay_ms(10);
			if((PINC&(1<<pin_3))!=result[i])
			{
				break;
			}
		}
		else if(pin_3==pin11)
		{
			PORTC=((bit1<<pin_1) + (bit2<<pin_2));
			_delay_ms(10);
			if((PINC&(1<<pin_3))!=result[i])
			{
				break;
			}
		}
	}
	if(i==4)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void commonfour(char str_1[],char str_2[],int p[]) 
{ 
	if(function==1 && state==1)
	{
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_string(str_1);
		lcd_cmd(0xc0);
		lcd_string(str_2);
		state=0;
	}
	else if(function==2 && state==1)
	{
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_string("1 : ");
		if(p[0]==1)
			lcd_string("OK");
		else if(p[0]==0)
			lcd_string("FY");
		lcd_cmd(0x88);
		lcd_string("2 : ");
		if(p[1]==1)
			lcd_string("OK");
		else if(p[1]==0)
			lcd_string("FY");
		state=0;

	}
}
void commonthree(char str_1[],char str_2[],int p[]) 
{ 
	if(function==1 && state==1)
	{
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_string(str_1);
		lcd_cmd(0xc0);
		lcd_string(str_2);
		state=0;
	}
	else if(function==2 && state==1)
	{
		lcd_cmd(0x01);
		lcd_cmd(0x85);
		lcd_string("1 : ");
		if(p[0]==1)
			lcd_string("OK");
		else if(p[0]==0)
			lcd_string("FY");
		lcd_cmd(0xc0);
		lcd_string("2 : ");
		if(p[1]==1)
			lcd_string("OK");
		else if(p[1]==0)
			lcd_string("FY");
		lcd_cmd(0xc8);
		lcd_string("3 : ");
		if(p[2]==1)
			lcd_string("OK");
		else if(p[2]==0)
			lcd_string("FY");
		state=0;
	}
}
void commontwo(char str_1[],char str_2[],int p[]) 
{ 
	if(function==1 && state==1)
	{
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_string(str_1);
		lcd_cmd(0xc0);
		lcd_string(str_2);
		state=0;
	}
	else if(function==2 && state==1)
	{
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_string("1 : ");
		if(p[0]==1)
			lcd_string("OK");
		else if(p[0]==0)
			lcd_string("FY");
		lcd_cmd(0xc0);
		lcd_string("2 : ");
		if(p[1]==1)
			lcd_string("OK");
		else if(p[1]==0)
			lcd_string("FY");
		lcd_cmd(0xc8);
		lcd_string("3 : ");
		if(p[2]==1)
			lcd_string("OK");
		else if(p[2]==0)
			lcd_string("FY");
		lcd_cmd(0x88);
		lcd_string("4 : ");
		if(p[2]==1)
			lcd_string("OK");
		else if(p[2]==0)
			lcd_string("FY");
		state=0;

	}
}
