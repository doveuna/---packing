#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define M 6
#define STEPSIZE 0.005

typedef struct _circle {
	//int order;
	double x;
	double y;
	double r;
	_circle *next;
}CIRCLE;

typedef struct _ball {
	//int order;
	double x;
	double y;
	//double z;
	double r;
  //	_ball *next;
}BALL;

CIRCLE* circlesHead = new CIRCLE;
BALL* ballsHead = new BALL;

bool ifOverlap2(double x,double y,double r)
{
	//if (x + r > 1 || x - r < -1	|| y + r > 1 || y - r < -1)
	//	return false;
	double p=-0.83;
    double q=-0.83; 
    	if((x==p&&y==q)||sqrt((x-p)*(x-p)+(y-q)*(y-q))<r)
		return false;
	CIRCLE *temp = circlesHead->next;
	
	while (temp != NULL) 
	{
		if (temp->r + r > sqrt((temp->x - x)*(temp->x - x) + (temp->y - y)*(temp->y - y)))
			return false;
	
		temp = temp->next;
	}
	return true;
}

void max2d()
{
	CIRCLE *add = new CIRCLE,*temp;
	add->r = 1;
	add->x = 0;
	add->y = 0;
	add->next = NULL;
	circlesHead->next = add;

	for (int i = 1;i < M;i++)
	{
		for (double r = 0.180;r > 0;r -= STEPSIZE)
		{
			for (double x = -1.0 + r;x < 1.0 - r;x += STEPSIZE)//三四象限
				for (double y = -1.0 + r;y <(-1) * sqrt(1 - x * x);y += STEPSIZE)
				{
					if (ifOverlap2(x, y, r))
					{
						temp = new CIRCLE;
						temp->r = r;
						temp->x = x;
						temp->y = y;
						temp->next = NULL;
						add->next = temp;
						add = add->next;
						goto out;
					}
				}
			for (double x = -1.0 + r;x < 1.0 - r;x += STEPSIZE)//一二象限
				for (double y = sqrt(1 - x * x);y < 1.0 - r;y += STEPSIZE)
				{
					if (ifOverlap2(x, y, r))
					{
						temp = new CIRCLE;
						temp->r = r;
						temp->x = x;
						temp->y = y;
						temp->next = NULL;
						add->next = temp;
						add = add->next;
						goto out;
					}
				}

		}
		printf("error2\n");
		break;
	out:
		continue;
	}

}



int main()
{
	clock_t start2, end2, start3, end3;
	start2 = clock();
	max2d();
	end2 = clock();

	CIRCLE *temp1 = circlesHead->next;
	double sum1 = 0;
	int i=0;
	while (temp1 != NULL)
	{
        i++; 
		sum1 += temp1->r*temp1->r;
		printf("R%d:%lf,X:%lf,Y:%lf\n",i,temp1->r,temp1->x,temp1->y);
		temp1 = temp1->next;
	}
	printf("sum2(r^2):%lf\n", sum1);
	printf("time2:%.3f\n", (double)(end2 - start2) / CLOCKS_PER_SEC);
	system("pause");



}
