int PBL=111,PBR=112,PBU=113,PBD=114, latest=0,k=0,g=0,i,g1=0,prev=0,n=0,a=2,b=1;
int Row[8], Column[8],r=0,c=0,Size=1;
int C=Size,R=0,z=0;
int RP=7, CP=7,nn=0,xx,yy, rate;


byte long left_right[8][8]={0x7F80,0xBF80,0xDF80,0xEF80,0xF780,0xFB80,0xFD80,0xFE80,0x7F40,0xBF40,0xDF40,0xEF40,0xF740,0xFB40,0xFD40,0xFE40,0x7F20,0xBF20,0xDF20,0xEF20,0xF720,0xFB20,0xFD20,0xFE20,0x7F10,0xBF10,0xDF10,0xEF10,0xF710,0xFB10,0xFD10,0xFE10,0x7F08,0xBF08,0xDF08,0xEF08,0xF708,0xFB08,0xFD08,0xFE08,0x7F04,0xBF04,0xDF04,0xEF04,0xF704,0xFB04,0xFD04,0xFE04,0x7F02,0xBF02,0xDF02,0xEF02,0xF702,0xFB02,0xFD02,0xFE02,0x7F01,0xBF01,0xDF01,0xEF01,0xF701,0xFB01,0xFD01,0xFE01}; 
void button();// to read the joystick inputs
void Position();// to calculate position of the pixels of the snake
void sizee();// to change the refresh rate of the matrix as the size of the snake changes 
void win();// shows some led pattern when the player wins
void Display_1();// tp display position of the food for the snake
void Display(int rr,int cc);// to display position of the snake
void point();// calculates next position of the food of the snake using random()
void over();// calculates when the snake eats itself
void setup()
{Serial.begin(9600);
 pinMode(2,OUTPUT);
 pinMode(3,OUTPUT);
 pinMode(4,OUTPUT);
 pinMode(5,OUTPUT);
 pinMode(13,OUTPUT);
 pinMode(6,OUTPUT);
 pinMode(7,OUTPUT);
 pinMode(8,OUTPUT);
 pinMode(A0,INPUT);
 pinMode(A1,INPUT);
 digitalWrite(2,HIGH);
 digitalWrite(3,HIGH);
 digitalWrite(4,HIGH);
 digitalWrite(5,HIGH); 
 digitalWrite(13,HIGH);
}

void loop() 
{int n=0;
  button();
  Position();
  if((Row[Size-1]==RP && Column[Size-1]==CP) || nn==0)
  {point();
   sizee();
   nn=1;
  }
  
  while(n<rate)
      {for(i=0;i<Size;i++)
          {r=i;
           c=i;
           Display(r,c); 
           if(i==Size-1)
              {
                 xx = Row[r];
                 yy = Column[c];
              }
          }
       Display_1();
       n++; 
      } 
     
      if((xx==RP) && (yy==CP))
         {point();
         }
              
    
}
void Display(int rr,int cc)
{   digitalWrite(8,LOW); 
    shiftOut(6,7,LSBFIRST,left_right[Row[rr]][Column[cc]]);
    shiftOut(6,7,LSBFIRST,left_right[Row[rr]][Column[cc]]>>8);
    digitalWrite(8,HIGH); 
  
}
void Display_1()
{   digitalWrite(8,LOW); 
    shiftOut(6,7,LSBFIRST,left_right[RP][CP]);
    shiftOut(6,7,LSBFIRST,left_right[RP][CP]>>8);
    digitalWrite(8,HIGH); 
  
}

void button()
{ 
  if(analogRead(A1)>535)
     latest=PBU;
  if(analogRead(A1)<=510)
     latest=PBD;
  if(analogRead(A0)>520)
     latest=PBR;
  if(analogRead(A0)<=500)
     latest=PBL;
    
}

void Position()
{
  if(latest==0)
     {for(int i=0;i<Size;i++)
          { Row[i]=i;
            Column[i]=0;
          }
     }
  if((latest==PBD && prev!=PBU) || (latest==PBU && prev==PBD))
     {for(int i=0;i<Size-1;i++)
         {Row[i]=Row[i+1];
          Column[i]=Column[i+1]; 
         }
      Row[Size-1]++;
      if(Row[Size-1]>7)
         Row[Size-1]=0;
   
         prev=PBD;
        
     }
  if((latest==PBU && prev!=PBD) || (latest==PBD && prev==PBU))
     {for(int i=0;i<Size-1;i++)
         {Row[i]=Row[i+1];
          Column[i]=Column[i+1]; 
         }
      Row[Size-1]--;
      if(Row[Size-1]<0)
         Row[Size-1]=7;
   
         prev=PBU;
        
     }
  if((latest==PBR && prev!=PBL) || (latest==PBL && prev==PBR))
     {for(int i=0;i<Size-1;i++)
         {Row[i]=Row[i+1];
          Column[i]=Column[i+1]; 
         }
      Column[Size-1]++;
      if(Column[Size-1]>7)
         Column[Size-1]=0;
     
         prev=PBR;
          
     }
  if((latest==PBL && prev!=PBR) || (latest==PBR && prev==PBL))
    {for(int i=0;i<Size-1;i++)
         {Row[i]=Row[i+1];
          Column[i]=Column[i+1]; 
         }
      Column[Size-1]--;
      if(Column[Size-1]<0)
         Column[Size-1]=7;
  
         prev=PBL;
        
     }
     
}
void sizee()
{
  Size++;
  if(Size==4||Size==5)
     rate=120;
  if(Size==6||Size==7)
     rate=100;
  if(Size==7)
    {Size=1;}
}
void point()
{ int j;
  do{ 
     j=0;
     CP= random(0,8);
     RP= random(0,8);
     for(int i=0;i<Size-1;i++)
        {
         if(RP==Row[i] && CP==Column[i])
         j++;
        }

    }while(j!=0);
}

void win()
{
  for(int o=0;o<5;o++)
  {digitalWrite(8,LOW); 
  shiftOut(6,7,LSBFIRST,0x0011);
  shiftOut(6,7,LSBFIRST,0x0011>>8);
  digitalWrite(8,HIGH); 
  delay(200);
  digitalWrite(8,LOW); 
  shiftOut(6,7,LSBFIRST,0x0000);
  shiftOut(6,7,LSBFIRST,0x0000>>8);
  digitalWrite(8,HIGH); 
  }
}
void over()
{
 for(int i=0;i<Size-1;i++)
  {
     if(Row[Size-1]==Row[i] && Column[Size-1]==Column[i])
       {win();
        Size=1;
       }
  }
}
