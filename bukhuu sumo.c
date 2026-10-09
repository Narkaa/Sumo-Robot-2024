#include <bukhuu sumo.h>
//#include <string.h>
unsigned int8 mode=0,m_mode=0,user_mode=0,mic_mode=0;
int16 counter=0;
unsigned int8 f0,f1=0;
unsigned int8 t0,t1,t2,l0,l1,r0;
unsigned int8 cntr=0;
unsigned int8 led_out[12];
unsigned int8 k[2],s[13]={0};
unsigned int8 con[8];
unsigned int8 btn1_set=0,btn2_set=0;
unsigned int8 UL=0,UR=0,C=0,HR=0,HL=0,AL=0,AR=0;

unsigned int8 UlineR=0,UlineL=0,AlineR=0,AlineL=0;

unsigned int16 start_cnt=0,start_time=12000;
unsigned int8 cansel=0,start=0;

#bit PC=0x2c8.15

#bit PR=0x2c8.11

#bit PL=0x2c8.12
#bit down=0x2da.5   //e5
#bit up=0x2c8.4    //b4
#bit control=0x2e0.4    //f4
unsigned int8 btn1_state=0,btn2_state=0;

unsigned int8 s_data_out=0,s_data_in=0,s_data[200];


#define stop    0 
#define forward 1
#define back    2
#define right   3
#define left    4
#define left_go     5
#define right_go    6
#define forward_left     7
#define forward_right    8
#define forward_fast     9
#define back_left     10
#define back_right    11 
#define f_time    100
#define s_time    10
#define m_time    25
#define b_time    40
#define stop_time 50
#define go_cnt_time 150
#define f_time_set 100

//#include <function.c>
#include <gyro.c>
//#include <ESP12.c>

/*
0             1
      2
   6      7
 8          5
   3      4
      11
9            10
*/

signed int16 pow1=0,pow2=0,power1=0,power2=0,m_power1=0,m_power2=0;
unsigned int8 pwm,breack1=0,breack2=0;


#inline
void motor_control(){
   if(pow1>m_power1){
      m_power1=m_power1+5;
   }
   if(pow1<m_power1){
      m_power1=m_power1-5;
   }
   if(pow2>m_power2){
      m_power2=m_power2+5;
   }
   if(pow2<m_power2){
      m_power2=m_power2-5;
   }
   pwm=0;
   if(m_power1>1){
       dirR1=1;
       dirL1=1; 
      pwm=m_power1;
      breack1=0;      
      led_out[1]=10;      
   }
   else if(m_power1<-1){
       dirR1=1;
       dirL1=0; 
      pwm=m_power1*-1;
      breack1=0;      
      led_out[10]=10;      
   }else{
       dirR1=1;
       dirL1=0; 
//!      if(breack1<150){
//!         breack1++;
//!         breack1++;
//!      }
      pwm=0;
   }
   if(pwm>250){
      pwm=250;
   }
//   pwm=pwm*1;
   set_pwm_duty(5,pwm);//1

   pwm=0;
   if(m_power2>1){
      dirR2=1;
      dirL2=1; 
      pwm=m_power2;
      breack2=0;      
      led_out[0]=10;      
   }else if(m_power2<-1){
      dirR2=1;
      dirL2=0;
      pwm=m_power2*-1;
      breack2=0;      
      led_out[9]=10;      
   }
   else{
      dirR2=1;
      dirL2=0;
//!      if(breack2<150){
//!         breack2++;
//!         breack2++;
//!      }
      pwm=0;
   }
   if(pwm>250){
      pwm=250;
   }
//   pwm=pwm*1;
   set_pwm_duty(2,pwm);//1
}


 
#INT_TIMER4
void  timer4_isr(void) 
{

   motor_control();
   t0=1;
   t2=1;
   select1=1;
   select2=1;
   select3=1;
   select4=1;
   
   led1=0;
   led2=0;
   led3=0;
   
   switch(cntr)
   {
      case 0:
         if(led_out[0]>0){
            led_out[0]--;
            led1=1;
         }
         if(led_out[1]>0){
            led_out[1]--;
            led2=1;
         }
         if(led_out[2]>0){
            led3=1;
         }
         select1=0;
         cntr=1;
      break;
      case 1:
         if(led_out[3]>0){
            led_out[3]--;
            led1=1;
         }
         if(led_out[4]>0){
            led_out[4]--;
            led2=1;
         }
         if(led_out[5]>0){
            led3=1;
         }
         select2=0;
         cntr=2;
      break;
      case 2:
         if(led_out[6]>0){
            led1=1;
         }
         if(led_out[7]>0){
            led2=1;
         }
         if(led_out[8]>0){
            led3=1;
         }
         select3=0;
         cntr=3;
      break;
      case 3:
         if(led_out[9]>0){
            led_out[9]--;
            led1=1;
         }
         if(led_out[10]>0){
            led_out[10]--;
            led2=1;
         }
         if(led_out[11]>0){
            led3=1;
         }
         select4=0;
         cntr=0;
      break;
   }
   restart_wdt();
}

