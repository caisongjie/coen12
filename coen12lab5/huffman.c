#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"
#include "pack.h"
#include <sys/stat.h>
#include <ctype.h>
#include <errno.h>

#define p(x) (((x)-1)/2)
#define l(x) ((x)*2+1)
#define r(x) ((x)*2+2)
#define SIZE 256
static struct tree *heap[257];
static struct tree *node[257];
static int count;
void printcode(struct tree *np)
{
    if(getParent(np)!=NULL)
    {
        printcode(getParent(np));
        printf("%d", np==getLeft(getParent(np)));
    }
}
static struct tree *delete()
{
    int curr;
    curr = 0;
    int child;

     
    struct tree *min, *np;
    min = heap[0];
    np = heap[-- count];
    /* if there is a left child,set child equal to the left child
     if there is a right child and it is smaller than child, set child = right child
     compare child to parent
     */
    while(l(curr) < count)    {
        child = l(curr);
    
        if(r(curr) < count && getData(heap[l(curr)]) > getData(heap[r(curr)]))
        {
            child=r(curr);
        }
    
        if(getData(np) > getData(heap[child]))
        {
            heap[curr] = heap[child];
            curr = child;
        }
        else
            break;
    }
    
    heap[curr] = np;
    return min;
}

static void insert(struct tree *np)/* insert new tree in the end ,then pop it if it is smaller than its parent*/
{
    int index;
    index=count ++;
    while(index > 0 && getData(np) < getData(heap[p(index)]))
          {
              heap[index]=heap[p(index)];
              index=p(index);
          }
          heap[index]=np;
}
          

int main(int argc, char *argv[])
{

    int counts[257];
    struct tree *l, *r;

    FILE *fp;
    int ch,c;
    if(argc != 3)
    {
        printf("file name is missing\n");
        exit(EXIT_FAILURE);
    }
    fp=fopen(argv[1], "rb");
    for(c=0;c<=SIZE;c++)
    {
        counts[c]=0;
        node[c]=NULL;
    }
    while ((ch=getc(fp))!=EOF)
    {
        counts[ch] ++;
    }
    fclose(fp);


    for(c=0;c<SIZE;c++)
    {
        if (counts[c]>0)
        {
            insert(node[c]=createTree(counts[c],NULL,NULL));
        }
    }
    insert(node[SIZE]=createTree(0, NULL, NULL));

    while(count>1)/* if there is more than one subtree, combine them into one tree*/
        {
            l=delete();
            r=delete();
            insert(createTree(getData(l)+getData(r),l,r));
        }

    for (c=0; c<=SIZE; c++)
        {
            if(node[c] !=NULL)
            {
                printf(isprint(c) ? " '%c' " : "%03o",c);
                printf(": %d ", counts[c]);
                printcode(node[c]);
                printf("\n");
            }
        }

        pack(argv[1],argv[2],node);
    return 0;
}





