// Implementing Red-Black Tree in C
#include <stdio.h>
#include <stdlib.h>
int preval;
char lr;

enum nodeColor
{
  RED,
  BLACK
};
struct rbNode
{
  int data, color;
  char colority;
  struct rbNode *link[2];
};
struct rbNode *root = NULL;
struct rbNode *createNode(int data)
{
  struct rbNode *newnode;
  newnode = (struct rbNode *)malloc(sizeof(struct rbNode));
  newnode->data = data;
  newnode->color = RED;
  newnode->colority = 'R';
  newnode->link[0] = newnode->link[1] = NULL;
  return newnode;
}
void insertion(int data)
{
  struct rbNode *stack[98], *ptr, *newnode, *xPtr, *yPtr;
  int dir[98], ht = 0, index;
  ptr = root;
  if (!root)
  {
    root = createNode(data);
    return;
  }
  stack[ht] = root;
  dir[ht++] = 0;
  while (ptr != NULL)
  {
    if (ptr->data == data)
    {
      printf("Duplicates Not Allowed!!\n");
      return;
    }
    index = (data - ptr->data) > 0 ? 1 : 0;
    stack[ht] = ptr;
    ptr = ptr->link[index];
    dir[ht++] = index;
  }
  stack[ht - 1]->link[index] = newnode = createNode(data);
  while ((ht >= 3) && (stack[ht - 1]->color == RED))
  {
    if (dir[ht - 2] == 0)
    {
      yPtr = stack[ht - 2]->link[1];
      if (yPtr != NULL && yPtr->color == RED)
      {
        stack[ht - 2]->color = RED;
        stack[ht - 1]->color = yPtr->color = BLACK;
        stack[ht - 2]->colority = 'R';
        stack[ht - 1]->colority = yPtr->colority = 'B';
        ht = ht - 2;
      }
      else
      {
        if (dir[ht - 1] == 0)
        {
          yPtr = stack[ht - 1];
        }
        else
        {
          xPtr = stack[ht - 1];
          yPtr = xPtr->link[1];
          xPtr->link[1] = yPtr->link[0];
          yPtr->link[0] = xPtr;
          stack[ht - 2]->link[0] = yPtr;
        }
        xPtr = stack[ht - 2];
        xPtr->color = RED;
        yPtr->color = BLACK;
        xPtr->colority = 'R';
        yPtr->colority = 'B';
      	xPtr->link[0] = yPtr->link[1];
        yPtr->link[1] = xPtr;
        if (xPtr == root)
        {
          root = yPtr;
        }
        else
        {
          stack[ht - 3]->link[dir[ht - 3]] = yPtr;
        }
        break;
      }
    }
    else
    {
      yPtr = stack[ht - 2]->link[0];
      if ((yPtr != NULL) && (yPtr->color == RED))
      {
        stack[ht - 2]->color = RED;
        stack[ht - 1]->color = yPtr->color = BLACK;
        stack[ht - 2]->colority = 'R';
        stack[ht - 1]->colority = yPtr->colority = 'B';
        ht = ht - 2;
      }
      else
      {
        if (dir[ht - 1] == 1)
        {
          yPtr = stack[ht - 1];
        }
        else
        {
          xPtr = stack[ht - 1];
          yPtr = xPtr->link[0];
          xPtr->link[0] = yPtr->link[1];
          yPtr->link[1] = xPtr;
          stack[ht - 2]->link[1] = yPtr;
        }
        xPtr = stack[ht - 2];
        yPtr->color = BLACK;
        xPtr->color = RED;
        yPtr->colority = 'B';
        xPtr->colority = 'R';
        xPtr->link[1] = yPtr->link[0];
        yPtr->link[0] = xPtr;
        if (xPtr == root)
        {
          root = yPtr;
        }
        else
        {
          stack[ht - 3]->link[dir[ht - 3]] = yPtr;
        }
        break;
      }
    }
  }
  root->color = BLACK;
  root->colority = 'B';
}

void inorderTraversal(struct rbNode *node)
{
  if (node)
  {
    inorderTraversal(node->link[0]);
    printf("%d\n", node->data);
    inorderTraversal(node->link[1]);
  }
  return;
}
void printTree(struct rbNode* root, int level) 
{ 
	if (root == NULL) 
        return; 
    if (level == 1) {
    	if(preval==0)
	    	printf("%d %c ",root->data,root->colority);
		else 
	    	printf("%d %c (%d %c) ",root->data,root->colority,preval,lr); 
	}
	else if (level > 1) 
    { 
    	preval=root->data;
    	lr='L';
        printTree(root->link[0], level-1); 
        lr='R';
		printTree(root->link[1], level-1); 
    } 
} 
int main()
{
  int data;
  int i=0,j=1,level=0;
  while (1)
  {
 	  scanf("%d", &data);
 	  if(data==-1)
      break;
      insertion(data);
      i++;
  }
  while(1) {
		if(j>i || j==i) {
			level++;
			break;
		}
		j*=2;
		level++;
	}
  
  
      inorderTraversal(root);
      printf("\n");
   
   	  for(j=1;j<=level;j++) {
		printTree(root,j);
		printf("\n");
	} 
  return 0;
}
