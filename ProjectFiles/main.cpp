#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <graphics.h>
#include <conio.h>
#include<time.h>
#define MAXX 640
#define MAXY 480
#define maxR 10
struct nokta
{
    int x,y;
} nokta[10];

//FONKSIYONLAR

//Ust Faktoryel
int upperFactorial(int num, int n){
    int result = 1;
    for(int i = num ; i > num-n ; i--){
        result *=i;
    }
    return result;

}
//Faktoryel
int factorial(int a){
    if(a == 0){
        return 1 ;
    }
    int result = 1;
    for(int i = a; i >0 ; i--){
        result *= i ;
    }
    return result;
}
//Bezier Curve X'e gore
float bezier_x(int index, struct nokta P[], float t){

 int n = index - 1;
 float b  = 0;
 for(int i = 0 ; i < n+1 ; i++){
    b += ((upperFactorial(n,i)/factorial(i)) * pow(t, i) * (pow((1-t),(n-i))) * P[i].x);//(1-u)^(n-i)*u^i

 }
 return b ;

}

//Bezier Curve Y'ye gore
float bezier_y(int index, struct nokta P[], float t){

 int n = index - 1;
 float b  = 0;
 for(int i = 0 ; i < n+1 ; i++){
    b += (upperFactorial(n,i)/factorial(i)) * pow(t, i) * pow((1-t),(n-i)) * P[i].y;

 }
 return b ;

}
//Merkez Koordinatinin hesabi icin gerekli determinant alma
int detA(struct nokta a,struct nokta j,struct nokta k)
{
        int c= a.x*j.y+a.y*k.x+j.x*k.y-k.x*j.y-k.y*a.x-j.x*a.y;
        return c;
}
int detD(struct nokta a,struct nokta j,struct nokta k)
{
     int c=(a.x*a.x+a.y*a.y)*j.y+a.y*(k.x*k.x+k.y*k.y)+k.y*(j.x*j.x+j.y*j.y)-(k.x*k.x+k.y*k.y)*j.y-k.y*(a.x*a.x+a.y*a.y)-(j.x*j.x+j.y*j.y)*a.y;
    return c;
}
int detE(struct nokta a,struct nokta j,struct nokta k)
{
    int c=(a.x*a.x+a.y*a.y)*j.x+a.x*(k.x*k.x+k.y*k.y)+k.x*(j.x*j.x+j.y*j.y)-(k.x*k.x+k.y*k.y)*j.x-k.x*(a.x*a.x+a.y*a.y)-(j.x*j.x+j.y*j.y)*a.x;
    return c;
}
int detF(struct nokta a,struct nokta j,struct nokta k)
{
    int c=(a.x*a.x+a.y*a.y)*j.x*k.y+a.x*j.y*(k.x*k.x+k.y*k.y)+a.y*k.x*(j.x*j.x+j.y*j.y)-(k.x*k.x+k.y*k.y)*j.x*a.y-k.x*j.y*(a.x*a.x+a.y*a.y)-k.y*(j.x*j.x+j.y*j.y)*a.x;
    return c;
}
//Koordinat sisteminde ki cizgilerin cizimi
void CreateGraph(int width,int height)
{
    line(width/2,0,width/2,height);
    line(0,height/2,width,height/2);
}