#define val 55
unsigned int val_white=0; 
//b15/11/13
void read_s(){
//!#bit sens1  =   0x2c8.0
//!#bit sens2  =   0x2c8.1
//!#bit sens3  =   0x2c8.2
//!#bit sens4  =   0x2c8.3
//!#bit sens5  =   0x2d4.9
//!
//!#bit line_lift =  0x2d4.10
//!#bit line_right =  0x2d4.11
//!
//!#bit start_signal =  0x2d4.14
//!
/*
0             1
      2
   6      7
 8          5
   3      4
      11
9            10
*/

   if(sens1==0){
      led_out[8]=1;
      if(s[0]<100){
         s[0]++;
      }
   }else{
      led_out[8]=0;
      s[0]=0;
   }
   if(sens2==0){
      led_out[6]=1;
      if(s[1]<100){
         s[1]++;
      }
   }else{
      led_out[6]=0;
      s[1]=0;
   }
   if(sens3==0){
      led_out[2]=1;
      if(s[2]<100){
         s[2]++;
      }
   }else{
      led_out[2]=0;
      s[2]=0;
   }
   if(sens4==0){
      led_out[7]=1;
      if(s[3]<100){
         s[3]++;
      }
   }else{
      led_out[7]=0;
      s[3]=0;
   }
   if(sens5==0){
      led_out[5]=1;
      if(s[4]<100){
         s[4]++;
      }
   }else{
      led_out[5]=0;
      s[4]=0;
   }
//!   if(line_lift==0){
//!      led_out[3]=10;
//!      if(s[5]<100){
//!         s[5]++;
//!      }
//!   }
//!   else{
//!      led_out[1]=0;
//!      s[5]=0;
//!   }
//!   if(line_right==0){
//!      led_out[4]=1;
//!      if(s[6]<100){
//!         s[6]++;
//!      }
//!   }
//!   else{
//!      led_out[0]=0;
//!      s[6]=0;
//!   }
   if(start_signal==1){
      led_out[11]=1;
      if(s[7]<100){
         s[7]++;
      }
   }
   else{
      led_out[11]=0;
      s[7]=0;
   }
}  

unsigned int8 l[4];
#inline
void line_sens(){

   if(line_lift==0){
      if(l[0]<100){
         l[0]++;
      }
      led_out[4]=10;
   }
   else{
      l[0]=0;
   }

   if(line_right==0){
      if(l[1]<100){
         l[1]++;
      }
      led_out[3]=10;
   }
   else{
      l[1]=0;
   }

/*
   if(li3==0){
      if(l[2]<100){
         l[2]++;
      }
   }
   else{
      l[2]=0;
   }
   led_out[2]=l[2]/10;
   if(li4==0){
      if(l[3]<100){
         l[3]++;
      }
   }
   else{
      l[3]=0;
   }
   led_out[3]=l[3]/10;
   */

//!   l[2]=0;
//!   l[3]=0;

}

unsigned int16 c_timer=0,c_counter,s_counter,s_mode=0,stop_mode=0;

