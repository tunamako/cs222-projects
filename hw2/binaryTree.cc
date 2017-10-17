#include "binaryTree.h"

template <typename T>
TreeNode<T>::TreeNode(T newValue){
	this->value = newValue;
	this->left = 0;
	this->right = 0;
}

template <typename T>
TreeNode<T>::TreeNode(T newValue, TreeNode<T> *leftNode, TreeNode<T> *rightNode){
	this->value = newValue;
	this->left = leftNode;
	this->right = rightNode;
}

template <typename T>
TreeNode<T>::~TreeNode(){
	if(this->left != nullptr) {
		delete this->left;
	}
	if(this->right != nullptr) {
		delete this->right;
	}
}

template <typename T>
BinaryTree<T>::BinaryTree(TreeNode<T> * aNode){
	this->root = aNode;
}

template <typename T>
BinaryTree<T>::~BinaryTree() {
	if(this->root != nullptr) {
		delete this->root;
	}
}

template <typename T>
bool BinaryTree<T>::isEmpty(){
	return !this->root;
}

template<typename T>
int BinaryTree<T>::heightHelper(TreeNode<T>* aNode){
	if(aNode == nullptr){
		return 0;
	}
	else{
		int leftHeight = heightHelper(aNode->left);
		int rightHeight= heightHelper(aNode->right);
		return leftHeight > rightHeight
			? leftHeight+1
			: rightHeight+1;
	}
}

template <typename T>
int BinaryTree<T>::height(){
	return heightHelper(this->root);
}


template <typename T>
void BinaryTree<T>::preOrder(pfnv<T> visitor){
	if(this->root != nullptr){
		preVisitHelper(this->root, visitor);
	}
}

template <typename T>
void BinaryTree<T>::inOrder(pfnv<T> visitor){
	if(this->root != nullptr){
		inVisitHelper(this->root, visitor);
	}
}

template <typename T>
void BinaryTree<T>::postOrder(pfnv<T> visitor){
	if(this->root != nullptr){
		postVisitHelper(this->root, visitor);
	}
}

template <typename T>
void BinaryTree<T>::preVisitHelper(TreeNode<int>* aNode, pfnv<T> visitor){
	visitor(aNode);
	if(aNode->left != nullptr){
		preVisitHelper(aNode->left, visitor);
	}
	if(aNode->right != nullptr){
		preVisitHelper(aNode->right, visitor);
	}
}

template <typename T>
void BinaryTree<T>::inVisitHelper(TreeNode<int>* aNode, pfnv<T> visitor){
	if(aNode->left != nullptr){
		inVisitHelper(aNode->left, visitor);
	}
	visitor(aNode);
	if(aNode->right != nullptr){
		inVisitHelper(aNode->right, visitor);
	}
}

template <typename T>
void BinaryTree<T>::postVisitHelper(TreeNode<int>* aNode, pfnv<T> visitor){
	if(aNode->left != nullptr){
		postVisitHelper(aNode->left, visitor);
	}
	if(aNode->right != nullptr){
		postVisitHelper(aNode->right, visitor);
	}
	visitor(aNode);
}

#include "binaryTreeConfig.h"
