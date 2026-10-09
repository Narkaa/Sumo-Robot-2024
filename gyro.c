
#define W_DATA         0xD0
#define R_DATA         0xD1
#define PWR_MGMT_1     0x6B
#define PWR_MGMT_2     0x6C
#define SMPRT_DIV      0x19
#define CONFIG_R       0x1A
#define GYRO_CONFIG    0x1B
#define ACCEL_CONFIG   0x1C
#define ACCEL_XOUT_H   0x3B
#define ACCEL_XOUT_L   0x3C
#define ACCEL_YOUT_H   0x3D
#define ACCEL_YOUT_L   0x3E
#define ACCEL_ZOUT_H   0x3F
#define ACCEL_ZOUT_L   0x40
#define TEMP_OUT_H     0x41
#define TEMP_OUT_L     0x42
#define GYRO_XOUT_H    0x43
#define GYRO_XOUT_L    0x44
#define GYRO_YOUT_H    0x45
#define GYRO_YOUT_L    0x46
#define GYRO_ZOUT_H    0x47
#define GYRO_ZOUT_L    0x48

void mpu6050_write(int add, int data)
{
         i2c_start();
         i2c_write(W_DATA);
         i2c_write(add);
         i2c_write(data);
         i2c_stop();
 
}
      
int16 mpu6050_read(int add){
         int retval;
         i2c_start();
         i2c_write(W_DATA);
         i2c_write(add);
         i2c_start();
         i2c_write(R_DATA);
         retval=i2c_read(0);
         i2c_stop();
         return retval;
}
 
void mpu6050_init(){
         mpu6050_write(PWR_MGMT_1,  0x80);
         delay_ms(100);
         mpu6050_write(PWR_MGMT_1,  0x00);
         delay_ms(100);
         mpu6050_write(CONFIG_R,    0x01);
         delay_ms(10);
         mpu6050_write(GYRO_CONFIG, 0x1f);
}


/*
void main()
{
delay_ms(2);
lcd_init();
   
printf(lcd_putc,"\f");
lcd_gotoxy(1,1);
printf(lcd_putc," MPU6050 Gyro   ");
lcd_gotoxy(1,2);
printf(lcd_putc," Accelerometer  ");
delay_ms(1000);
printf(lcd_putc,"\f");

   while(TRUE)
   {
   A_data[0]=mpu6050_read(0x3B); //Read X axis(LSB)
   A_data[1]=mpu6050_read(0x3C); //Read X axis(MSB)
   A_data[2]=mpu6050_read(0x3D); //Read Y axis(LSB)
   A_data[3]=mpu6050_read(0x3E); //Read Y axis(MSB)
   A_data[4]=mpu6050_read(0x3F); //Read Z axis(LSB)
   A_data[5]=mpu6050_read(0x40); //Read Z axis(MSB)
     
   temp_data[0]=mpu6050_read(0x41);
   temp_data[1]=mpu6050_read(0x42);
     
   G_data[0]=mpu6050_read(0x43); //Read X axis(LSB)
   G_data[1]=mpu6050_read(0x44); //Read X axis(MSB)
   G_data[2]=mpu6050_read(0x45); //Read Y axis(LSB)
   G_data[3]=mpu6050_read(0x46); //Read Y axis(MSB)
   G_data[4]=mpu6050_read(0x47); //Read Z axis(LSB)
   G_data[5]=mpu6050_read(0x48); //Read Z axis(MSB)
    
   Xa=make16(A_data[0],A_data[1]);
   Ya=make16(A_data[2],A_data[3]);
   Za=make16(A_data[4],A_data[5]);
    
   temp=make16(temp_data[0],temp_data[1]);
   temp=temp/340 + 36.53;
   
   Xg=make16(G_data[0],G_data[1]);
   Yg=make16(G_data[2],G_data[3]);
   Zg=make16(G_data[4],G_data[5]);
   
   float Heading = atan2((signed int16)Ya,(signed int16)Xa)* 180 / pi + 180;
     
   lcd_gotoxy(1,1);
   printf(lcd_putc,"X:%ld  ",Xa);
   lcd_gotoxy(10,1);
   printf(lcd_putc,"Y:%ld  ",Ya);
   lcd_gotoxy(1,2);
   printf(lcd_putc,"Z:%ld  ",Za);
   lcd_gotoxy(10,2);
   printf(lcd_putc,"H:%f  ",heading);
/* For  4x16 LCD
   lcd_gotoxy(1,3);
   printf(lcd_putc,"Xg:%ld  ",Xg);
   lcd_gotoxy(9,3);
   printf(lcd_putc,"Yg:%ld  ",Yg);
   lcd_gotoxy(1,4);
   printf(lcd_putc,"Zg:%ld  ",Zg);
   lcd_gotoxy(9,4);
   printf(lcd_putc,"T :%ld  ",temp);

   printf("\n\r H: %f X: %ld  Y: %ld  Z: %ld  T: %ld  \n\r",Heading,Xg,Yg,Zg,temp);
   delay_ms(100);
   }
}
*/
