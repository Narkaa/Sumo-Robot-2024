unsigned int16 rd=0,rd0=0,rd1=0,rd2=0,rd3=0;
unsigned int8 wifi_rx[400];
unsigned int8 wifi_out_data[5][60],wifi_tx0,wifi_tx1;


int8 wifi_mode,sms_mode,t_mode,gprs_mode,gprs_reset,dtmf_r;
//uint8_t a_level,ip0,ip1,ip2,ip3,sms_num[10],send_num[10];
int16 ws0,ws1,ws2;
unsigned int8 cmd_srt[50];
unsigned int8 cr,sel=0,cmd=0,mmd=0,gmd=0;
unsigned int16 rcounter_1,rcounter_2;
unsigned int8 dec[6];

int16 test,temp[5];
int16 block,did,bak,tled,m_sensor,f_sensor; 

//extern UART_HandleTypeDef huart1;

int8 check(char ch[15],unsigned int8 c2,unsigned int8 c0){
   for(unsigned int8 c1=0;c1<c0;c1++){
//      HAL_fputc1(ch[c1],&huart1);
       if(wifi_rx[c2]==ch[c1]){
            c2++;
       }
       else{
            c1=c0;
            c2=0;
       }
   }
   return c2;
}

void wifi_read_command(){
unsigned int8 w0,w1,w2,w3,w4;
   if(wifi_rx[0]>1){
       if(wifi_rx[1]=='+'){
            if(check("IPD,",2,4)){
               w1=0;
               w2=6;
               for(w0=0;w0<3;w0++){
                  w1=w1*10;
                  w1+=wifi_rx[w2]&0x0f;
                  w2++;
                  if((wifi_rx[w2]<0x30)||(wifi_rx[w2]>0x39)){
                     w0=3;
                  }   
               }
               if(w1<10){
                  tcp_last=w1;
                  w2++;
                  w1=0;
                  for(w0=0;w0<3;w0++){
                     w1=w1*10;
                     w1+=wifi_rx[w2]&0x0f;
                     w2++;
                     if((wifi_rx[w2]<0x30)||(wifi_rx[w2]>0x39)){
                        w0=3;
                     }   
                  }
                  w2++;
                  s1=0;
                  for(w0=0;w0<w1;w0=w0+2){
                     w3=wifi_rx[w2]&0x0f;
                     w2++;
                     w4=wifi_rx[w2]&0x0f;
                     w2++;
                     w3=w3<<4;
                     s_data[s1]=w3|w4;
                     s1++;
                  }
                 s2=3;
               }
            }
            wifi_rx[0]=0;
       }
       else{
            if(check("OK",1,2)){
               cmd=1;
               mmd=1;
               wifi_rx[0]=0;
            }
            if(check("CONNECT",3,7)){
               cmd=2;
               wifi_rx[0]=0;
               w1=wifi_rx[1]&0x0f;
               if(w1<10){
                  tcp_order[w1]=1;
                  tcp_last=w1;
                  w0=0;
                  for(w1=0;w1<10;w1++){
                     if(tcp_order[w1]>0){
                        w0++;
                     }
                  }
                  tcp_total=w0;
               }
            }
            if(check("CLOSED",3,6)){
               cmd=3;
               wifi_rx[0]=0;
               w1=wifi_rx[1]&0x0f;
               if(w1<10){
                  tcp_order[w1]=0;
                  tcp_last=w1;
                  w0=0;
                  for(w1=0;w1<10;w1++){
                     if(tcp_order[w1]>0){
                        w0++;
                     }
                  }
                  tcp_total=w0;
               }
            }
            if(check(">",1,2)){
               cmd=4;
               wifi_rx[0]=0;
            }
            if(check("SEND OK",1,7)){
               cmd=5;
               wifi_rx[0]=0;
            }
       }
   }
}

void send_cmd(char str[20],int8_t check_cmd,int8_t wait_time,int8_t repear,int8_t back_mode,int8_t go_mode){
uint8_t sv;
   if(ws0==0){
      f1=1;
         for(f0=0;f0<60;f0++){
            sv=str[f0];
            wifi_out_data[wifi_tx0][f1]=sv;
             if(sv==0x0a){
                  wifi_out_data[wifi_tx0][0]=f1;
                  wifi_tx0++;
                  if(wifi_tx0>4){
                     wifi_tx0=0;
                  }
                  f0=50;
             }
             f1++;
      }
      cmd=0;
      ws0++;   
   }
   else{
      ws0++;   
      if(cmd==check_cmd){
         cmd=0;
             if(wifi_mode!=go_mode){
               wifi_mode=go_mode;
               ws0=0;
               ws1=0;
             }
      }
   }
   if(ws0>((wait_time*25)+25)){
      ws0=0;
      ws1++;
      if(ws1>repear){
         wifi_mode=back_mode;
      }
   }
}



