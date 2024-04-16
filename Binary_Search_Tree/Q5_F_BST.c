//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 5
		 Implementing 'remove node' operation for BST*/
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS2(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);
BSTNode* removeNodeFromTree(BSTNode *root, int value);
BSTNode* removeNodeFromTree2(BSTNode *root, int value);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode * root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("3: Insert an integer to remove from the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS2(root); // You need to code this function
			printf("\n");
			break;
		case 3:
			printf("Input an integer that you want to remove from the Binary Search Tree: ");
			scanf("%d", &i);
			removeNodeFromTree2(root, i);
			postOrderIterativeS2(root);
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS2(BSTNode *root)
{
	if (root == NULL) return;

	Stack tmp1 = {NULL};
	Stack tmp2 = {NULL};
	push(&tmp1, root);

	while (1) {
		root = pop(&tmp1);
		if (!root) break;
		push(&tmp2, root);

		if (root->left != NULL) {
			push(&tmp1, root->left);
		}
		if (root->right != NULL) {
			push(&tmp1, root->right);
		}
	}

	while(1) {
		root = pop(&tmp2);
		if (!root) break;
		printf("%d ", root->item);
	}
	
}

/* Given a binary search tree and a key, this function
   deletes the key and returns the new root. Make recursive function. */
BSTNode* removeNodeFromTree(BSTNode *root, int value)
{
	if (root == NULL) return NULL;
	// 1. 삭제될 값이 root일 때
	if (root->item == value) {
		// 1.1 root의 자식이 0개
		if (root->left == NULL && root->right == NULL) {
			printf("[1.1] deleted: %d \n", root->item);
			root = NULL;
			return root;
		}
		// 1.2.1 root의 자식이 1개 - left
		if (root->left != NULL && root->right == NULL) {
			printf("[1.2.1] deleted: %d \n", root->item);
			root = root->left;
			return root;
		}
		// 1.2.2 root의 자식이 1개 - right
		if (root->left == NULL && root->right != NULL) {
			printf("[1.2.2] deleted: %d \n", root->item);
			root = root->right;
			return root;
		}
		// 1.3 root의 자식이 2개 (예외, 후임자의 right가 존재)
		if (root->left != NULL && root->right != NULL) {
			printf("[1.3] deleted: %d \n", root->item);
			BSTNode* successor = root->right;
			BSTNode* successorParent = root;
			
			// 후임자 찾기
			for (;successor->left; successor = successor->left) {
				successorParent = successor;
			}

			// root와 후임자의 값 교환
			int tmp = root->item;
			root->item = successor->item;
			successor->item = tmp;

			// 후임자 삭제
			successorParent->left = successor->right;

			return root;
		}
	} 
	// 2. 삭제될 값(deleted)이 root가 아닐 때
	else {
		// deleted 찾기
		BSTNode* deleted = root;
		BSTNode* deletedParent = NULL;
		while (deleted != NULL) {
			if (deleted->item < value) {
				deletedParent = deleted;
				deleted = deleted->right;
			} 
			else if (deleted->item > value) {
				deletedParent = deleted;
				deleted = deleted->left;
			} else {
				break;
			}
		}

		if (deleted == NULL) return root; // 삭제할 값이 존재하지 않은

		// 2.1 deleted의 자식이 0개
		if (deleted->left == NULL && deleted->right == NULL) {
			printf("[2.1] deleted: %d, deletedParent: %d \n", deleted->item, deletedParent->item);
			if (deletedParent->left == deleted) deletedParent->left = NULL;
			if (deletedParent->right == deleted) deletedParent->right = NULL;
			return root;
		}
		// 2.2.1 deleted의 자식이 1개 - left
		if (deleted->left != NULL && deleted->right == NULL) {
			printf("[2.2.1] deleted: %d, deletedParent: %d \n", deleted->item, deletedParent->item);
			if (deletedParent->left == deleted) deletedParent->left = deleted->left;
			if (deletedParent->right == deleted) deletedParent->right = deleted->left;
			return root;
		}
		// 2.2.2 deleted의 자식이 1개 - right
		if (deleted->left != NULL && deleted->right == NULL) {
			printf("[2.2.2] deleted: %d, deletedParent: %d \n", deleted->item, deletedParent->item);
			if (deletedParent->left == deleted) deletedParent->left = deleted->right;
			if (deletedParent->right == deleted) deletedParent->right = deleted->right;
			return root;
		}
		// 2.3 deleted의 자식이 2개 (예외, 후임자의 right가 존재)
		if (root->left != NULL && root->right != NULL) {
			printf("[2.3] deleted: %d, deletedParent: %d \n", deleted->item, deletedParent->item);
			BSTNode* successor = deleted->right;
			BSTNode* successorParent = deleted;
			
			// 후임자 찾기
			for (;successor->left; successor = successor->left) {
				successorParent = successor;
			}

			// root와 후임자의 값 교환
			int tmp = deleted->item;
			deleted->item = successor->item;
			successor->item = tmp;

			// 후임자 삭제
			successorParent->left = successor->right;

			return root;
		}
	}
	return NULL;
}

BSTNode* minValueNode(BSTNode* node) {
	BSTNode* current = node;

	// 가장 왼쪽 leaf 노드 == 가장 작은 노드
	while (current && current->left != NULL)
        current = current->left;
	
	return current;
}

BSTNode* removeNodeFromTree2(BSTNode *root, int value) {
	// 삭제할 노드를 발견하지 못하면 root 리턴
	if (root == NULL) return root;

	if (value < root->item) {
		root->left = removeNodeFromTree2(root->left, value);
	} else if (value > root->item) {
		root->right = removeNodeFromTree2(root->right, value);
	} else {
		if (root->left == NULL) {
			BSTNode* tmp = root->right;
			free(root);
			return tmp;
		} else if (root->right == NULL)
		{
			BSTNode* tmp = root->left;
			free(root);
			return tmp;
		}
		BSTNode* tmp = minValueNode(root->right);
		root->item = tmp->item;
		root->right = removeNodeFromTree2(root->right, tmp->item);
	}
	return root;
}
///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
