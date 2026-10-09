void go_manual(){
if (state){
    state=0;
 if(UlineR || ULineL  ){
         power1=-200;
         m_power1=-200;
         breack1=200;
         power2=-200;
         m_power2=-200;
         breack2=200;
                cmd=0;     //cmd=0;  
                 if(UlineR && UlineL)    line_set=3;
                      else if(UlineR)    line_set=2;
                                 else    line_set=1;
   }          
 else  if(AlineR || ALineL  ){
                cmd=1;    // cmd=1;
                 if(AlineR && AlineL)    line_set=3;
                      else if(AlineR)    line_set=2;
                                 else    line_set=1;
                   }  
      else   {
             cmd=2;
       }
}
    switch(cmd){
     case 0:
     
                 if(line_set==3 ){
                  if(cnt<300) set_motor_go(back);
                       else if(cnt<650) set_motor_go(right);
                                else { cnt=0;
                                       state=1;
                                       set_motor_go(stop);
                                }
                 }
                  if(line_set==2 ){

                  if(cnt<300) set_motor_go(back );
                       else if(cnt<650) set_motor_go(left);
                          // else if(cnt<800) set_motor_go(forward);
                                 else { cnt=0;
                                         state=1;
                                        set_motor_go(stop);
                                }
                }
                if(line_set==1 ){
                  if(cnt<300) set_motor_go(back);
                     else if(cnt<650) set_motor_go(right);
                      // else if(cnt<800) set_motor_go(forward);
                               else { cnt=0;
                                      state=1;
                                      set_motor_go(stop);
                                }
                }
                
              cnt++;
             
     break;
          case 1:
               if(line_set==3 ){
                    if(cnt<200) set_motor_go(forward);
                      //else if(cnt<200) set_motor_go(right);
                                else { cnt=0;
                                       state=1;
                                     // set_motor_go(stop);
                        }
                }
                if(line_set==2 ){

                  if(cnt<200) set_motor_go(forward);
                       else if(cnt<250) set_motor_go(left);
                               // else if(cnt<700) set_motor_go(forward);
                                   else { cnt=0;
                                         state=1;
                                    //    set_motor_go(stop);
                                }
                }
                if(line_set==1 ){
                  if(cnt<200) set_motor_go(forward);
                       else if(cnt<250) set_motor_go(right);
                              //  else if(cnt<1000) set_motor_go(right);
                                   else { cnt=0;
                                         state=1;
                                      //  set_motor_go(stop);
                                }
                }
              cnt++;  
               
     break;
         case 2:
         cnt=0;
         state=1;
         set_motor_go(motor_go);
       break;
    } 
}

void go_forward(){

   if(state){     
      state=0;
      
 if(UlineR || ULineL  ){
         power1=-150;
         m_power1=-150;
         breack1=100;
         power2=-150;
         m_power2=-150;
         breack2=100;
         cmd=0;     //cmd=0;  
                 if(UlineR && UlineL)    line_set=3;
                      else if(UlineR)    line_set=2;
                                 else    line_set=1;
   }          
 else  if(AlineR || ALineL  ){
                cmd=1;    // cmd=1;
                 if(AlineR && AlineL)    line_set=3;
                      else if(AlineR)    line_set=2;
                                 else    line_set=1;
                           }  
      else   {
               cmd=2;
               sensor_go_forward();
          }
}
    switch(cmd){
     case 0:
     
                  if(line_set==3 ){
                  if(cnt<300) set_motor_go(back);
                       else if(cnt<650) set_motor_go(right);
                                else { cnt=0;
                                       state=1;
                                       set_motor_go(stop);
                                       cmd=2;
                                }
                 }
                  if(line_set==2 ){

                  if(cnt<300) set_motor_go(back );
                       else if(cnt<650) set_motor_go(left);
                          // else if(cnt<800) set_motor_go(forward);
                                 else { cnt=0;
                                         state=1;
                                         set_motor_go(stop);
                                         cmd=2;
                                }
                }
                if(line_set==1 ){
                  if(cnt<300) set_motor_go(back);
                     else if(cnt<650) set_motor_go(right);
                      // else if(cnt<800) set_motor_go(forward);
                               else { cnt=0;
                                      state=1;
                                      set_motor_go(stop);
                                      cmd=2;
                                }
                }
                
              cnt++;
             
     break;
          case 1:
               if(line_set==3 ){
                    if(cnt<200) set_motor_go(forward);
                      //else if(cnt<200) set_motor_go(right);
                                else { cnt=0;
                                       state=1;
                                       set_motor_go(stop);
                                       cmd=2;
                        }
                }
                if(line_set==2 ){

                  if(cnt<200) set_motor_go(forward);
                       else if(cnt<250) set_motor_go(left);
                               // else if(cnt<700) set_motor_go(forward);
                                   else { cnt=0;
                                          state=1;
                                          set_motor_go(stop);
                                          cmd=2;
                                }
                }
                if(line_set==1 ){
                  if(cnt<200) set_motor_go(forward);
                       else if(cnt<250) set_motor_go(right);
                              //  else if(cnt<1000) set_motor_go(right);
                                   else { cnt=0;
                                         state=1;
                                         set_motor_go(stop);
                                         cmd=2;
                            }
                }
              cnt++;  
               break;
       case 2:
    if(UlineR || ULineL  ){
         power1=-150;
         m_power1=-150;
         breack1=100;
         power2=-150;
         m_power2=-150;
         breack2=100;
        
                cmd=0;     //cmd=0;  
                 if(UlineR && UlineL)    line_set=3;
                      else if(UlineR)    line_set=2;
                                 else    line_set=1;
   }
   else{
        if(cnt<s_go_time ) {
           set_motor_go(s_go);
           if(C){
           set_motor_go(forward_fast);
           }
        }
                  else {
                   cnt=0;
                   state=1;
                   set_motor_go(stop);
                 }
           cnt++;
   }
        break;
   case 3:
          
       /* if(cnt<150) set_motor_go(forward_right);
                       else if(cnt<500) set_motor_go(forward);
                           else if(cnt<1000) set_motor_go(left_go);
                                else {  
                        set_motor_go(stop);
                        cmd=3;
                        cnt=0;
                        state=1;
                        first=0;
                     }
                cnt++;
         */       
       break;
     } 
}

