#include "set.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define Empty 0
#define Filled 1
#define Deleted 2



struct set
{
	int count;
	int length;
	char **data;
    char *flags;
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
    sp->flags=malloc(maxElts * sizeof(char));
    assert(sp->flags!=NULL);
    int i;
    for(i=0;i<maxElts;i++)
    {
    sp->flags[i]=Empty;

    }
	return sp;
    /*
     create and initialize the set and flags
     */
    
}

unsigned hashString(char *s)
{
    unsigned hash = 0;
    while (*s != '\0')
    {
    hash = 31 * hash + *s ++;
    }
    return hash;
}
                     
void destroySet(SET *sp)
{
    
    int i;
    assert(sp!=NULL);
    for(i=0;i<sp->length;i++)
    {
        if (sp->flags[i]==Filled)
        {
                free (sp->data[i]);
        }
    }
    free(sp->flags);
    free(sp->data);
    free(sp);
    
}


static int findElement(SET *sp,char *elements, bool *found)
{
    int avail=-1;
    assert(sp!=NULL && elements !=NULL);
    int start=hashString(elements)%sp->length;
    int loc,k;
    for(k=0;k<sp->length;k++)
	{
        loc=(start+k)%sp->length;
        if (sp->flags[loc]==Empty)
        {
            *found=false;
            if(avail==-1)
            {
            return loc;
            }
            return avail;
        }
        else if(sp->flags[loc]==Deleted)
        {
            if(avail==-1)
            {
            avail=loc;
            }
        }
        else if(strcmp(sp->data[loc],elements)==0)
        {
            *found=true;
            return loc;
        }
	}
    *found=false;
    return avail;
    /*
     if the location is empty, returns location if there is nothing deleted in the previous home location(avail==-1), or returns avail if avail != -1
     if the location is deleted, set avail equal to that location
     if the element is on the location, return location
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
    if (!found)
    {
        return false;
    }
        free(sp->data[location]);

        sp->count--;
        sp->flags[location]=Deleted;
        return true;
    /*
     set flags to deleted when removes an element
     */

}

bool addElement(SET *sp,char *elt)
    {
        bool found;
        assert(sp!=NULL && elt!=NULL);

        int loc;
        loc=findElement(sp,elt,&found);

        if (found== true || sp->count==sp->length)
        {
            return false;
        }
        sp->data[loc]=strdup(elt);
        sp->flags[loc]=Filled;
        sp->count++;
        return true;
        /*
         find the location first. If the element is not on the list, add it and then set flags to filled.
         */
    }
                     


