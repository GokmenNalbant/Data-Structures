#include <stdio.h>
#include <stdlib.h>

int x;
char c;
struct node {
	int id;
	int grade;
	struct node *left;
	struct node *right;
};

struct node *CreateNode(int id,int grade) {
	struct node *temp=malloc(sizeof(struct node));
	temp->id=id;
	temp->grade=grade;
	temp->left=NULL;
	temp->right=NULL;
	return temp;
}
struct node *CreateTree(struct node *root,int id,int grade) {
	
	if(root==NULL)
		return CreateNode(id,grade);
		
	if(root->grade>grade)
		root->left=CreateTree(root->left,id,grade);
	else if(root->grade<grade)
		root->right=CreateTree(root->right,id,grade);
	
	return root;
}

void inorder(struct node *root) { 
    if (root != NULL) { 
        inorder(root->left); 
        printf("%d %d\n",root->id,root->grade); 
        inorder(root->right); 
    } 
} 
void PrintTree(struct node *root) {
	int x;
	x=root->grade;
	if(root->left!=NULL)
		printf("%d %d (%d L)",root->left->id,root->left->grade,x);
	if(root->right!=NULL)
		printf("%d %d (%d R)",root->right->id,root->right->grade,x);
	
	if(root->left!=NULL)
		PrintTree(root->left);
	if(root->right!=NULL)
		PrintTree(root->right);
	printf("\n");
}
void printTree(struct node* root, int level) 
{ 
    if (root == NULL) 
        return; 
    if (level == 1) {
    	if(x==0)
	    	printf("%d %d ",root->id, root->grade);
		else 
	    	printf("%d %d (%d %c) ",root->id, root->grade,x,c); 
	}
	else if (level > 1) 
    { 
    	x=root->grade;
    	c='L';
        printTree(root->left, level-1); 
        c='R';
		printTree(root->right, level-1); 
    } 
} 


int main() {
	
	struct node *root=NULL;
	int grades[500];
	int ids[500];
	int level=0,i=0,j=1;
	while(1) {
		scanf("%d",&ids[i]);
		scanf("%d",&grades[i]);
		if(ids[i]==-1 && grades[i]==-1)
			break;
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
	
	root=CreateTree(root,ids[0],grades[0]);
	for(j=1;j<i;j++) {
		CreateTree(root,ids[j],grades[j]);
	}
	
	inorder(root);
	printf("\n");
	for(j=1;j<=level;j++) {
		printTree(root,j);
		printf("\n");
	}

	
	return 0;
}