int main()
{
    FILE *noktalar;
    noktalar=fopen("noktalar.txt","r");
    int N;
    printf("Kac tane nokta olucak:\n");
    scanf("%d",&N);
    char satir[N];
    int x[N],y[N];
    srand(time(0));
    int gd = DETECT, gm,colors;
    //file check
    if(noktalar==NULL)
    {
        printf("error openning file");
        exit(1);
    }
        printf("\n");
    /* for(int i=0;i<4;i++) //yeninoktaolusturma fopeni W yap
          {
              int x=rand()%(400-300+1)+300;
              int y=rand()%(300-200+1)+200;
              fprintf(noktalar,"%d %d\n",x,y);

          }*/


    int index=0;
    //noktalarin dosyadan okunmasi ve yazilmasi
    printf("Noktalar:\n");
    while (fgets(satir,sizeof(satir),noktalar))
    {

        fscanf(noktalar,"%d %d",&nokta[index].x,&nokta[index].y);
        printf("X:%d Y:%d\n",nokta[index].x,nokta[index].y);
        index++;

    }

    printf("\nKac nokta var:%d\n",index);
    for(int i=0;i<index;i++)
    {
        x[i]=nokta[i].x;
        y[i]=nokta[i].y;
    }



    initgraph(&gd, &gm, "");
    CreateGraph(640,480);


    //noktalarin cizilmesi
    for(int i=0; i<index; i++)
    {
        //rectangle(nokta[i].x,nokta[i].y,nokta[i].x+2,nokta[i].y+2);//kutu
        circle(nokta[i].x,nokta[i].y,2);//cember
        //putpixel(nokta[i].x,nokta[i].y,RED);//pixel
    }


    // En buyuk ve en kucuk X ve Y noktalarinin bulunmasi
    int largeXY,smallXY;
    int largeYX,smallYX;
    int largeX,smallX,largeY,smallY;
    largeX=smallX=largeYX=smallYX=x[0];
    largeY=smallY=largeXY=smallXY=y[0];
    int flag1=0,flag2=0,flagy1=0,flagy2=0;
    for(int i=0; i<index; i++)
    {
        if(x[i]>largeX)
        {
            largeX=x[i];
            largeXY=y[i];
            flag1=i;
        }
        if(x[i]<smallX)
        {
            smallX=x[i];
            smallXY=y[i];
            flag2=i;
        }
        if(y[i]>largeY)
        {
            largeY=y[i];
            largeYX=x[i];
            flagy1=i;
        }
        if(y[i]<smallY)
        {
            smallY=y[i];
            smallYX=x[i];
            flagy2=i;
        }
    }
    printf("Large X:%d,%d",largeX,largeXY);
    printf("\nSmall X:%d,%d",smallX,smallXY);
    printf("\nLarge Y:%d,%d",largeYX,largeY);
    printf("\nSmall Y:%d,%d",smallYX,smallY);


    // Cizilecek cemberin merkezinin koordinat hesabi
        int tamA,tamB;
    float tamYaricap;
    int a=detA(nokta[flag1],nokta[flag2],nokta[flagy1]);
    int d=detD(nokta[flag1],nokta[flag2],nokta[flagy1]);
    int e=detE(nokta[flag1],nokta[flag2],nokta[flagy1]);
    int f=detF(nokta[flag1],nokta[flag2],nokta[flagy1]);
    //formuller princeton.edu den alindi
    //3 noktayla kesisen bir cemberin merkezini ve yaricapini bulmak
    int p=(a*a)*4;
    float o=f/a;
    tamA=d/(2*a);
    tamB=-e/(2*a);
    tamYaricap=sqrt((pow(d,2)+pow(e,2))/p+o);

    printf("\na:%d\n",a);
    printf("\nd:%d\n",d);
    printf("\ne:%d\n",e);
    printf("\nf:%d\n",f);

    // Cizilecek Cember Koordinatlari
    printf("\nCember Merkezi X:%d\n",tamA);
    printf("\nCember Merkezi Y:%d\n",tamB);
    printf("\nCember Yaricapi:%.2f\n",tamYaricap);

    //Cemberin Cizilmesi
    circle(tamA,tamB,tamYaricap);


   //                BEZIER CURVE CIZIMI


    double xu = 0.0 , yu = 0.0 , u = 0.0 ;

    for(u = 0.0 ; u <= 1.0 ; u += 0.0001)
    {
        putpixel(bezier_x(index,nokta,u),bezier_y(index,nokta,u),BLUE);

    }

    getch();

    fclose(noktalar);

}
