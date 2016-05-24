#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define M 20
#define Q 999
#define true 1
#define false 0
#define square(x)  ((x)*(x))
#define degree 0.000001
#define minh 0.0001


static double d[M][M+5];//��¼����


 struct _direct{
    double x;
    double y;
};

struct _pattern{

    double h;//�ƶ��ٶ�
    double t;//�ݶ�
    double flag;//��־���ܱ仯
    double energy;
}Pattern={0.2,1,0,100};


struct _circle{

   double x;
   double y;
   double r;
   struct _direct direct;
   double e;
}CIRCLE[M];

struct _ball{

   double x;
   double y;
   double L;
   double W;
}BALL={0,0,1,1};





double *seat=(double *)malloc(sizeof(double)*2*M);
double *radius=(double*)malloc(M*sizeof(double));

/*****�����������******/
double play()
{
    srand(time(NULL));
    for(int i=0;i<2*M;i++)
    {
        seat[i]=rand()%(Q+1)/(float)(Q+1);
    }
}
/**����Բ������**/
double circleRadius()
{
    for(int i=0;i<M;i++)
    {
        scanf("%f",radius[i]);
    }
}
/**�����긳��Բ��ʼ��**/
double initCircle()
{
    play();
    for(int i=0;i++;i<M)
      {
          CIRCLE[i].x=seat[i];
          CIRCLE[i].y=seat[i+1];
          CIRCLE[i].r=radius[i];
      }
}


//CIRCLE* circlesHead=new  CIRCLE;
//BALL* ballsHead=new BALL;
/********�����ͻ*********/
int constrait(int i,int j)
{
    if ((CIRCLE[i].x>=CIRCLE[i].r)&&(CIRCLE[i].x<=(BALL.L-CIRCLE[i].r))&&
        (CIRCLE[i].y>=CIRCLE[i].r)&&(CIRCLE[i].y<=(BALL.W-CIRCLE[i].r))&&
        sqrt(pow(CIRCLE[i].x-CIRCLE[j].x,2)+pow(CIRCLE[i].y-CIRCLE[j].y,2))>=CIRCLE[i].r+CIRCLE[j].r)
        {return true;}
    else
    {
        return false;
    }
}

/*******��������********/
double calDepth1(int i,int j)
{
   //��¼����Բ���������
    if(sqrt(pow(CIRCLE[i].x-CIRCLE[j].x,2)+pow(CIRCLE[i].y-CIRCLE[j].y,2))<CIRCLE[i].r+CIRCLE[j].r)
    {
        d[i][j]=CIRCLE[i].r+CIRCLE[j].r-sqrt(pow(CIRCLE[i].x-CIRCLE[j].x,2)+pow(CIRCLE[i].y-CIRCLE[j].y,2));
    }
    else
    {
        d[i][j]=0;
    }
    return square(d[i][j]);
}
double calDepth2(int i)
{
    //��¼Բ������ĸ��ߵ��ཻ��ȣ�

     if(CIRCLE[i].y<CIRCLE[i].r)
    {
        d[i][M]=CIRCLE[i].r-CIRCLE[i].y;
    }
    else
    {
        d[i][M]=0;
    }
     if(CIRCLE[i].x<CIRCLE[i].r)
    {
        d[i][M+1]=CIRCLE[i].r-CIRCLE[i].x;
    }
    else
    {
        d[i][M+1]=0;
    }
    if(CIRCLE[i].y+CIRCLE[i].r>BALL.W)
    {
        d[i][M+2]=CIRCLE[i].y+CIRCLE[i].r-BALL.W;
    }
    else
    {
        d[i][M+2]=0;
    }
    if(CIRCLE[i].x+CIRCLE[i].r>BALL.L)
    {
        d[i][M+3]=CIRCLE[i].x+CIRCLE[i].r-BALL.L;
    }
    else
    {
        d[i][M+3]=0;
    }
    double EX=square(d[i][M])+square(d[i][M+1])+square(d[i][M+2])+square(d[i][M+3]);
    return EX;
}
/**�ͷ�radius��seat**/
double FreeRS()
{
    free(radius);
    free(seat);
    radius=0;
    seat=0;
}

