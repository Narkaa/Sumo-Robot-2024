
#inline
void io_int(){

   led_fr =  0;
   led_fl =  0;
   led_rl =  0;
   led_rr =  0;
   
   led_5  =  0;
   led_4  =  0;
   led_7  =  0;
   led_6  =  0;
   led_2  =  0;
   led_1  =  0;
   led_3  =  0;
   led_8  =  0;

   m1_up    =  0;
   m1_down  =  0;
   m2_up    =  0;
   m2_down  =  0;

   SET_TRIS_a(0xb93f);
   SET_TRIS_b(0xffff);
   SET_TRIS_c(0x9fe1);
   SET_TRIS_D(0xffc0);
   set_tris_f(0xff4c);
   set_tris_g(0x0e3c);
   
   for(f0=0;f0<12;f0++){
      led_out[f0]=0;
   }
   

}

#inline
void key_scan(){

      if(key_up==0){
         k[0]++;
         if(k[0]>100){
            k[0]=100;
         }
      }
      else{
         k[0]=0;
      }
      if(key_dn==0){
         k[1]++;
         if(k[1]>100){
            k[1]=100;
         }
      }
      else{
         k[1]=0;
      }
      if(key_ok==0){
         k[2]++;
         if(k[2]>100){
            k[2]=100;
         }
      }
      else{
         k[2]=0;
      }
}

void hex_dec(unsigned int16 temp1){
   unsigned int16 e0;
   unsigned int8 e3;
   for(e3=0;e3<2;e3++){
      e0=temp1/10;
      dec[e3]=temp1-e0*10;
      temp1=e0;
   }
}

#inline
void read_sharp(){

   set_adc_channel(12);
   delay_us(20);
   r_adc[12]+=read_adc();

/*
   set_adc_channel(2);
   delay_us(2);
   r_adc[2] += read_adc();

   set_adc_channel(3);
   delay_us(2);
   r_adc[3] += read_adc();

   set_adc_channel(4);
   delay_us(2);
   r_adc[4] += read_adc();

   set_adc_channel(5);
   delay_us(2);
   r_adc[5] += read_adc();

   set_adc_channel(12);
   delay_us(2);
   r_adc[12] += read_adc();

   set_adc_channel(13);
   delay_us(2);
   r_adc[13] += read_adc();

   set_adc_channel(14);
   delay_us(2);
   r_adc[14] += read_adc();

   set_adc_channel(15);
   delay_us(2);
   r_adc[15] += read_adc();
*/
/*
   a0++;
   if(a0>9){
      a0=0;
      
      adc[2]=r_adc[2]/10;
      adc[3]=r_adc[3]/10;
      adc[4]=r_adc[4]/10;
      adc[5]=r_adc[5]/10;
      adc[12]=r_adc[12]/10;
      adc[13]=r_adc[13]/10;
      adc[14]=r_adc[14]/10;
      adc[15]=r_adc[15]/10;

      r_adc[2]=0;
      r_adc[3]=0;
      r_adc[4]=0;
      r_adc[5]=0;
      r_adc[12]=0;
      r_adc[13]=0;
      r_adc[14]=0;
      r_adc[15]=0;
      
*/
   a0++;
   if(a0>9){
      a0=0;
      adc[12]=r_adc[12]/10;
      r_adc[12]=0;
      if(adc[12]>600){
         led_out[4]=1;
      }
      else{
         led_out[4]=0;
      }
      
   }
   
   if(ms0==0){
      led_out[9]=10;
      adc[2]=200;
      bit_set(sensor,7);
   }
   else{
      bit_clear(sensor,7);
      led_out[9]=0;
      adc[2]=0;         
   }
   
   if(ms1==0){
      led_out[11]=10;
      adc[3]=200;         
      bit_set(sensor,5);
   }
   else{
      adc[3]=0;         
      led_out[11]=0;
      bit_clear(sensor,5);
   }
   
   if(ms5==0){
      adc[4]=200;         
      led_out[10]=10;
      bit_set(sensor,6);
   }
   else{
      led_out[10]=0;
      adc[4]=0;         
      bit_clear(sensor,6);
   }
   
   if(ms2==0){
      led_out[6]=10;
      adc[13]=200;         
      bit_set(sensor,1);
   }
   else{
      led_out[6]=0;
      adc[13]=0;         
      bit_clear(sensor,1);
   }
   if(ms6==0){
      led_out[5]=10;
      adc[14]=200;         
      bit_set(sensor,2);
   }
   else{
      led_out[5]=0;
      adc[14]=0;         
      bit_clear(sensor,2);
   }
   if(ms7==0){
      led_out[7]=10;
      adc[15]=200;         
      bit_set(sensor,0);
   }
   else{
      led_out[7]=0;
      adc[15]=0;         
      bit_clear(sensor,0);
   }
}

#inline
void line_sens(){

   if(li1==0){
      if(l[0]<100){
         l[0]++;
      }
   }
   else{
      l[0]=0;
   }
   led_out[0]=l[0]/10;

   if(li2==0){
      if(l[1]<100){
         l[1]++;
      }
   }
   else{
      l[1]=0;
   }
   led_out[1]=l[1]/10;

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

   l[2]=0;
   l[3]=0;

}