void wifi_init(){
   switch(wifi_mode){
      case 0:// power on
//         HAL_GPIO_WritePin(NRESET_GPIO_Port,NRESET_Pin,GPIO_PIN_RESET);//gsm_reset=0;
//         if(HAL_GPIO_ReadPin(STATUS_GPIO_Port,STATUS_Pin)==0){ //gsm_status==0){
            ws0++;
            if(ws0>50){
               wifi_mode=1;
               ws0=0;
               ws1=0;
                     d_mode=9;
            }
//         }
      break;
      case 1:
            HAL_GPIO_WritePin(RM_M1_GPIO_Port,RM_M1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(RM_M2_GPIO_Port,RM_M2_Pin,GPIO_PIN_SET);
//         HAL_GPIO_WritePin(NRESET_GPIO_Port,NRESET_Pin,GPIO_PIN_SET);//         gsm_reset=1;
         ws0++;
         if(ws0>200){
//                  if(HAL_GPIO_ReadPin(STATUS_GPIO_Port,STATUS_Pin)==1){ //            if(gsm_status==1){
               if(ws0>300){
                  wifi_mode=2;
                  ws0=0;
                  ws1=0;
               }
  //          }
/*            else{
               if(ws0>300){
                  wifi_mode=0;
                  ws0=0;
               }
            }*/
         }
      break;
      case 2:
//         strcpy(cmd_srt,"AT\r\n");
        send_cmd("AT\r\n",1,1,3,0,3);
            d_mode=9;
      break;
      case 3:
         strcpy(cmd_srt,"ATE0\r\n");
         send_cmd(cmd_srt,1,1,3,2,4);
      break;
      case 4:
         strcpy(cmd_srt,"AT+CIPAP=\"192.168.10.1\"\r\n");
         send_cmd(cmd_srt,1,1,3,2,5);
      break;
      case 5:
         strcpy(cmd_srt,"AT+CWMODE=2\r\n");
         send_cmd(cmd_srt,1,1,3,2,6);
      break;
      case 6:
         strcpy(cmd_srt,"AT+CWSAP=\"Access control LIFT\",\"93161616\",11,4\r\n");
         send_cmd(cmd_srt,1,3,3,2,7);
      break;
      case 7:
         strcpy(cmd_srt,"AT+CIPMUX=1\r\n");
         send_cmd(cmd_srt,1,3,3,2,8);
      break;
      case 8:
         strcpy(cmd_srt,"AT+CIPSERVER=1,50000\r\n");
         send_cmd(cmd_srt,1,3,3,2,9);
               wifi_on=2;
      break;
      case 9:
            if(tcp_total>0){
               if(serial_out[0]>0){
                  wifi_mode=11;
                  ws0=0;
                  ws1=0;
               }
            }
      break;
      case 10:
         send_cmd("AT\r\n",1,3,3,2,11);
      break;
      case 11:
        //send_cmd("AT\r",1,3,3,2,11);
            wifi_out_data[wifi_tx0][1]='A';
            wifi_out_data[wifi_tx0][2]='T';
            wifi_out_data[wifi_tx0][3]='+';
            wifi_out_data[wifi_tx0][4]='C';
            wifi_out_data[wifi_tx0][5]='I';
            wifi_out_data[wifi_tx0][6]='P';
            wifi_out_data[wifi_tx0][7]='S';
            wifi_out_data[wifi_tx0][8]='E';
            wifi_out_data[wifi_tx0][9]='N';
            wifi_out_data[wifi_tx0][10]='D';
            wifi_out_data[wifi_tx0][11]='=';
            wifi_out_data[wifi_tx0][12]=tcp_last+0x30;
            wifi_out_data[wifi_tx0][13]=',';
            ws0=14;
            ws2=serial_out[0];
            for(ws1=0;ws1<3;ws1++){
               wifi_out_data[wifi_tx0][ws0+2]=wifi_out_data[wifi_tx0][ws0+1];
               wifi_out_data[wifi_tx0][ws0+1]=wifi_out_data[wifi_tx0][ws0];
               wifi_out_data[wifi_tx0][ws0]=0x30+(ws2%10);
               ws2=ws2/10;
               if(ws2==0){
                  ws0+=ws1+1;
                  ws1=3;
               }
            }
             wifi_out_data[wifi_tx0][ws0]=0x0d;
            ws0++;
            wifi_out_data[wifi_tx0][ws0]=0x0a;
            wifi_out_data[wifi_tx0][0]=ws0;
            wifi_tx0++;
            if(wifi_tx0>4){
               wifi_tx0=0;
            }
        ws1=0;
        wifi_mode=12;      
            cmd=0;
      break;
      case 12:
            ws1++;
            if(ws1>1000){
               wifi_mode=9;
            }
            if(cmd==1){
               HAL_UART_Transmit_DMA(wifi,&serial_out[1],serial_out[0]);
               ws1=0;
               cmd=0;
               wifi_mode=13;
            }
      break;
      case 13:
            ws1++;
            if(ws1>1000){
               wifi_mode=9;
            }
            if(cmd==5){
               serial_out[0]=0;
               ws1=0;
               cmd=0;
               wifi_mode=9;
            }
      break;
      default:
         wifi_mode=0;
      break;
   }
}

uint16_t sm0,sm1; 
int16_t hex_string(int8_t p0){
int8_t p1,p2;
int16_t p3;
      p1=p0&0x0f;
      if(p1>9){
         p1=p1-9;
         p1=p1|0x40;
      }
      else{
         p1=p1|0x30;
      }
         p0=p0>>4;
      p2=p0&0x0f;
      if(p2>9){
         p2=p2-9;
         p2=p2|0x40;
      }
      else{
         p2=p2|0x30;
      }
      p3=make16(p2,p1);
      return p3;
}

int8_t string_hex(uint8_t p0,uint8_t p1){
   if(p0>0x40){
      p0=p0&0x0f;
      p0=p0+9;
         p0=p0<<4;
   }
   else{
      p0=p0&0x0f;
         p0=p0<<4;
   }
   if(p1>0x40){
      p1=p1&0x0f;
      p1=p1+9;      
   }
   else{
      p1=p1&0x0f;
   }
   p0=p0|p1;
   return p0;
}

int16_t add;






