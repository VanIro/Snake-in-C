# define max 10

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>


int snake[max][max];//low level snake 
int egg[2]={30,15};
int gend=0;
int boundrx=75,bounddy=20,boundlx=4,bounduy=4; //boundaries
int data;
int hlsnak[max][2];// hl<high level> snake data(the snake is represented as a chain of vectors); [...][0](horizontal)->-1:left,1:right,0:none<cuz of up or down> ; [...][1](vertical)->-1:up,1:down,0:none<cuz of left or right>
void printsnk();//prints snk
void printhlsnk(int (*)[2]);//given hlsnk prints hlsnk's data
const int initlcn[2]={30,12};//mlsnake's (0,0) location
int crnlcn[2]={initlcn[0],initlcn[1]};//location of top left corner of bounding box of snake
int snkHeadLcn[2]={initlcn[0],initlcn[1]};
int csrlcn[2]={0,0};
int len=0;  //length of snake. only head=>0.
char player_name[100];
void xshift(int); //xmax=79=" "*79
void yshift(int,int); // ymax=24=" "*24
void add(int(*)[2],int,int);//given vecx,vecy,hlsnk adds a vector to hlsnk
int headx(int ,int (*)[2]);//returns head x cord given len,hlsnk  
int heady(int ,int (*)[2]);//returns head y cord given len,hlsnk
void drawsnk(int,int,int);//draws the snake given x,y,len
void hlml(int ,int (*)[2]);// given len,hlsnk remakes snake acrdng to hlsnk
void modsnk(int ,int (*)[2],char* );//given len, hlsnk,u or d or l or r changes hlsnk to new position
char snkmov(int);//given spd(1 or 2) moves snake along dat and returns e if boundary problem
void resetsnk(int );//given i resets snake and hlsnak if i=1, only snak if i=0
void gmend();//after gameover returns 1 to play again 0 to end

//at x/y means the cursor is at x/y after this line executes

//..................................................................
int main(){
   srand(time(0));//seed for random number generator
   setvbuf(stdout, NULL, _IONBF, 0);   //make stdout unbuffered for faster refresh rate ;NULL is ptr to custom buffer space; 
                                          //_IONBF means no buffer; 0 is for buffer size
   while(gend==0){
      system("cls");
      int spdd;
      resetsnk(1);
     // add(hlsnak,1,0);
     // add(hlsnak,1,0);
     // add(hlsnak,1,0);
      printf("Enter your name : ");
      scanf("%s",player_name);
      printf("Enter Difficulty.\n\tPress 1 for easy and press 2 for hard.");
      scanf("%d",&spdd);
      char cor=snkmov(spdd);
      if(cor=='e')   gmend();
   }
   return 7;
}
//...................................................................
#include "colors.h" 

void printBoundaryEnd(char a){
   RESET_COLOR
   printf("%c",a);
   
}
void printBoundaryBegin(char a){
   printf("%c",a);
   COLOR_FIELD_BACKG
}

