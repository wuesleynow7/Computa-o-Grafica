#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void cls(){
  printf("\x1b[H");
}
int sgn(int x){
	if (x<0)return -1;else return 1;
}

void locate(int x, int y){
	
    printf("\x1b[%i;%iH",y,x);
		
}
void fgrgb(int r, int g, int b){
	
	 printf("\033[38;2;%i;%i;%im",r,g,b);
}

void fg(int n){
	
	 printf("\033[38;5;%im",n);
}

void bgrgb(int r, int g, int b){
	
	 printf("\033[48;2;%i;%i;%im",r,g,b);
}
void bg(int n){
	
	 printf("\033[48;5;%im",n);
}

void drawline(int x1, int y1, int x2, int y2, int fore, int back, int c)
{
    int i,dx,dy,sdx,sdy,dxabs,dyabs,x,y,px,py;
     char chars[4]={176,177,178,219};
    dx=x2-x1;      /* the horizontal distance of the line */
    dy=y2-y1;      /* the vertical distance of the line */
    dxabs=abs(dx);
    dyabs=abs(dy);
    sdx=sgn(dx);
    sdy=sgn(dy);
    x=dyabs>>1;
    y=dxabs>>1;
    px=x1;
    py=y1;

    if (dxabs>=dyabs) /* the line is more horizontal than vertical */
    {
        for(i=0; i<dxabs; i++)
        {
            y+=dyabs;
            if (y>=dxabs)
            {
                y-=dxabs;
                py+=sdy;
            }
            px+=sdx;
            locate(px,py);
			fg(fore);
			bg(back);
			printf("%c",chars[c]);
        }
    }
    else /* the line is more vertical than horizontal */
    {
        for(i=0; i<dyabs; i++)
        {
            x+=dxabs;
            if (x>=dyabs)
            {
                x-=dyabs;
                px+=sdx;
            }
            py+=sdy;
            locate(px,py);
			fg(fore);
			bg(back);
			printf("%c",chars[c]);
        }
    }
}



int main(){

    int i;
	char chars[4]={176,177,178,219};

	cls();
    
	for (i=0;i<9;i++){fg(i);printf("%c",chars[3]); }
	for (i=0;i<40;i++){
		drawline(0,i,150,i,4,4,3);
				}
	for (i=40;i<50;i++){
		drawline(0,i,150,i,2,2,3);

		}
		
	for (i=10;i<25;i++){
		drawline(50.0-30.0*sin(((double)i-10)/15.0*3.1415),i-9,50.0+20.0*sin(((double)i-10)/15.0*3.1415),i-9,7,7,3
		);

	}	
		
	for (i=10;i<25;i++){
		drawline(30.0-20.0*sin(((double)i-10)/15.0*3.1415),i,30.0+20.0*sin(((double)i-10)/15.0*3.1415),i,2,2,3);

	}
	drawline(28,20,28,42,1,0,1);
	drawline(29,20,29,42,1,0,1);
	drawline(30,20,30,42,1,1,3);
	drawline(31,20,31,42,1,1,3);
	drawline(32,20,32,42,7,1,1);
	drawline(33,20,33,42,7,1,1);

	for (i=10;i<25;i++){
		drawline(90.0-10.0*sin(((double)i-10)/15.0*3.1415),i-5,90.0+10.0*sin(((double)i-10)/15.0*3.1415),i-5,3,3,3);
	}

}