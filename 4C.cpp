#include <iostream> 
#include <bits/stdc++.h> 
using namespace std; 

//***Struct and Constructor***------------------------------------------------//
struct Node { 
    int value,balanceFactor,height;
    struct Node *left, *right, *back; 
}; 
  
Node* newNode(int data) 
{ 
    Node* temp = new Node; 
  
    temp->value = data; 
  
    temp->left = NULL; 
    temp->right = NULL;
    temp->back = NULL;
	temp->balanceFactor = 0;
	temp->height = 0;
  
    return temp; 
} 
/* Print nodes at a given level */
void printGivenLevel(Node* root, int level) 
{ 
    if (root == NULL) 
        return; 
    if (level == 0) 
        printf("%d ", root->value); 
    else if (level > 0) 
    { 
        printGivenLevel(root->left, level-1); 
        printGivenLevel(root->right, level-1); 
    } 
} 

/* Function to line by line print level order traversal a tree*/
void printLevelOrder(Node* root) 
{ 
    int h = root->height; 
    int i; 
    for (i=0; i<=h; i++) 
    { 
        printGivenLevel(root, i); 
        printf("\n"); 
    } 
} 


void heightManager(Node* root){
    Node* manager=root;
    //Height Managment:-------------------------------------------------------//
    if(manager->right!=NULL && manager->left!=NULL){
        if(manager->right->height > manager->left->height){
            manager->height=manager->right->height+1;
        }
        else{
            manager->height=manager->left->height+1;
        }
    }
    else if(manager->right==NULL && manager->left!=NULL){
        manager->height=manager->left->height+1;
    }
    else if(manager->right!=NULL && manager->left==NULL){
        manager->height=manager->right->height+1;
    }
    else{
        manager->height=0;
    }
}

void balanceManager(Node* root){
    Node* manager=root;
    //Balance Managment:------------------------------------------------------//
    if(manager->right!=NULL && manager->left!=NULL){
        manager->balanceFactor=manager->left->height - manager->right->height;
    }
    else if(manager->right==NULL && manager->left!=NULL){
        manager->balanceFactor=manager->left->height+1;
    }
    else if(manager->right!=NULL && manager->left==NULL){
        manager->balanceFactor=-manager->right->height-1;
    }
    else if(manager->right==NULL && manager->left==NULL){
        manager->balanceFactor=0;
    }
}

//***Left left inbalance***----------------------------------------------------------//
Node* rightRightRotation(Node* grandparent){
    cout<<"Left left inbalance found!\n";
    Node* fixer;
    Node* back=grandparent->back;
    Node* temp;
    Node* parent=grandparent->left;
    if(parent->right!=NULL){
        temp=parent->right;
    }
    else{
        temp=NULL;
    }
    parent->back=back;
    parent->left->back=parent;
    parent->right=grandparent;
    parent->right->back=parent;
    parent->right->left=temp;
    
    heightManager(parent->left);
    balanceManager(parent->left);
    heightManager(parent->right);
    balanceManager(parent->right);
    heightManager(parent);
    balanceManager(parent);
    
    if(parent->back!=NULL){
        fixer=parent;
        parent->back->left=fixer;
    }
    
    return parent;
}
//***Right right inbalance***--------------------------------------------------------//
Node* leftLeftRotation(Node* grandparent){
    cout<<"Right right inbalance found!\n";
    Node* fixer;
    Node* back=grandparent->back;
    Node* temp;
    Node* parent=grandparent->right;
    if(parent->left!=NULL){
        temp=parent->left;
    }
    else{
        temp=NULL;
    }
    parent->back=back;
    parent->right->back=parent;
    parent->left=grandparent;
    parent->left->back=parent;
    parent->left->right=temp;
    
    heightManager(parent->left);
    balanceManager(parent->left);
    heightManager(parent->right);
    balanceManager(parent->right);
    heightManager(parent);
    balanceManager(parent);
    
    if(parent->back!=NULL){
        fixer=parent;
        parent->back->right=fixer;
    }
    
    return parent;
}

//***Right left inbalance***--------------------------------------------------------//
Node* leftRightRotation(Node* grandparent){
    cout<<"Right left inbalance found!\n";
    Node* fixer,*fixer1,*fixer2,*fixer3,*fixer4;
    Node* back=grandparent->back;
    Node* parent=grandparent->left->right;
    if(parent->left!=NULL && parent->left->left!=NULL){
        fixer1=parent->left->left;
    }
    else{
        fixer1=NULL;
    }
    //cout<<"Here 1\n";
    if(parent->left!=NULL && parent->left->right!=NULL && parent->left->right->left!=NULL){
        fixer2=parent->left->right->left;
    }
    else{
        fixer2=NULL;
    }
    //cout<<"Here 2\n";
    if(parent->left!=NULL && parent->left->right!=NULL && parent->left->right->right!=NULL){
        fixer3=parent->left->right->right;
    }
    else{
        fixer3=NULL;
    }
    //cout<<"Here 3\n";
    parent->back=back;
    parent->right=grandparent;
    parent->right->back=parent;
    parent->left=grandparent->left;
    parent->left->back=parent;
    //cout<<"Here 4\n";
    if(parent->right!=NULL){
        parent->right->left=fixer3;
    }
    if(parent->left!=NULL){
        parent->left->right=fixer2;
    }
    //cout<<"Here 5\n";
    heightManager(parent->left);
    balanceManager(parent->left);
    heightManager(parent->right);
    balanceManager(parent->right);
    heightManager(parent);
    balanceManager(parent);
    
    if(parent->back!=NULL){
        fixer=parent;
        parent->back->left=fixer;
    }
    
    return parent;
}