void drawsnk(int x,int y,int l){


   SET_COLOR(1,31) printf("%s's Game",player_name); RESET_COLOR yshift(1,0);
   
   SET_COLOR(1,32) printf("Current Score: %d",len); RESET_COLOR yshift(1,0);


   yshift(bounduy-2,0);//at bounduy
   xshift(boundlx);
   printBoundaryBegin('#');//at boundlx+1
   for(int i=0;i<boundrx-boundlx-1;i++){
      printf("-");
   }//at boundrx
   printBoundaryEnd('#');
   yshift(1,0);//at bounduy+1
   if(egg[1]<y){
      yshift(egg[1]-bounduy-1,1);//at egg[1]
      xshift(boundlx);
      printBoundaryBegin("|");//at boundlx+1
      xshift(egg[0]-boundlx-1);//at egg[0]
      COLOR_EGG COLOR_EGG_BACKG
      printf("$");//at egg[0]+1
      printBoundaryBegin('\0');
      xshift(boundrx-egg[0]-1);//at boundrx
      printBoundaryEnd('|'); //at boundrx+1
      yshift(1,0);//at egg[1]+1
      yshift(y-egg[1]-1,1);//at y
   }
   else yshift(y-bounduy-1,1);//at y
   //yshift(1,0);
   // xshift(x);
   int eggx=-1,eggy=-1;
   if(egg[1]>=y && egg[1]<=y+l){
      eggy = egg[1]-y;
      eggx = egg[0];
   }
   for(int i=0;i<=l;i++){
      xshift(boundlx);//at boundlx
      printBoundaryBegin('|');//at boundlx+1
      if(i==eggy && eggx<x){
         xshift(eggx-boundlx-1);//at eggx
         COLOR_EGG COLOR_EGG_BACKG
         printf("$");//at egg[0]+1
         printBoundaryBegin('\0'); 
         xshift(x-eggx-1);//at x
      }
      else      xshift(x-boundlx-1);//at x
      int j=0;
      for(j=0;(j<=l)&&(x+j<boundrx);j++){
         if(snake[i][j]==1) {
            COLOR_SNAKE_BODY COLOR_SNAKE_BODY_BACKG 
            printf("0");
            printBoundaryBegin('\0');
         }
         else if(snake[i][j]==2){ //print head
            COLOR_SNAKE_HEAD COLOR_SNAKE_HEAD_BACKG
            if(hlsnak[0][0]==-1) printf("%c",16); //right arrow
            else if(hlsnak[0][0]==1) printf("%c",17); //left arrow
            else if(hlsnak[0][1]==-1) printf("%c",31); //down arrow
            else if(hlsnak[0][1]==1) printf("%c",30); //up arrow
            else printf("%c",'X');
            printBoundaryBegin('\0');
         } 
         else if(i==eggy && j == eggx-x){ 
            COLOR_EGG COLOR_EGG_BACKG
            printf("$");//at egg[0]+1
            printBoundaryBegin('\0');
         }
         else {
            COLOR_FIELD_BACKG
            printf(" ");
         }
         printBoundaryBegin('\0');
      }//at min(x+l+1,boundrx)
      if(i==eggy && eggx>x+l){
         xshift(eggx-x-l-1);//at eggx
         COLOR_EGG COLOR_EGG_BACKG
         printf("$");//at egg[0]+1
         printBoundaryBegin('\0');
         xshift(boundrx-eggx-1);//at boundrx
      }
      else      xshift(boundrx-x-l-1);//at boundrx
      printBoundaryEnd('|');
      yshift(1,0);
   }//at y+l+1
   if(egg[1]>y+l){
      yshift(egg[1]-y-l-1,1);//at egg[1]
      xshift(boundlx);
      printBoundaryBegin('|');//at boundlx+1
      xshift(egg[0]-boundlx-1);//at egg[0]
      COLOR_EGG COLOR_EGG_BACKG
      printf("$");//at egg[0]+1
      printBoundaryBegin('\0');
      xshift(boundrx-egg[0]-1);//at boundrx
      printBoundaryEnd('|');
      yshift(1,0);//at egg[1]+1
      yshift(bounddy-egg[1]-1,1);//at bounddy
   }
   else   yshift(bounddy-y-l-1,1);//at bounddy
   xshift(boundlx);
   printBoundaryBegin('#');//at boundlx+1
   for(int i=0;i<boundrx-boundlx-1;i++){
      printf("-");
   }   //at boundrx
   printBoundaryEnd('#');
   yshift(1,0);//at bounddy+1

}
//.....................................................................
void add(int(*hlsnk)[2],int x,int y){
   //printf("added");
   static int i=0;
   int head_x0 = headx(len,hlsnk);
   int head_y0 = heady(len,hlsnk);
   hlsnk[i][0]=x;
   hlsnk[i][1]=y;
   len++;
   int head_x1 = headx(len,hlsnk);
   int head_y1 = heady(len,hlsnk);
   if(head_x1>head_x0) crnlcn[0]--;
   if(head_y1>head_y0) crnlcn[1]--;
   hlml(len,hlsnk);
   i++;
   //printsnk();
}
//....................................................................
void xshift(int x){
   for(int i=0;i<x;i++){
      printf(" ");
   }
   csrlcn[0]+=x;
}
//.....................................................................
void yshift(int y,int draw_bound){
   for(int j=0;j<y;j++){
      if(draw_bound){
         xshift(boundlx);
         printBoundaryBegin('|');
         xshift(boundrx-boundlx-1);
         printBoundaryEnd('|');
      }
      printf("\n");
      csrlcn[1]+=1;
      csrlcn[0]=0;
   }
}
//......................................................................
int headx(int l,int (*hlsnk)[2]){
   int temp1=0,temp2=0;
   if (l==0) return 0;
   for(int i=0;i<l;i++){
      temp1+=hlsnk[i][0];
      if (temp1<temp2)  temp2=temp1;
   }
   return (-temp2);
}
//......................................................................
int heady(int l,int (*hlsnk)[2]){
   int temp1=0,temp2=0;
   if(l==0) return 0;
   for(int i=0;i<l;i++){
      temp1+=hlsnk[i][1];
      if (temp1<temp2)  temp2=temp1;
   }
   return (-temp2);
}
//......................................................................
void modsnk(int l,int (*hlsnk)[2],char* wh){
   int head_x0 = headx(l,hlsnk);
   int head_y0 = heady(l,hlsnk);
   if(l>1){//for body
      //shift body forward
      for(int i=l-1;i>0;i--){
         hlsnk[i][0]=hlsnk[i-1][0];
         hlsnk[i][1]=hlsnk[i-1][1];
      }
   }
   //for head
   char temp=wh[0];
   int delHead[2] = {0,0};
   if(temp=='u'){
      if (head_y0==0) crnlcn[1]-=1;
      delHead[1] = -1;
      hlsnk[0][0]=0;
      hlsnk[0][1]=1;

   }
   else if(temp=='d'){
      delHead[1] = 1;
      hlsnk[0][0]=0;
      hlsnk[0][1]=-1;
   }
   else if(temp=='r'){
      delHead[0] = 1;
      hlsnk[0][0]=-1;
      hlsnk[0][1]=0;
   }
   else if(temp=='l'){
      if (head_x0==0){ crnlcn[0]-=1; printf("%d",l);} 
      delHead[0] = -1;
      hlsnk[0][0]=1;
      hlsnk[0][1]=0;
   }

   snkHeadLcn[0] += delHead[0];
   snkHeadLcn[1] += delHead[1];

   int head_x1 = headx(l,hlsnk);
   int head_y1 = heady(l,hlsnk);

   if( head_x1-delHead[0] -head_x0 < 0 ) {
      crnlcn[0]++;
   }
   if( head_y1-delHead[1] -head_y0 < 0 ){
      crnlcn[1]++;
   } 
   hlml(len,hlsnk);
}
//......................................................................
void resetsnk(int hl){
   int temp=len;
   for(int i=0;i<=len;i++){
      if(hl==1){
	 hlsnak[i][0]=7;
	 hlsnak[i][1]=7;
	 len=0;
	 crnlcn[0]=initlcn[0];
	 crnlcn[1]=initlcn[1];
    snkHeadLcn[0]=initlcn[0];
	 snkHeadLcn[1]=initlcn[1];
      }
      for(int j=0;j<=temp;j++){
	 snake[i][j]=0;
      }
   }
   csrlcn[0]=0;
   csrlcn[1]=0;
}
//......................................................................
void hlml(int l,int (*hlsnk)[2]){
   int x=headx(l,hlsnk);
   int y=heady(l,hlsnk);
   resetsnk(0);
   snake[y][x]=2;
   if (l>0){
      for (int k=0;k<l;k++){
         x+=hlsnk[k][0];
         y+=hlsnk[k][1];
         snake[y][x]=1;
      }
   }
}
//.....................................................................
char translate_inp(char c){
   if(c==0){
      c=_getch();
   }
   switch(c){
               case 'A':
               case 'a':
               case 'K'://Larrow
            return 'l';
            break;
               case 's':
               case 'S':
               case 'P'://Darrow
            return 'd';
            break;
               case 'd':
               case 'D':
               case 'M'://Rarrow
            return 'r';
            break;
               case 'w':
               case 'W':
               case 'H'://Uarrow
            return 'u';
            break;
   };
   return 'Z';//do nothing
}
char snkmov(int spd){
      while(0==0){
         if(!((snkHeadLcn[0]<boundrx)&&(snkHeadLcn[0]>boundlx))) return'e';
         if(!((snkHeadLcn[1]<bounddy)&&(snkHeadLcn[1]>bounduy))) return 'e';
         if(snkHeadLcn[0]==egg[0]&&snkHeadLcn[1]==egg[1]){
            if(len==0)   add(hlsnak,1,0);
            else add(hlsnak,hlsnak[len-1][0],hlsnak[len-1][1]);

            int egg_next[2] = {rand(),rand()};
            egg[0] = egg_next[0]%(boundrx-boundlx-1) + boundlx+1;
            egg[1] = egg_next[1]%(bounddy-bounduy-1) + bounduy+1;
         }
         system("cls");
         char cr[1]={data};
         modsnk(len,hlsnak,cr);
         drawsnk(crnlcn[0],crnlcn[1],len);
         printf("egg :\t\t %d,%d\nsnake :\t\t %d,%d\n",egg[0],egg[1],crnlcn[0],crnlcn[1]);
         printf("snake head :\t %d,%d\n",snkHeadLcn[0],snkHeadLcn[1]);
         //printsnk();
         //printhlsnk(hlsnak);

         //data = translate_inp(getch()); //for debug purpose
         Sleep(10/spd);
         if(_kbhit()) {
            data = translate_inp(_getch());
         }
         int i=0;
         //while(_kbhit()||i++<32000){_getch();} //kharaab
      }
}
//.......................................................................
void gmend(){
   char inp;
   printf("\n\tGame Over. Press enter.");
   getch();
   printf("\n\tPress p to play agin, any other key to end.");
   inp=getch();
   if(inp=='p'||inp=='P') gend=0;
   else gend=1;
}
//.......................................................................
void printsnk(){
   for(int j=0;j<=len;j++){
      for(int k=0;k<=len;k++){
	      printf("<%d> ",snake[j][k]);
      }
     printf("\n");
   }
}
void printhlsnk(int (*hlsnk)[2]){
   for(int i=0;i<len;i++){
      printf("x%d y%d\n",hlsnk[i][0],hlsnk[i][1]);
   }
}