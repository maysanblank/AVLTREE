#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node* left;
	struct node* right;
	int ht;
};
struct node* root = NULL;
struct node* rotate_left(struct node* root);
struct node* rotate_right(struct node* root);
int balance_factor(struct node* root);
int height(struct node* root);
struct node* create_node(int data);
struct node* insert(struct node* root, int data);
struct node* delete_node(struct node* root, int data);
struct node* search(struct node* root, int data);
void inorder(struct node* root);
void preorder(struct node* root);
void postorder(struct node* root);
struct node* rotate_left(struct node* root)
{
    struct node* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;
    root->ht = height(root);
    right_child->ht = height(right_child);
    return right_child;
}
struct node* rotate_right(struct node* root)
{
    struct node* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;
    root->ht = height(root);
    left_child->ht = height(left_child);
    return left_child;
}

int balance_factor(struct node* root){
	int lh, rh;
	
	if (root == NULL){
		return 0;
	}
	if (root->left == NULL){
		lh = 0;
	}
	else{
		lh = 1 + root->left->ht;
	}
	if (root->right == NULL){
		rh = 0;
	}
	else {
		rh = 1 + root->right->ht;
	}
	return lh - rh;
}
int height(struct node* root){
	int lh, rh;
	
	if (root == NULL){
		return 0;
	}
	if (root->left == NULL){
		lh = 0;
	}
	else{
		lh = 1 + root->left->ht;
	}
	if (root->right == NULL){
		rh = 0;
	}
	else {
		rh = 1 + root->right->ht;
	}
	if (lh > rh)
		return lh;
	return rh;
}
struct node* create_node(int data){
	struct node* new_node = (struct node*) malloc (sizeof(struct node));
	new_node->data = data;
	new_node->right = NULL;
	new_node->left = NULL;
	
	return new_node;
}
struct node* insert(struct node* root, int data){
	if(root == NULL){
		struct node* new_node = create_node(data);
		root = new_node;
	}
	else if ( data > root->data){
		root->right = insert(root->right, data);
		if (balance_factor(root) == -2){
			if (data > root->right->data){
				root = rotate_left(root);
			}
			else{ 
				root->right = rotate_right(root->right);
				root = rotate_left(root);
			}			
		}		
	}
	else{
		root->left = insert(root->left, data);
		
		if (balance_factor(root) == 2){
			if (data < root->left->data){ 
				root = rotate_right(root);
			}
			else{
				root->left = rotate_left(root->left);
				root = rotate_right(root);

			}
		}
	}
	root->ht = height(root);
	return root;
}
struct node* delete_node(struct node* root, int data){
    if (root == NULL)
        return root;
    if (data < root->data)
        root->left = delete_node(root->left, data);
    else if (data > root->data)
        root->right = delete_node(root->right, data);
    else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
        struct node* temp = root->right;
        while (temp && temp->left != NULL)
            temp = temp->left;
        root->data = temp->data;
        root->right = delete_node(root->right, temp->data);
    }
    if (root == NULL)
        return root;
    root->ht = height(root);
    int balance = balance_factor(root);
    if (balance > 1 && balance_factor(root->left) >= 0)
        return rotate_right(root);
    if (balance > 1 && balance_factor(root->left) < 0) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    if (balance < -1 && balance_factor(root->right) <= 0)
        return rotate_left(root);
    if (balance < -1 && balance_factor(root->right) > 0) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }
 
    return root;
}

struct node* search(struct node* root, int data){
    if (root == NULL || root->data == data)
        return root;
    if (root->data < data)
        return search(root->right, data);
    return search(root->left, data);
}
void inorder(struct node* root)
{
    if (root == NULL)
        return;
 
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
void preorder(struct node* root)
{
    if (root == NULL)
        return;
 
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}
void postorder(struct node* root)
{
    if (root == NULL)
        return;
 
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int main(){

	root = insert(root, 56);
	root = insert(root, 76); 
	root = insert(root, 12); 
	root = insert(root, 34);
	root = insert(root, 23);
	root = insert(root, 68);
	root = insert(root, 98);
	root = insert(root, 231);
	root = insert(root, 16);
	root = insert(root, 565);
	root = insert(root, 732);
	root = insert(root, 417);
	root = insert(root, 892);
	root = insert(root, 1023);

	printf("Angka yang diinput:");
	inorder(root);
	printf("\n");

	root = delete_node(root, 565);

	printf("Command delete 565:");
	inorder(root);
	printf("\n");

	root = delete_node(root, 98);
	
	printf("Command delete 98:");
	inorder(root);
	printf("\n");
	
	printf("Cari data:\n");
	printf("Cari 98:\n");
	struct node* search_result = search(root, 98);
	if (search_result != NULL)
		printf("Data ada");
	else
		printf("Data ga ada\n");
	printf("Cari 1023\n");
	struct node* search_result_2 = search(root, 1023);
	if (search_result_2 != NULL)
    printf("Data ada\n");
	else
    printf("Data ga ada\n");
	return 0;
}

