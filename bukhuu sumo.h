#include <30F6015.h>
#device ADC=8
#device ICSP=1
#FUSES WDT                      //Watch Dog Timer
#FUSES WPSA8                    //Watch Dog Timer PreScalar A 1:8
#FUSES WPSB10                   //Watch Dog Timer PreScalar B 1:10
#FUSES NOCKSFSM                 //Clock Switching is disabled, fail Safe clock monitor is disabled
#FUSES NOBROWNOUT               //No brownout reset
#use delay(clock=80000000,restart_wdt)
#FUSES XT_PLL8

//#use rs232(UART2, baud=115200, stream=U1) // TRANSMIT_BUFFER=32
#use rs232(UART2, baud=115200, stream=U1) //TRANSMIT_BUFFER=100, 

/*
#define select0 pin_c13
#define select1 pin_c14
#define select2 pin_d0

#define read1 PIN_f3 //1
#define read2 PIN_f0 //4
#define read3 PIN_f1 //2
#define read4 PIN_d7 //3
*/
//#byte LATC=0X2D0
//#byte LATD=0X2D6
//#byte LATF=0X2e2

//#byte trisc=0X2cc
//#byte trisd=0X2D2

#bit select1=0x2e2.3
#bit select2=0x2e2.0
#bit select3=0x2e2.1
#bit select4=0x2d6.7

#bit led1=0x2d0.13
#bit led2=0x2d0.14
#bit led3=0x2d6.0

//#bit tris_led1=trisc.13
//#bit tris_led2=trisc.14
//#bit tris_led3=trisd.0



#byte B_tris       =0x2c6
#byte B_port       =0x2c8  
#byte B_latch      =0x2ca 


#byte D_tris       =0x2d2
#byte D_port       =0x2d4  
#byte D_latch      =0x2d6  

#byte E_tris       =0x2d8
#byte E_port       =0x2da  
#byte E_latch      =0x2dc  



//#bit pwm2=E_latch.2   //pwm2 low
#bit dirR1=D_latch.5
#bit dirL1=D_latch.6
//#bit Enable2=D_latch.4

//#bit pwm1=E_latch.0   //pwm1 low
#bit dirR2=D_latch.2
#bit dirL2=D_latch.3
//#bit Enable1=D_latch.1





#bit btn1     =   0x2DA.5 // E port nii 5 bit //negdugeer hol
#bit btn2     =   B_port.4

#bit btn1_tris=E_tris.5

#bit sens1  =   0x2c8.0
#bit sens2  =   0x2c8.1
#bit sens3  =   0x2c8.2
#bit sens4  =   0x2c8.3
#bit sens5  =   0x2d4.9

#bit line_lift =  0x2d4.10
#bit line_right =  0x2d4.11

#bit start_signal =  0x2c8.14

#bit cntrl_tris=B_tris.12
#bit cntrl     =B_port.12
#bit test_pin  =B_port.11
#bit mic_pin  =B_port.13
#bit U2TBF_bit  =  0x0218.9


#use i2c(MASTER, I2C1, FAST)


