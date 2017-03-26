#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deque.h"
#include <math.h>

#define r 10

int main(void)
{

	int i,x,loop, index, max,lvl;
	DEQUE *a, *dp[r];

	max=0;
	a= createDeque();

	for(i=0;i<r;i++)
	{
		dp[i]=createDeque();
	}
    /* create deque */

	while(scanf("%d",&x)==1) /* read the numbers and record the max value */
	{
		if(x>=0)
		{
			addLast(a,x);

			if(x>max)
			max=x;
		}
		else
		{
			printf("no negative numbers" );
			return -1;
		}
	}
	loop=ceil(log(max+1)/log(r));/* the times of iterations */
	lvl=1;
	while(loop--)
	{
		while(numItems(a)>0)/* move the numbers to the deque */
		{
			x=removeFirst(a);
			addLast(dp[x/lvl % r],x);
		}
		for(i=0;i<r;i++) /* move the numbers from the deque back to the list */
		{
			while(numItems(dp[i])>0)
			{
				addLast(a,removeFirst(dp[i]));
			}
			
		}
		lvl=lvl * r;
	}
	while(numItems(a)>0)
	{
		printf("%d\n",removeFirst(a));
	}
	return 0;
}
