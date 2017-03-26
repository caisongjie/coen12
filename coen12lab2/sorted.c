
#include "set.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
struct set
{
	int count;
	int length;
	char **data;
};

SET *createSet(int maxElts)
{
  
	SET *sp;
	sp=malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count=0;
	sp->length=maxElts;
	sp->data=malloc(maxElts*sizeof(char *));
	assert(sp->data!=NULL);
	return sp;
  
}

void destroySet(SET *sp)
{
    
    int i;
    assert(sp!=NULL);
    for(i=0;i<sp->count;i++)
    {
        free (sp->data[i]);
    }
    free(sp->data);
    free(sp);
    
}


static int findElement(SET *sp,char *elements, bool *found)
{

    assert(sp!=NULL && elements !=NULL);
    int lo,hi,mid;
    lo=0;
    hi=sp->count-1;
    while(lo<=hi)
    {
        mid=(lo+hi)/2;
        if(strcmp(sp->data[mid],elements)==0)
        {
            *found=true;	
            return mid;
            
        }
        if(strcmp(sp->data[mid],elements)>0)
        {
            hi=mid-1;
        }
        else
        {
            lo=mid+1;
        }
    }
    *found=false;

    return lo;
    /*
     use binary search
     if it is not found, return lo, which is the location for this element in the sorted array
     */
}

int numElements(SET *sp)
{
    
    assert(sp!=NULL);
    return sp->count;
    
}

bool hasElement(SET *sp,char *elt)
{
    bool found;

    assert(sp!=NULL && elt !=NULL);
    int i=findElement(sp,elt,&found);
    return found;

}

bool removeElement(SET *sp, char *elt)
{
    bool found;

    assert(sp!=NULL && elt !=NULL);
    int location=findElement(sp,elt,&found);
    if(found==true)
    {
        free(sp->data[location]);
        int i;
        for(i=location;i<sp->count-1;i++)
        {
            sp->data[i]=sp->data[i+1];
        }
        sp->count--;
        return true;
    }
    else
        return false;
    
    /*
     free this elt. then moves the rest of the set one step forward
     */

}

bool addElement(SET *sp,char *elt)
{
    bool found;
    assert(sp!=NULL && elt!=NULL);

    int loc;
    int i;

    loc=findElement(sp,elt,&found);

    if (found== true || sp->count==sp->length)
	{
	return false;
	}
    for (i=sp->count;i>loc;i--)
    {
       
        sp->data[i] = sp->data[i-1];

    }
    
    sp->data[loc]=strdup(elt);
    sp->count++;
    return true;
    /*
     move the elements after location backward, then add the elt
     */
}

