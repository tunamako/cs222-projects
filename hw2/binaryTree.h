#ifndef BINARYTREE_H
#define BINARYTREE_H

template <typename T>
struct TreeNode{
	struct TreeNode<T> *left;
	struct TreeNode<T> *right;
	T value;
	TreeNode(T newValue);
	TreeNode(T newValue, TreeNode<T> *leftNode, TreeNode<T> *rightNode);
	~TreeNode();
};

template <typename T>
using pfnv = void (*)(TreeNode<T> *node);

template <typename T>
class BinaryTree{
private:
	TreeNode<T> *root;
	int heightHelper(TreeNode<T>* aNode);
	void visitHelper(pfnv<T> visitor);
public:
	BinaryTree(TreeNode<T> *aNode);
	~BinaryTree();
	bool isEmpty();
	int height(void);
	void preOrder(pfnv<T> visitor);
	void inOrder(pfnv<T> visitor);
	void postOrder(pfnv<T> visitor);
	void preVisitHelper(TreeNode<int>* aNode, pfnv<T> visitor);
	void postVisitHelper(TreeNode<int>* aNode, pfnv<T> visitor);
	void inVisitHelper(TreeNode<int>* aNode, pfnv<T> visitor);
};
#endif
