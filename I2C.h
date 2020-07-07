//#ifndef __I2C_H
//#define __I2C_H

extern bit SCL;
extern bit SDA;

//i2c start bit
void I2C_Start()
{
	SDA=1;
	SCL=1;
	SDA=0;
	SCL=0;
}

//i2c stop bit
void I2C_Stop()
{
	SDA=0;
	SCL=1;
	SDA=1;
	SCL=0;
}

//i2c ack
void Ack()
{
	SDA=0;
	SCL=1;
	SCL=0;
	SDA=1;
}

//i2c Not ack
void Nack()
{
	SDA=1;
	SCL=1;
	SCL=0;
	SDA=1;
}

//i2c send
void I2C_Send(unsigned char Data)
{
	int i;
	for(i=0;i<8;i++)
	{
		SDA=Data&0x80;
		SCL=1;
		SCL=0;
		Data<<=1;
	}	
	Ack();
}

//i2c read
unsigned char I2C_Read()
{
	unsigned char i,Data=0;
	for(i=0;i<8;i++)
	{
		SCL=1;
		Data|=SDA;
		if(i<7)
			Data<<=1;
		SCL=0;
	}
	return Data;
}