/**��������������**/
int sumEnergy()
{
    int i,j;
    double U=0.0;
    for(i=0;i<M;i++)
        for(j=i+1;j<M;j++)
    {
        U=U+square(d[i][j]);
    }
    return U;
}

/**����������㵱ǰԲ�����ܺ��˶�����**/
double update(struct _pattern Pattern)
{
    double Uold=Pattern.energy;
    Pattern.energy=0;
    for(int i=0;i<M;i++)
    {
        struct _circle c1=CIRCLE[i];
        c1.direct.x=0;
        c1.direct.y=0;
    }
    for(int i=0;i<M;i++)
    {
        double m0,m1,z0,z1;
        double sum=d[i][M]+d[i][M+1]+d[i][M+2]+d[i][M+3];
        struct _circle c1=CIRCLE[i];
        /**��i������������ѹ�ĵ�������**/
        double E0=calDepth2(i);
        c1.direct.x+=(d[i][M+1]+d[i][M+3])/sum*E0;//x�᷽�������
        c1.direct.y+=(d[i][M]+d[i][M+2])/sum*E0;//y�᷽�������
        c1.e+=E0;
        Pattern.energy+=E0;//������
        /**��i������������ĵ�������**/
        for(int j=i+1;j<M;j++)
        {
            struct _circle c2=CIRCLE[j];
            if(c1.x>c2.x){m0=c1.x-c2.x;}
            else {m0=c2.x-c1.x;}
            if(c1.y>c2.y) {m1=c1.y-c2.y;}
            else {m1=c2.y-c1.y;}
            z0=m0/sqrt(square((m0+m1)));//���ң�
            z1=m1/sqrt(square((m0+m1)));//���ң�
            double E1=calDepth1(i,j);
            c1.direct.x+=z0*E1;
            c1.direct.y+=z1*E1;
            c2.direct.x+=z0*E1;
            c2.direct.y+=z1*E1;
            c1.e+=E1;
            c2.e+=E1;
            Pattern.energy+=E1;
        }
        CIRCLE[i].e=c1.e;
    }
     Pattern.flag=Uold-Pattern.energy;  //flag����0����������С

}
/***IPQ�㷨��ʵ��**/
double IPQ()
{
    circleRadius();//��ȡԲ�İ뾶
    play();//�����������
    initCircle();//�������Բ�Ľṹ��
    FreeRS();

    int count=1;
    struct _circle pity;
    struct _circle oldpity;
    while(Pattern.energy>degree)
    {
          update(Pattern);
          //���ܲ�Ϊ0�������ƶ�Ϊ0
          if(Pattern.h<minh)
          {
              pity=CIRCLE[0];
              //�ҵ������ܶ����ĵ�����
              for(int i=1;i<M;i++)
              {
                  pity=pity.e/square(pity.r)>CIRCLE[i].e/square(CIRCLE[i].r) ? pity:CIRCLE[i];

              }
               if(pity==oldpity)
               {
                   pity=CIRCLE[0];
                   //�ҵ�������С�ĵ�
                   for(int i=1;i<M;i++)
                    pity=pity.e<CIRCLE[i].e ? pity:CIRCLE[i];
               }
               oldpity=pity;
               //
               srand(time(NULL));
               int i=rand()%5;
                    switch(i){
                    case 0:
                        pity.x=0.4;
                        pity.y=0.6;
                        break;
                    case 1:
                        pity.x=0.5;
                        pity.y=0.5;
                        break;
                    case 2:
                        pity.x=0.6;
                        pity.y=0.4;
                        break;
                    case 3:
                        pity.x=0.2;
                        pity.y=0.2;
                        break;
                    case 4:
                        pity.x=0.8;
                        pity.y=0.8;
                        break;
                     }
                     update(Pattern);
                     Pattern.flag=0;
                     Pattern.h=0.2;
          }
          else if(Pattern.flag<0)//��������
           Pattern.h=Pattern.t*Pattern.h;

    }
}





int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