#inline
void control(){
//*/
   if(s[7]>10){
      switch(stop_mode){
         case 0:
            if(l[0]>2){
//               stop[0]=250;
               stop_mode=2;
               s_mode=0;
               s_counter=0;
            }
            if(l[1]>2){
//               stop[1]=250;
               stop_mode=1;
               s_mode=0;
               s_counter=0;
            }
//!            if(l[2]>2){
//!               stop[2]=250;
//!               stop_mode=3;
//!               s_mode=0;
//!               s_counter=0;
//!            }
//!            if(l[3]>2){
//!               stop[3]=250;
//!               stop_mode=3;
//!               s_mode=0;
//!               s_counter=0;
//!            }
//!            
         break;
         case 1:
            switch(s_mode){
               case 0:
                  s_counter++;
                  if(s_counter>100){
                     s_counter=0;
                     s_mode=1;
                  }
                  power1=0;
                  m_power1=0;
                  if(breack1<150){
                     breack1=150; 
                  }
                  power2=0;
                  m_power2=0;
                  if(breack2<150){
                     breack2=150; 
                  }
               break;
               case 1:
                  s_counter++;
                  if(s_counter>200){
                     s_counter=0;
                     s_mode=2;
                  }
                  power1=-150;
                  power2=-150;
               break;
               case 2:
                  s_counter++;
                  if(s_counter>100){
                     s_counter=0;
                     s_mode=3;
                  }
                  power1=0;
                  m_power1=0;
                  if(breack1<150){
                     breack1=150; 
                  }
                  power2=0;
                  m_power2=0;
                  if(breack2<150){
                     breack2=150; 
                  }
               break;
               case 3:
                  s_counter++;
                  if(s_counter>150){
                     s_counter=0;
                     s_mode=4;
                  }
                  power1=-150;
                  power2=150;
               break;
               case 4:
                  stop_mode=0;
               break;
               case 5:
               break;
               case 6:
               break;
            }
         break;
         case 2:
            switch(s_mode){
               case 0:
                  s_counter++;
                  if(s_counter>100){
                     s_counter=0;
                     s_mode=1;
                  }
                  power1=0;
                  m_power1=0;
//                  breack1=100; 
                  if(breack1<150){
                     breack1=150; 
                  }
                  power2=0;
                  m_power2=0;
//                  breack2=100; 
                  if(breack2<150){
                     breack2=150; 
                  }
               break;
               case 1:
                  s_counter++;
                  if(s_counter>200){
                     s_counter=0;
                     s_mode=2;
                  }
                  power1=-150;
                  power2=-150;
               break;
               case 2:
                  s_counter++;
                  if(s_counter>100){
                     s_counter=0;
                     s_mode=3;
                  }
                  power1=0;
                  m_power1=0;
                  if(breack1<150){
                     breack1=150; 
                  }
                  power2=0;
                  m_power2=0;
                  if(breack2<150){
                     breack2=150; 
                  }
               break;
               case 3:
                  s_counter++;
                  if(s_counter>150){
                     s_counter=0;
                     s_mode=4;
                  }
                  power2=-150;
                  power1=150;
               break;
               case 4:
                  stop_mode=0;
               break;
               case 5:
               break;
               case 6:
               break;
            }
         break;
         case 3:
            switch(s_mode){
               case 0:
                  s_counter++;
                  if(s_counter>1500){
                     s_counter=0;
                     s_mode=1;
                  }
                  power1=0;
                  m_power1=0;
                  if(breack1<50){
                     breack1=50; 
                  }
                  power2=0;
                  m_power2=0;
                  if(breack2<50){
                     breack2=50; 
                  }
               break;
               case 1:
                  s_counter++;
                  if(s_counter>100){
                     s_counter=10;
                     if((l[2]==0)&&(l[3]==0)){
                        stop_mode=0;
                        s_mode=2;
                     }
                  }
               break;
               case 2:
               break;
               case 3:
               break;
               case 4:
               break;
               case 5:
               break;
               case 6:
               break;
            }
         
         break;
         default:
         break;
      }
   }
   else{
      power1=0;
      power2=0;
   }
      c_counter++;
      if(c_counter>100){
         c_counter=100;
//         cap[4]=0;
      }
      if(start_signal==0){
         power1=0;
         power2=0;
      }
      pow1=power1;
      pow2=power2;
      
}


signed int16 m0=0,m1=0,m2=0,m3=0,m4=0,m5=0,m6=0; 

unsigned int8 s0,s1=0,s2=0,s3=0;
int8 sdata[3],wifi_rx[250];


#INT_RDA2
void  rda2_isr(void) 
{
   s0=getc(U1);
   if(s1<250){
       wifi_rx[s1]=s0;
       s1++;
   }
   s2=0;
}

int16 mc0=0,mc1=0;
signed int16 temp,angel;
signed int32 temp1=0,temp2=0,temp3=0;

void gyro_read(){
   temp=make16(mpu6050_read(0x47),mpu6050_read(0x48));
   temp=temp+6;
   temp1=temp;
   temp2=temp2+temp1;
   temp3=(temp2/16110);
   angel=temp3;
}

