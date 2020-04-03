#include<stdio.h> 
#include<stdlib.h> 

int preval;
char lr; 
struct Node 
{ 
	int key; 
	struct Node *left; 
	struct Node *right; 
	int height; 
}; 

// A utility function to get maximum of two integers 
int max(int a, int b); 

// A utility function to get the height of the tree 
int height(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return N->height; 
} 

// A utility function to get maximum of two integers 
int max(int a, int b) 
{ 
	return (a > b)? a : b; 
} 

/* Helper function that allocates a new node with the given key and 
	NULL left and right pointers. */
struct Node* newNode(int key) 
{ 
	struct Node* node = (struct Node*) 
						malloc(sizeof(struct Node)); 
	node->key = key; 
	node->left = NULL; 
	node->right = NULL; 
	node->height = 1; // new node is initially added at leaf 
	return(node); 
} 

// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
struct Node *rightRotate(struct Node *y) 
{ 
	struct Node *x = y->left; 
	struct Node *T2 = x->right; 

	// Perform rotation 
	x->right = y; 
	y->left = T2; 

	// Update heights 
	y->height = max(height(y->left), height(y->right))+1; 
	x->height = max(height(x->left), height(x->right))+1; 

	// Return new root 
	return x; 
} 

// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
struct Node *leftRotate(struct Node *x) 
{ 
	struct Node *y = x->right; 
	struct Node *T2 = y->left; 

	// Perform rotation 
	y->left = x; 
	x->right = T2; 

	// Update heights 
	x->height = max(height(x->left), height(x->right))+1; 
	y->height = max(height(y->left), height(y->right))+1; 

	// Return new root 
	return y; 
} 

// Get Balance factor of node N 
int getBalance(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return height(N->left) - height(N->right); 
} 

// Recursive function to insert a key in the subtree rooted 
// with node and returns the new root of the subtree. 
struct Node* insert(struct Node* node, int key) 
{ 
	/* 1. Perform the normal BST insertion */
	if (node == NULL) 
		return(newNode(key)); 

	if (key < node->key) 
		node->left = insert(node->left, key); 
	else if (key > node->key) 
		node->right = insert(node->right, key); 
	else // Equal keys are not allowed in BST 
		return node; 

	/* 2. Update height of this ancestor node */
	node->height = 1 + max(height(node->left), 
						height(node->right)); 

	/* 3. Get the balance factor of this ancestor 
		node to check whether this node became 
		unbalanced */
	int balance = getBalance(node); 

	// If this node becomes unbalanced, then 
	// there are 4 cases 

	// Left Left Case 
	if (balance > 1 && key < node->left->key) 
		return rightRotate(node); 

	// Right Right Case 
	if (balance < -1 && key > node->right->key) 
		return leftRotate(node); 

	// Left Right Case 
	if (balance > 1 && key > node->left->key) 
	{ 
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
	} 

	// Right Left Case 
	if (balance < -1 && key < node->right->key) 
	{ 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 

	/* return the (unchanged) node pointer */
	return node; 
} 
void inorder(struct Node *root) {
	if(root==NULL)
		return;
	
	inorder(root->left);
	printf("%d\n",root->key);
	inorder(root->right);
	
}

void printTree(struct Node* root, int level) 
{ 
    if (root == NULL) 
        return; 
    if (level == 1) {
    	if(preval==0)
	    	printf("%d (%d B) ",root->key,getBalance(root));
		else 
	    	printf("%d (%d %c) (%d B) ",root->key,preval,lr,getBalance(root)); 
	}
	else if (level > 1) 
    { 
    	preval=root->key;
    	lr='L';
        printTree(root->left, level-1); 
        lr='R';
		printTree(root->right, level-1); 
    } 
} 


/* Drier program to test above function*/
int main() 
{ 
struct Node *root = NULL; 
int data[50],i=0,j,level=1;
while(1) {
	scanf("%d",&data[i]);
	if(data[i]==-1)
		break;
		i++;
}
for(j=0;j<i;j++)
	root = insert(root, data[j]); 
j=1;
	while(1) {
		if(j>i || j==i) {
			level++;
			break;
		}
		j*=2;
		level++;
	}

 
for(j=1;j<=level;j++) {
		printTree(root,j);
		printf("\n");
	} 

return 0; 
} 