//***Left right inbalance***--------------------------------------------------------//
Node* rightLeftRotation(Node* grandparent){
    cout<<"Left right inbalance found!\n";
    Node* fixer,*fixer1,*fixer2,*fixer3,*fixer4;
    Node* back=grandparent->back;
    Node* parent=grandparent->right->left;
    if(parent->right!=NULL && parent->right->right!=NULL){
        fixer1=parent->right->right;
    }
    else{
        fixer1=NULL;
    }
    //cout<<"Here 1\n";
    if(parent->right!=NULL && parent->right->left!=NULL && parent->right->left->right!=NULL){
        fixer2=parent->right->left->right;
    }
    else{
        fixer2=NULL;
    }
    //cout<<"Here 2\n";
    if(parent->right!=NULL && parent->right->left!=NULL && parent->right->left->left!=NULL){
        fixer3=parent->right->left->left;
    }
    else{
        fixer3=NULL;
    }
    //cout<<"Here 3\n";
    parent->back=back;
    parent->left=grandparent;
    parent->left->back=parent;
    parent->right=grandparent->right;
    parent->right->back=parent;
    //cout<<"Here 4\n";
    if(parent->left!=NULL){
        parent->left->right=fixer3;
    }
    if(parent->right!=NULL){
        parent->right->left=fixer2;
    }
    //cout<<"Here 5\n";
    heightManager(parent->left);
    balanceManager(parent->left);
    heightManager(parent->right);
    balanceManager(parent->right);
    heightManager(parent);
    balanceManager(parent);
    
    if(parent->back!=NULL){
        fixer=parent;
        parent->back->right=fixer;
    }
    
    return parent;
}
//***Updating and fixing inbalances***----------------------------------------//
Node* fixerUpper(Node* root, int factor){
	
	/*
	This fixerUpper() is responsible from fixing from bottom to top and balance 
	the tree. It does so with the help of the heightManager() and balanceManager().
	Also it is responsible to choose how to rotate to fix inbalances. The functions
	responsible for that are rightRightRotation(), rightLeftRotation(),
	leftLeftRotation() and leftRightRotation().
	*/
	
    Node* manager=root;
    Node* fixer;
    
    while(manager->back!=NULL){
        manager=manager->back;
        heightManager(manager);
        balanceManager(manager);
        if(manager->balanceFactor==-2){
            if(manager->right->balanceFactor==-1){
                manager=leftLeftRotation(manager);
            }
            else{
                manager=rightLeftRotation(manager);
            }
        }
        else if(manager->balanceFactor==2){
            if(manager->left->balanceFactor==1){
                manager=rightRightRotation(manager);
            }
            else{
                manager=leftRightRotation(manager);
            }
        }
    }
    
    return manager;
}

//***Inserting New Element***-------------------------------------------------//
Node* insert(Node* root, int value) 
{ 
	/*
	insert() navigates from top to bottom iterating the tree and finds where to 
	put the new value and calls the function fixerUpper().
	In the end, it makes sure it returns root. 
	(Normaly the it skips the loop as it is not needed.)
	*/
	
    Node* newnode = newNode(value); 
  

    Node* x = root; 
  
    Node* y = NULL; 
  
    while (x != NULL) { 
        y = x; 
        if (value < x->value) 
            x = x->left; 
        else
            x = x->right; 
    } 
  
    if (y == NULL){
        y = newnode;
        
    } 
  
    else if (value < y->value){
        y->left = newnode;
        y->left->back=y;
        
        y->balanceFactor+=1;
        
        if(y->right!=NULL){
            if(y->right->height > y->left->height){
                y->height=y->right->height+1;
            }
            else{
                y->height=y->left->height+1;
            }
        }
        else{
            y->height=y->left->height+1;
        }
        
        y=fixerUpper(y,1);
    } 
  
    else{
        y->right = newnode;
        y->right->back=y;
        
        y->balanceFactor-=1;
        
        if(y->left!=NULL){
            if(y->left->height > y->right->height){
                y->height=y->left->height+1;
            }
            else{
                y->height=y->right->height+1;
            }
        }
        else{
            y->height=y->right->height+1;
        }
        
        y=fixerUpper(y,-1);
    }
    
    while(y->back!=NULL){
        y=y->back;
    }
    
    return y; 
} 


