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


static int findElement(SET *sp,char *elements)
{

assert(sp!=NULL && elements !=NULL);
int k;
for(k=0;k<sp->count;k++)
	{
		if (strcmp(sp->data[k],elements)==0)
		{
		return k;
		}
	}
	return -1;
    /* 
       if element is in the set, return the index
       if not, return -1
    */
}

int numElements(SET *sp)
{

    assert(sp!=NULL);
    return sp->count;

}

bool hasElement(SET *sp,char *elt)
{

    assert(sp!=NULL && elt !=NULL);
    int i=findElement(sp,elt);
    if (i==-1)
    {
        return false;
    }
    else
    {
        return true;
    }

}

bool removeElement(SET *sp, char *elt)
{

    assert(sp!=NULL && elt !=NULL);
    int location=findElement(sp,elt);
    if(location>-1)/* check if elt is in the set*/
    {
        free(sp->data[location]);
        sp->data[location]=sp->data[(sp->count)-1];
        sp->count--;
        return true;
    }
    else
        return false;
        /* switch the elt with the last element, then decrements the count*/
}

bool addElement(SET *sp,char *elt)
{
    assert(sp!=NULL && elt!=NULL);
    if((hasElement(sp,elt)==true) || sp->count==sp->length)
    {
        return false;
    }
    sp->data[sp->count]=strdup(elt);
    sp->count++;
    return true;
    /*
     check if elt is in the set
     if it is not in the set and there is space for adding an element
     add elt at the end and then increase the count
    */
}