unsigned int8 wifi_mode=0;
unsigned int16 wf0=0,wf1=0,wf2=0,wf3=0; 
char str_data[100];
void wifi_task(){
   switch(wifi_mode){
      case 0:
         if(wf0==0){
            str_data="AT\r\n";
            for(f0=0;f0<4;f0++){
               s_data[s_data_in]=str_data[f0];
               s_data_in++;
               if(s_data_in>199){
                  s_data_in=0;
               }
            }
         }
         wf0++;
         if(wf0>1000){
            wf0=0;
         }
      break;
      case 1:
      break;
      case 2:
      break;
      case 3:
      break;
      case 4:
      break;
      case 5:
      break;
      case 6:
      break;
      case 7:
      break;
      case 8:
      break;
      default:
      break;
   }
}
void main()
{
  // setup_timer2(TMR_INTERNAL | TMR_DIV_BY_8, 249);
  // setup_timer4(TMR_INTERNAL | TMR_DIV_BY_8, 1250);  1ms
    setup_timer4(TMR_INTERNAL | TMR_DIV_BY_8,999); //400.8us
  //setup_timer2(TMR_INTERNAL | TMR_DIV_BY_8,255);
    setup_timer2(TMR_INTERNAL | TMR_DIV_BY_8,249);  //TMR_DIV_BY_64  //  102.4us
    //setup_adc_ports(sAN15 | sAN14 | sAN13 | sAN12 | sAN11 | sAN10 | sAN9,VSS_VDD);
//    setup_adc_ports(sAN14 | sAN13 | sAN10 | sAN9,VSS_VDD);
  // setup_adc_ports(sAN8 | sAN9 | sAN10 | sAN11, VSS_VDD);
//   setup_adc(ADC_CLOCK_DIV_16 | ADC_TAD_MUL_2);
   
   setup_compare(2, COMPARE_PWM | COMPARE_TIMER2);
   set_pwm_duty(2,0);
   setup_compare(5, COMPARE_PWM | COMPARE_TIMER2);
   set_pwm_duty(5,0);

   
   enable_interrupts(INT_TIMER4);
//   enable_interrupts(INT_RDA2);
   enable_interrupts(INTR_GLOBAL);

   select1=1;
   select2=1;
   select3=1;
   select4=1;

   set_pullup(TRUE,PIN_F4);
   set_pullup(TRUE,PIN_B4);


   
   delay_ms(100);
  // out4   =   0;
  // out7   =   0;
   
   SET_TRIS_b(0xf7ff); // 1 bol orolt
   SET_TRIS_c(0x9fff);
   SET_TRIS_D(0xff00);
   SET_TRIS_e(0xFffa);
   set_tris_f(0xfff4);
//   set_tris_g(0x0e3c);
   
   for(f0=0;f0<12;f0++){
      led_out[f0]=0;
   }
 
  cntrl_tris=1;
  btn1_tris=1;
  
   delay_ms(200);
   led_out[1]=1;
   led_out[0]=1;
  
   delay_ms(200);
   led_out[10]=1;
   led_out[9]=1;
   led_out[3]=1;
   led_out[8]=1;
   led_out[6]=1;
   led_out[2]=1;
   led_out[7]=1;
   led_out[5]=1;
   led_out[4]=1;
   led_out[11]=1;
   delay_ms(200);
   
   
//  enable_interrupts(INT_RDA2);
  
   for(f0=0;f0<12;f0++){
     led_out[f0]=0;
   }

//   mpu6050_init();

while(TRUE)
{
   if(t0==1){
      t0=0;
      if(btn1==0){
         if(k[0]<100){
            k[0]++;
         }
         if(k[0]==20){
            user_mode++;
            if(user_mode>4){
               user_mode=0;
            }
         }
      }
      else{
         k[0]=0;
      }
      if(btn2==0){
         if(k[1]<100){
            k[1]++;
         }
         if(k[1]==20){
            if(mic_mode==1){
               mic_mode=0;
            }
            else{
               mic_mode=1;
               
            }
         }
      }
      else{
         k[1]=0;
      }
//      gyro_read();
      t1++;
      if(t1>100){
         t1=0;
//         printf("hello=%d\r\n",make16(mpu6050_read(0x47),mpu6050_read(0x48)));
      }
      read_s();
      line_sens();
      if(btn1==0){
         led_out[4]=0;
         led_out[3]=0;
         led_out[6]=0;
         led_out[7]=0;
         if(user_mode==1){
            led_out[4]=1;
         }
         if(user_mode==2){
            led_out[3]=1;
         }
         if(user_mode==3){
            led_out[6]=1;
         }
         if(user_mode==4){
            led_out[7]=1;
         }
      }
//      if(btn2==0){
         if(mic_mode==1){
            led_out[11]=10;
         }
//      }
      
      if(s[7]==0){
         mode=0;
      }
      switch(mode){
         case 0:
            if(s[7]>1){
               mc0=0;
               s[1]=0;
               s[2]=0;
               s[3]=0;
               if(mic_mode==1){
                  if(mc1<15000){
                     mc1++;
                  }
                  else{
                     if(user_mode==2){
                        mode=15;
                     }
                     if(user_mode==1){
                        mode=11;
                     }
                     if(user_mode==4){
                        mode=11;
                     }
                     if(user_mode==3){
                        mode=15;
                     }
                     if(user_mode==0){
                        mode=1;
                     }
                  }
               }
               else{
                  if(user_mode==2){
                     mode=5;
                  }
                  if(user_mode==1){
                     mode=8;
                  }
                  if(user_mode==4){
                     mode=11;
                  }
                  if(user_mode==3){
                     mode=15;
                  }
                  if(user_mode==0){
                     mode=1;
                  }
               }
            }
            else{
               mc1=0;
               
            }
            power1=0;
            power2=0;
         break;
         case 1:
            mc0++;
            if(mc0>600){
               mc0=0;
               mode=1;
            }
            power1=251;
            power2=251;
         break;
         case 2:
            mc0++;
            if(mc0>1000){
               mc0=0;
               mode=3;
            }
            power1=0;
            power2=0;
         break;
         case 3:
            mc0++;
            if(mc0>600){
               mc0=0;
               mode=4;
            }
//            power1=-250;
//            power2=-250;
         break;
         case 4:
            mc0++;
            if(mc0>1000){
               mc0=0;
               mode=0;
            }
            power1=0;
            power2=0;
         break;
         case 5:
            mc0++;
            if(mc0>350){
               mc0=0;
               mode=6;
            }
            else{
               if(mc0>200){
                  power1=-251;
                  power2=30;
               }
               else{
                  power1=0;
                  power2=0;
               }
            }
               s[1]=0;
               s[2]=0;
               s[3]=0;
         break;
         case 6:
            mc0++;
            if(mc0>150){
               mc0=0;
               mode=7;
               mc1=0;               
            }
            power1=-251;
            power2=-251;
               s[1]=0;
               s[2]=0;
               s[3]=0;
         break;
         case 7:
            mc0++;
            if(mc0>5){
               mc0=5;
               if((s[2]>10)||(s[4]>10)||(s[3]>10)||(s[0]>10)||(s[1]>10)){
                  mc0=0;
                  mode=1;
               }
               if(mc1<10000){
                  mc1++;
               }
               else{
                  mc0=0;
                  mode=1;
               }
            }
            power1=0;
            power2=0;
         break;
         case 8:
            mc0++;
            if(mc0>350){
               mc0=0;
               mode=9;
            }
            else{
               if(mc0>200){
                  power1=30;
                  power2=-251;
               }
               else{
                  power1=0;
                  power2=0;
               }
            }
               s[1]=0;
               s[2]=0;
               s[3]=0;
         break;
         case 9:
            mc0++;
            if(mc0>150){
               mc0=0;
               mode=10;
               mc1=0;               
            }
            power1=-251;
            power2=-251;
               s[1]=0;
               s[2]=0;
               s[3]=0;
         break;
         case 10:
            mc0++;
            if(mc0>5){
               mc0=5;
               if((s[2]>10)||(s[4]>10)||(s[3]>10)||(s[0]>10)||(s[1]>10)){
                  mc0=0;
                  mode=1;
               }
               if(mc1<10000){
                  mc1++;
               }
               else{
                  mc0=0;
                  mode=1;
               }
            }
            power1=0;
            power2=0;
         break;
         case 11:
            mc0++;
            if(mc0>120){
               mc0=0;
               mode=12;
            }
            power1=-20;
            power2=251;
            s[1]=0;
            s[2]=0;
            s[3]=0;
            s[0]=0;
            s[4]=0;
         break;
         case 12:
            mc0++;
            if(mc0>300){
               mc0=0;
               mode=13;
            }
            power1=251;
            power2=251;
            s[1]=0;
            s[2]=0;
            s[3]=0;
            s[0]=0;
            s[4]=0;
         break;
         case 13:
            mc0++;
            if(mc0>200){
               mc0=0;
               mode=14;
            }
            power1=251;
            power2=0;
            s[1]=0;
            s[2]=0;
            s[3]=0;
            s[0]=0;
            s[4]=0;
         break;
         case 14:
            mc0++;
            if(mc0>300){
               mc0=300;
               mode=1;
//               power1=0;
//               power2=0;
            }
            else{
               power1=251;
               power2=251;
            }
         break;
         case 15:
            mc0++;
            if(mc0>120){
               mc0=0;
               mode=16;
            }
            power1=251;
            power2=-20;
            s[1]=0;
            s[2]=0;
            s[3]=0;
            s[0]=0;
            s[4]=0;
         break;
         case 16:
            mc0++;
            if(mc0>300){
               mc0=0;
               mode=17;
            }
            power1=251;
            power2=251;
            s[1]=0;
            s[2]=0;
            s[3]=0;
            s[0]=0;
            s[4]=0;
            
         break;
         case 17:
            mc0++;
            if(mc0>200){
               mc0=0;
               mode=18;
            }
            power1=0;
            power2=251;
            s[1]=0;
            s[2]=0;
            s[3]=0;
            s[0]=0;
            s[4]=0;
         break;
         case 18:
            mc0++;
            if(mc0>300){
               mc0=300;
               mode=1;
//               power1=0;
//               power2=0;
            }
            else{
               power1=251;
               power2=251;
            }
         break;
         default:
             mode=0;
         break;
      }
      if(s[0]>10){
          power2=0;
      }
      else if(s[1]>10){
          power2=power2*10;
          power2=power2/15;
      }
      if(s[4]>10){
          power1=0;
      }else if(s[3]>10){
          power1=power1*10;
          power1=power1/15;
      }
      if(s[2]>10){
         if(power1<power2){
            power1=power2;
         }
         if(power2<power1){
            power2=power1;
         }
      }
      control();
      if(s2<15){
         s2++;
         if(s2==5){
            s2=20;
            s3=1;
         }
      }
      else{
         s1=0;
      }
//      wifi_task();
   }
   if(s_data_out!=s_data_in){
      if(U2TBF_bit==0){
         test_pin=1;
          putc(s_data[s_data_out],U1);
          s_data_out++;
          if(s_data_out>199){
            s_data_out=0;
          }
         test_pin=0;
      }
   }
   if(mic_pin==0){
      mic_mode=0;
      led_out[11]=10;
   }
//!   power1=250;
//!   power2=250;
//!   led_out[1]=1;
//!   led_out[0]=1;
//!   delay_ms(2000);
//!   power1=0;
//!   power2=0;
//!   led_out[1]=0;
//!   led_out[0]=0;
//!   led_out[9]=0;
//!   led_out[10]=0;
//!   delay_ms(1000);
//!   power1=-250;
//!   power2=-250;
//!   led_out[9]=1;
//!   led_out[10]=1;
//!   delay_ms(2000);
//!   power1=0;
//!   power2=0;
//!   led_out[1]=0;
//!   led_out[0]=0;
//!   led_out[9]=0;
//!   led_out[10]=0;
//!   delay_ms(1000);
//!   
}
}
/*
 if(t0==1){
   t0=0;
   if(!control) {
      led_out[11]=0;
      cansel=1;
   }
   else{
      first=1; 
      led_out[11]=1;
      set=1;
      cansel=0; 
   }
   if(cansel && first){
      reset_cpu();
   }
   read_s();
   if(set){
       if(mode==1) go();                                 // L1
       if(mode==2) go_forward();   // go_manual();       // R1
       if(mode==3) go_angle_forward();                   // L2
       if(mode==4) go_back();                            // R2
   }
   else {
      if(!up && btn1_state){ 
              mode++;
              btn1_state=0;
      }
      if(up) btn1_state=1;
   
      if(mode>4) mode=0;
              
      if(mode>0){
         if(mode==1){      
            led_out[0]=1;
            led_out[1]=0; 
            led_out[9]=0;
            led_out[10]=0;
         }
         if(mode==2){
            led_out[0]=0;
            led_out[1]=1; 
            led_out[9]=0;
            led_out[10]=0;
         }
         if(mode==3){     
            led_out[0]=0;
            led_out[1]=0; 
            led_out[9]=0;
            led_out[10]=1;
         }
         if(mode==4){     
            led_out[0]=0;
            led_out[1]=0; 
            led_out[9]=1;
            led_out[10]=0;
         }
      } 
   }
}
*/
