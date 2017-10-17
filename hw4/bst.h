#ifndef BST_H
#define BST_H

#include "node.h"

template <typename K, typename V>
class Bst{
private:
	TreeNode<K,V> *root;
public:
	Bst(TreeNode<K,V> *aNode);
	~Bst();
	TreeNode<K,V>* getRoot();
	bool isEmpty();
	int height(void);
	void preOrder(pfnv<K,V> visitor);
	void inOrder(pfnv<K,V> visitor);
	void postOrder(pfnv<K,V> visitor);
	void bstAdd(K aKey, V aValue);
	void add(K aKey, V aValue);
	bool includes(K aKey);
	V retrieve(K aKey);
	void bstRemove(K aKey);
};

#endif
