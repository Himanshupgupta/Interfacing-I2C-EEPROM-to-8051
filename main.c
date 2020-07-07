#include<reg51.h>
#include"I2C.h"

//Define SCL and SDA pins
sbit SCL = P3^4;
sbit SDA = P3^5;

void EEP_Write_Byte(unsigned char Address,unsigned char Data)
{
	I2C_Start();					//I2C start the SDA and SCL
	I2C_Send(0xA0);       //send write control byte
	I2C_Send(Address);    //send add. of slave
	I2C_Send(Data);       //send the Data which have to write
	I2C_Stop();
}

unsigned char EEP_Read_Byte(unsigned char Address)
{
	unsigned char Data;
	I2C_Start();					//I2C write the SDA and SCL
	I2C_Send(0xA0);       //send read control byte
	I2C_Send(Address);
	
	I2C_Start();
	I2C_Send(0xA1);       //send read control byte
	Data=I2C_Read();      //read Data from EEPROM
		Nack();   
	I2C_Stop();
	return Data;
}

void EEP_Write_Bytes(unsigned char Address,unsigned char *Data,char N)
{
	while(N!=0)
	{
		EEP_Write_Byte(Address,*Data++);
		N--;Address++;
	}
	I2C_Stop();
}

unsigned char EEP_Read_Bytes(unsigned char Address,unsigned char *Data,char N)
{
	while(N!=0)
	{
		*Data=EEP_Read_Byte(Address);
		Data++; N--;Address++;
	}
}

void main()
{	
	int i=0;char f;
	char Name[]="himanshu Gupta";
	//for(i =0; i<14; i++){
	EEP_Write_Bytes(0,Name,13);
	
	f=EEP_Read_Byte(0);
	EEP_Write_Byte(0,f);
	while(1);
}