/****Delete Function***-------------------------------------------------------// Unfinished!!
void deleteIter(Node* root, int searchValue) 
{ 
    Node* x = root; 
  
    Node* y = NULL; 
  
    while (x != searchValue) { 
        y = x; 
        if (searchValue < x->value){ 
            x = x->left; 
        }
        else if(searchValue < x->value){
            x = x->right;
        }
        else{
            if(x->left==NULL){
                Node* temp=x;
                x=x->right;
                x->back=temp->back;
                if(temp->back->left!= NULL && temp->back->left->value==searchValue){temp->back->left=x;}
                else if(temp->back->right!= NULL && temp->back->right->value==searchValue){temp->back->right=x;}
                
                //***********           MANAGE THE CHILDREN AND UPDATE          ***********
                
            }
        }
        
    } 
    
    
}
*/
//***Maximum Function***------------------------------------------------------//
int findMaxIter(Node* root)  
{   
    if (root == NULL){return 0;}
    
    while(root->right!=NULL){root=root->right;}
    return root->value;
}  
//***Minimum Function***------------------------------------------------------//
int findMinIter(struct Node* root) 
{ 
    if (root == NULL){return 0;}
    
    while(root->left!=NULL){root=root->left;}
    return root->value;
}

//***Next Element, Prev Element & Search Functions***---------------------------------------//
Node* search(Node* manager, int value) 
{ 
    while (manager != NULL) { 
        if (value > manager->value) 
            manager = manager->right; 
  
        else if (value < manager->value) 
            manager = manager->left; 
        else
            return manager; 
    } 
    return manager; 
} 

int findNextIter(Node *root, Node *someNode) 
{ 
    if( someNode->right != NULL ){
        Node* temp=search(root,findMinIter(someNode->right));//findMin() always turns to the leftmost child under a cerain root.
        return temp->value;
    }
  
    Node *successor = NULL; 
  
    while (root != NULL) 
    { 
        if (someNode->value < root->value){successor = root;root = root->left;} 
        else if (someNode->value > root->value){root = root->right;} 
        else{break;} 
    } 
  
    return successor->value; 
} 
int findPrevIter(Node *root, Node *someNode) 
{ 
    if( someNode->right != NULL ){
        Node* temp=search(root,findMaxIter(someNode->left));//findMin() always turns to the leftmost child under a cerain root.
        return temp->value;
    }
  
    Node *successor = NULL; 
  
    while (root != NULL) 
    { 
        if (someNode->value > root->value){successor = root;root = root->right;} 
        else if (someNode->value < root->value){root = root->left;} 
        else{break;} 
    } 
  
    return successor->value; 
} 

//***Main Function***---------------------------------------------------------//
int main() 
{ 
    Node* root = NULL; 
    //root=insert(root, rand(//) % 100 + 1); 
	//for(int i=0 ; i<20 ; i++){int x=rand() % 100 + 1; insert(root,x);}
	//root =insert(root,20);
	//root =insert(root,10);
	//root =insert(root,20);
	//root =insert(root,30);
	/*
	root =insert(root,15);
	root =insert(root,25);
	root =insert(root,35);
	root =insert(root,45);
	root =insert(root,100);
	root =insert(root,5);
	root =insert(root,3);
	root =insert(root,4);
	*/
	
	/*
	root =insert(root,10);
	printLevelOrder(root);cout<<endl;
	root =insert(root,15);
	printLevelOrder(root);cout<<endl;
	root =insert(root,20);
	printLevelOrder(root);cout<<endl;
	root =insert(root,3);
	printLevelOrder(root);cout<<endl;
	root =insert(root,2);
	printLevelOrder(root);cout<<endl;
	root =insert(root,1);
	*/
	root =insert(root,10);
	printLevelOrder(root);cout<<endl;
	root =insert(root,20);
	printLevelOrder(root);cout<<endl;
	root =insert(root,15);
	printLevelOrder(root);cout<<endl;
	root =insert(root,25);
	printLevelOrder(root);cout<<endl;
	root =insert(root,35);
	printLevelOrder(root);cout<<endl;
	root =insert(root,45);
	printLevelOrder(root);cout<<endl;
	root =insert(root,100);
	printLevelOrder(root);cout<<endl;
	root =insert(root,5);
	printLevelOrder(root);cout<<endl;
	root =insert(root,3);
	printLevelOrder(root);cout<<endl;
	root =insert(root,4);
	
	printLevelOrder(root);
	
	cout<<"\n\nMAX\t=\t"<<findMaxIter(root)<<endl;
	cout<<"MIN\t=\t"<<findMinIter(root)<<endl;
	
	cout<<"Next of 5 is "<<findNextIter(root,search(root,5))<<endl;
	cout<<"Prev of 5 is "<<findPrevIter(root,search(root,5))<<endl;
	
}
	