void go_angle_forward(){

 if(state){     
      state=0;
      
 if(UlineR || ULineL  ){
         power1=-150;
         m_power1=-150;
         breack1=100;
         power2=-150;
         m_power2=-150;
         breack2=100;
        
                cmd=0;     //cmd=0;  
                 if(UlineR && UlineL)    line_set=3;
                      else if(UlineR)    line_set=2;
                                 else    line_set=1;
   }          
 else  if(AlineR || ALineL  ){
                cmd=1;    // cmd=1;
                 if(AlineR && AlineL)    line_set=3;
                      else if(AlineR)    line_set=2;
                                 else    line_set=1;
                           }  
      else   {
               cmd=2;
               sensor_go_forward();
          }
   if(first==1) cmd=3;      
}
    switch(cmd){
     case 0:
     
                 if(line_set==3 ){
                  if(cnt<300) set_motor_go(back);
                       else if(cnt<650) set_motor_go(right);
                                else { cnt=0;
                                       state=1;
                                       set_motor_go(stop);
                                       cmd=2;
                                }
                 }
                  if(line_set==2 ){

                  if(cnt<300) set_motor_go(back );
                       else if(cnt<650) set_motor_go(left);
                          // else if(cnt<800) set_motor_go(forward);
                                 else { cnt=0;
                                         state=1;
                                         set_motor_go(stop);
                                         cmd=2;
                                }
                }
                if(line_set==1 ){
                  if(cnt<300) set_motor_go(back);
                     else if(cnt<650) set_motor_go(right);
                      // else if(cnt<800) set_motor_go(forward);
                               else { cnt=0;
                                      state=1;
                                      set_motor_go(stop);
                                      cmd=2;
                                }
                }
                
              cnt++;
             
     break;
          case 1:
               if(line_set==3 ){
                    if(cnt<200) set_motor_go(forward);
                      //else if(cnt<200) set_motor_go(right);
                                else { cnt=0;
                                       state=1;
                                       set_motor_go(stop);
                                       cmd=2;
                        }
                }
                if(line_set==2 ){

                  if(cnt<200) set_motor_go(forward);
                       else if(cnt<250) set_motor_go(left);
                               // else if(cnt<700) set_motor_go(forward);
                                   else { cnt=0;
                                          state=1;
                                          set_motor_go(stop);
                                          cmd=2;
                                }
                }
                if(line_set==1 ){
                  if(cnt<200) set_motor_go(forward);
                       else if(cnt<250) set_motor_go(right);
                              //  else if(cnt<1000) set_motor_go(right);
                                   else { cnt=0;
                                         state=1;
                                         set_motor_go(stop);
                                         cmd=2;
                            }
                }
              cnt++;  
               
     break;
       case 2:
    if(UlineR || ULineL  ){
         power1=-150;
         m_power1=-150;
         breack1=100;
         power2=-150;
         m_power2=-150;
         breack2=100;
        
                cmd=0;     //cmd=0;  
                 if(UlineR && UlineL)    line_set=3;
                      else if(UlineR)    line_set=2;
                                 else    line_set=1;
   }
 else{  
        if(cnt<s_go_time ) {
           set_motor_go(s_go);
           if(C){
           set_motor_go(forward_fast);
           }
        }
                  else {
                   cnt=0;
                   state=1;
                   set_motor_go(stop);
                 }
           cnt++;
 }  
        break;
   case 3:
      //  if(cnt<200) set_motor_go(forward_right);
      //           else if(cnt<500) set_motor_go(forward_fast);
      //                   else if(cnt<1500) set_motor_go(left_go);
    if(cnt<50) {//set_motor_go(right);
    
             power1=250;               // left taliin motor1
             power2=-250;    
   }
      else  if(cnt<250) set_motor_go(forward_right);
                 else if(cnt<550) set_motor_go(forward_fast);
                         else if(cnt<1400) {
                                        //set_motor_go(left_go);
                                        power1= 130;
                                        power2= 250; 
                         }  
                         else {
                        set_motor_go(stop);
                        cmd=2;
                        cnt=0;
                        state=1;
                        first=0;
                     }
                     cnt++;            
       break;
     } 
}

