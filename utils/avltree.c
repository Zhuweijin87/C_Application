#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct AVLtree_s
{
	int  data;
	int  height;
	struct AVLtree_s  *left;
	struct AVLtree_s  *right;
} AVLtree_t;

#define HEIGHT(pt) ((pt) == NULL ? 0 : ((AVLtree_t *)(pt))->height)
#define MAX(a, b)  ((a) > (b) ? (a) : (b))

AVLtree_t *AVLtree_new(int data, AVLtree_t *left, AVLtree_t *right)
{
	AVLtree_t *node = malloc(sizeof(AVLtree_t));
	if(node == NULL)
		return NULL;

	node->data = data;
	node->height = 0;
	node->left = left;
	node->right = right;

	return node;
}

/* 左左旋转  A 为左子树
 *     A          B
 *    /          / \
 *   B     -->  C   A
 *  /
 * C       
 * */
AVLtree_t *LL_Rotate(AVLtree_t *k)
{
	AVLtree_t  *kLeft;
	//printf("LL_Rotate\n");	
	kLeft = k->left;
	k->left = kLeft->right;
	kLeft->right = k;

	k->height = MAX(HEIGHT(k->left), HEIGHT(k->right))+1;
	kLeft->height = MAX(HEIGHT(kLeft->left), k->height)+1;

	return kLeft;
}

/* 右右旋转 A 为右子树 
 *  A             B
 *   \ 			 / \
 *    B    -->  A   C
 *     \
 *      C  */
AVLtree_t *RR_Rotate(AVLtree_t *k)
{
	AVLtree_t  *kRight;
	//printf("RR_Rotate\n");
	kRight = k->right;
	k->right = kRight->left;
	kRight->left = k;

	k->height = MAX(HEIGHT(k->left), HEIGHT(k->right)) + 1;
	kRight->height = MAX(k->height, HEIGHT(kRight->right)) + 1;
	
	return kRight;
}

AVLtree_t *LR_Rotate(AVLtree_t *k)
{
	//printf("LR_Rotate\n");
	k->left = RR_Rotate(k->left);
	return LL_Rotate(k);
}

AVLtree_t *RL_Rotate(AVLtree_t *k)
{
	//printf("RL_Rotate\n");
	k->right = LL_Rotate(k->right);
	return RR_Rotate(k);
}

AVLtree_t *AVLtree_add(AVLtree_t *root, int data)
{
	if(root == NULL)
	{
		//printf("init add: %d\n", data);
		root = AVLtree_new(data, NULL, NULL);
		if(root == NULL)
		{
			printf("create avltree fail\n");
			return NULL;
		}
	}
	else
	{
		if(data < root->data)
		{
			//printf("add to left: %d\n", data);
			root->left = AVLtree_add(root->left, data);
				
			/* 校验是否平衡,高度相差<=1 */
			if(HEIGHT(root->left) - HEIGHT(root->right) == 2)
			{
				if(data < root->left->data)
					root = LL_Rotate(root);
				else
					root = LR_Rotate(root);
			}
		}
		else if(data > root->data)
		{
			//printf("add to right: %d\n", data);
			root->right = AVLtree_add(root->right, data);

			if(HEIGHT(root->right) - HEIGHT(root->left) == 2)
			{
				if(data > root->right->data)
					root = RR_Rotate(root);
				else
					root = RL_Rotate(root);
			}
		}
		else
		{
			printf("Insert data does exist\n");
		}
	}

	root->height = MAX(HEIGHT(root->left), HEIGHT(root->right)) + 1;
	return root;
}

AVLtree_t *AVLtree_Get(AVLtree_t *root, int data)
{
	AVLtree_t *temp = root;
	while(temp)
	{
		if(data == temp->data)
			return temp;
		else if(data < temp->data)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return temp;
}

AVLtree_t *AVLtree_GetMin(AVLtree_t *root)
{
	AVLtree_t *temp = root;

	while(temp)
	{
		if(temp->left == NULL)
			return temp;
		temp = temp->left;
	}
	return temp;
}

AVLtree_t *AVLtree_GetMax(AVLtree_t *root)
{
	AVLtree_t *temp = root;
	while(temp)
	{
		if(temp->right == NULL)
			return temp;
		temp = temp->right;
	}
	return temp;
}

AVLtree_t *AVLtree_node_delete(AVLtree_t *root, AVLtree_t *node)
{
	if(root == NULL || node == NULL)
		return NULL;

	if(node->data < root->data)
	{
		root->left = AVLtree_node_delete(root->left, node);
	
		//删除左节点是否平衡	
		if(HEIGHT(root->right) - HEIGHT(root->left) == 2)
		{
			AVLtree_t *rnode = root->right;
			if(HEIGHT(rnode->left) > HEIGHT(rnode->right))
				root = RL_Rotate(root);
			else
				root = RR_Rotate(root);
		}
	}
	else if(node->data > root->data)
	{
		root->right = AVLtree_node_delete(root->right, node);
		//删除右节点是否平衡  
		if(HEIGHT(root->left) - HEIGHT(root->right) == 2)
		{
			AVLtree_t *lnode = root->left;
			if(HEIGHT(lnode->right) > HEIGHT(lnode->left))
				root = LR_Rotate(root);
			else
				root = LL_Rotate(root);
		}
	}
	else
	{
		if( root->left && root->right )
		{
			if(HEIGHT(root->left) > HEIGHT(root->right))
			{
				/* 采用替换,可以减少平衡转换 */
				AVLtree_t *max = AVLtree_GetMax(root->left);
				root->data = max->data;
				root->left = AVLtree_node_delete(root->left, max);
			}
			else
			{
				/* 获取右子树最小节点，并替换该节点，删除最小node */
				AVLtree_t *min = AVLtree_GetMin(root->right);
				root->data = min->data;
				root->right = AVLtree_node_delete(root->right, min);
			}
		}
		else
		{
			AVLtree_t *temp = root;
			root = root->left ? root->left : root->right;
			free(temp);
		}
	}

	return root;
}

AVLtree_t *AVLtree_delete(AVLtree_t *root, int data)
{
	AVLtree_t *get = AVLtree_Get(root, data);
	if(!get)
		return root;

	return AVLtree_node_delete(root, get);
}

void PreOrder_Search(AVLtree_t *root)
{
	if(root != NULL)
	{
		PreOrder_Search(root->left);
		printf("%d ", root->data);
		PreOrder_Search(root->right);
	}
}

void InOrder_Search(AVLtree_t *root)
{
	if(root != NULL)
	{
		printf("%d ", root->data);
		PreOrder_Search(root->left);
		PreOrder_Search(root->right);
	}
}

void printAVLtree(AVLtree_t *root)
{
	PreOrder_Search(root);
	//InOrder_Search(root);
	printf("\n");
}

int main()
{
	AVLtree_t  *tree = NULL;

	int   a[] = {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9}; 
	int   asize = sizeof(a)/sizeof(int);
	
	int  i;
	for(i=0; i<asize; i++)
	{
		tree = AVLtree_add(tree, a[i]);
		printAVLtree(tree);
	}

	printf("Min data:%d, Max Data:%d\n", AVLtree_GetMin(tree)->data, AVLtree_GetMax(tree)->data);
	
	PreOrder_Search(tree);
	printf("\n");

	for(i=0; i<asize; i++)
    {
        tree = AVLtree_delete(tree, a[i]);
		printAVLtree(tree);
    }
	
	return 0;
}