void go_back(){

 if(state){     
      state=0;
      
 if(UlineR || ULineL  ){
         power1=-150;
         m_power1=-150;
         breack1=100;
         power2=-150;
         m_power2=-150;
         breack2=100;
        
                cmd=0;     //cmd=0;  
                 if(UlineR && UlineL)    line_set=3;
                      else if(UlineR)    line_set=2;
                                 else    line_set=1;
   }          
 else  if(AlineR || ALineL  ){
                cmd=1;    // cmd=1;
                 if(AlineR && AlineL)    line_set=3;
                      else if(AlineR)    line_set=2;
                                 else    line_set=1;
                           }  
      else   {
               cmd=2;
               sensor_go_forward();
          }
   if(first==1) cmd=3;      
}
    switch(cmd){
     case 0:
     
                 if(line_set==3 ){
                  if(cnt<300) set_motor_go(back);
                       else if(cnt<650) set_motor_go(right);
                                else { cnt=0;
                                       state=1;
                                       set_motor_go(stop);
                                       cmd=2;
                                }
                 }
                  if(line_set==2 ){

                  if(cnt<300) set_motor_go(back );
                       else if(cnt<650) set_motor_go(left);
                          // else if(cnt<800) set_motor_go(forward);
                                 else { cnt=0;
                                         state=1;
                                         set_motor_go(stop);
                                         cmd=2;
                                }
                }
                if(line_set==1 ){
                  if(cnt<300) set_motor_go(back);
                     else if(cnt<650) set_motor_go(right);
                      // else if(cnt<800) set_motor_go(forward);
                               else { cnt=0;
                                      state=1;
                                      set_motor_go(stop);
                                      cmd=2;
                                }
                }
                
              cnt++;
             
     break;
          case 1:
               if(line_set==3 ){
                    if(cnt<200) set_motor_go(forward);
                      //else if(cnt<200) set_motor_go(right);
                                else { cnt=0;
                                       state=1;
                                       set_motor_go(stop);
                                       cmd=2;
                        }
                }
                if(line_set==2 ){

                  if(cnt<200) set_motor_go(forward);
                       else if(cnt<250) set_motor_go(left);
                               // else if(cnt<700) set_motor_go(forward);
                                   else { cnt=0;
                                          state=1;
                                          set_motor_go(stop);
                                          cmd=2;
                                }
                }
                if(line_set==1 ){
                  if(cnt<200) set_motor_go(forward);
                       else if(cnt<250) set_motor_go(right);
                              //  else if(cnt<1000) set_motor_go(right);
                                   else { cnt=0;
                                         state=1;
                                         set_motor_go(stop);
                                         cmd=2;
                            }
                }
              cnt++;  
               
     break;
       case 2:
     
      
      
   if(UlineR || ULineL  ){
         power1=-150;
         m_power1=-150;
         breack1=100;
         power2=-150;
         m_power2=-150;
         breack2=100;
        
                cmd=0;     //cmd=0;  
                 if(UlineR && UlineL)    line_set=3;
                      else if(UlineR)    line_set=2;
                                 else    line_set=1;
   } 
   
 else{      
        if(cnt<s_go_time ) {
           set_motor_go(s_go);
           if(C){
           set_motor_go(forward_fast);
           }
        }
                  else {
                   cnt=0;
                   state=1;
                   set_motor_go(stop);
                 }
           cnt++;
 }    
        break;
   case 3:
        if(cnt<100) set_motor_go(left);
                // else if(cnt<250) set_motor_go(back);
                         else if(cnt<500) {
                                          
                                           power1=-250;
                                           power2=-250;
                         }
                           else {  
                        set_motor_go(stop);
                        cmd=2;
                        cnt=0;
                        state=1;
                        first=0;
                     }
                     cnt++;               
       break;
     } 
}
