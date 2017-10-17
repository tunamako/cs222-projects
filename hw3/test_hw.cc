#include "gtest/gtest.h"
#include "bst.h"
#include <string.h>
#include <stack>

TEST(TreeNodeTest, testConstructors){
	TreeNode <int,int> *node1 = new TreeNode<int,int>(5, 5, nullptr);
	TreeNode <int,int> *node2 = new TreeNode<int,int>(6, 6, nullptr);
	TreeNode <int,int> *node3 = new TreeNode<int,int>(7, 7, nullptr, node1, node2);

	EXPECT_EQ(node1->value, 5);
	EXPECT_EQ(node2->value, 6);
	EXPECT_EQ(node3->value, 7);
	EXPECT_EQ(node3->left, node1);
	EXPECT_EQ(node3->right, node2);

	delete node3;
}

int treeSpec[]={1,3,-2,9,-4,0};
Bst<int,int>* treeBuilder(int* treeData){
	std::stack<TreeNode<int,int> *> nodeStack;
	int* nextIntRef = treeData;
	while(*nextIntRef != 0){
		TreeNode<int,int> *node;
		if(*nextIntRef > 0){
			node = new TreeNode<int,int>(*nextIntRef, *nextIntRef, nullptr);
		}
		else{
			TreeNode<int,int> *right = nodeStack.top();
			nodeStack.pop();
			TreeNode<int,int> *left = nodeStack.top();
			nodeStack.pop();
			node = new TreeNode<int,int>(*nextIntRef * (-1), *nextIntRef, nullptr, left, right);
		}
		nodeStack.push(node);
		nextIntRef++;
	}
	return new Bst<int,int> (nodeStack.top());
}

TEST(BstTest, testConstructor){
	Bst<int,int> *aTree = new Bst<int,int>(new NullTreeNode<int,int>(nullptr));
	EXPECT_TRUE(aTree->isEmpty());
	delete aTree;
	aTree = treeBuilder(treeSpec);
	EXPECT_FALSE(aTree->isEmpty());
	delete aTree;
}


TEST(BstTest, testHeight){
  Bst<int,int> *aTree = new Bst<int,int>(new NullTreeNode<int,int>(nullptr));
	EXPECT_EQ(aTree->height(),0);
	delete aTree;
	aTree = treeBuilder(treeSpec);
	EXPECT_EQ(aTree->height(),3);
	delete aTree;
}

static int visitedNodes[32];
static int nodeIndex;
void visitNode(TreeNode<int,int>* aNode){
	visitedNodes[nodeIndex] = aNode->value;
	nodeIndex++;
}

TEST(BstTest, testPostOrder){
	nodeIndex = 0;
	Bst<int,int> *aTree = treeBuilder(treeSpec);
	aTree->postOrder(visitNode);
	EXPECT_EQ(visitedNodes[0],1);
	EXPECT_EQ(visitedNodes[1],3);
	EXPECT_EQ(visitedNodes[2],-2);
	EXPECT_EQ(visitedNodes[3],9);
	EXPECT_EQ(visitedNodes[4],-4);
	delete aTree;

}

TEST(BstTest, testPreOrder){
	nodeIndex = 0;
	Bst<int,int> *aTree = treeBuilder(treeSpec);
	aTree->preOrder(visitNode);
	EXPECT_EQ(visitedNodes[0],-4);
	EXPECT_EQ(visitedNodes[1],-2);
	EXPECT_EQ(visitedNodes[2],1);
	EXPECT_EQ(visitedNodes[3],3);
	EXPECT_EQ(visitedNodes[4],9);
	delete aTree;

}

TEST(BstTest, testInOrder){
	nodeIndex = 0;
	Bst<int,int> *aTree = treeBuilder(treeSpec);
	aTree->inOrder(visitNode);
	EXPECT_EQ(visitedNodes[0],1);
	EXPECT_EQ(visitedNodes[1],-2);
	EXPECT_EQ(visitedNodes[2],3);
	EXPECT_EQ(visitedNodes[3],-4);
	EXPECT_EQ(visitedNodes[4],9);
	delete aTree;
}

TEST(BstTest, testAdd){
	  Bst<int,int> *aTree = new Bst<int,int>(new NullTreeNode<int,int>(nullptr));
		nodeIndex = 0;
		aTree->inOrder(visitNode);
		EXPECT_EQ(nodeIndex,0);
		aTree->add(17, -17);
		aTree->inOrder(visitNode);
		EXPECT_EQ(nodeIndex,1);
		EXPECT_EQ(visitedNodes[0],-17);
		aTree->add(15,-15);
		nodeIndex = 0;
		aTree->inOrder(visitNode);
		EXPECT_EQ(visitedNodes[0],-15);
		EXPECT_EQ(visitedNodes[1], -17);
		aTree->add(11,-11);
		aTree->add(9,-9);
		aTree->add(13,-13);
		aTree->add(50,-50);
		aTree->add(37,-37);
		nodeIndex = 0;
		aTree->inOrder(visitNode);
		EXPECT_EQ(visitedNodes[0],-9);
		EXPECT_EQ(visitedNodes[1], -11);
		EXPECT_EQ(visitedNodes[2],-13);
		EXPECT_EQ(visitedNodes[3], -15);
		EXPECT_EQ(visitedNodes[4],-17);
		EXPECT_EQ(visitedNodes[5], -37);
		EXPECT_EQ(visitedNodes[6],-50);

		nodeIndex = 0;
		aTree->preOrder(visitNode);
		EXPECT_EQ(visitedNodes[0],-17);
		EXPECT_EQ(visitedNodes[1], -15);
		EXPECT_EQ(visitedNodes[2],-11);
		EXPECT_EQ(visitedNodes[3], -9);
		EXPECT_EQ(visitedNodes[4],-13);
		EXPECT_EQ(visitedNodes[5], -50);
		EXPECT_EQ(visitedNodes[6],-37);

		aTree->add(13,36);
		nodeIndex = 0;
		aTree->preOrder(visitNode);
		EXPECT_EQ(visitedNodes[4],36);
		delete aTree;

}

TEST(BstTest, testIncludes){
	Bst<int,int> *aTree = new Bst<int,int>(new NullTreeNode<int,int>(nullptr));
	aTree->add(17, -17);
	aTree->add(15,-15);
	aTree->add(11,-11);
	aTree->add(9,-9);
	aTree->add(13,-13);
	aTree->add(50,-50);
	aTree->add(37,-37);

	EXPECT_TRUE(aTree->includes(17));
	EXPECT_TRUE(aTree->includes(37));
	EXPECT_TRUE(aTree->includes(11));
	EXPECT_FALSE(aTree->includes(42));
	EXPECT_FALSE(aTree->includes(100));
	EXPECT_FALSE(aTree->includes(-17));
	delete aTree;

}

TEST(BstTest, testRetrieve){
	Bst<int,int> *aTree = new Bst<int,int>(new NullTreeNode<int,int>(nullptr));
	aTree->add(17, -17);
	aTree->add(15,-15);
	aTree->add(11,-11);
	aTree->add(9,-9);
	aTree->add(13,-13);
	aTree->add(50,-50);
	aTree->add(37,-37);

	EXPECT_EQ(aTree->retrieve(17), -17);
	EXPECT_EQ(aTree->retrieve(37), -37);
	EXPECT_EQ(aTree->retrieve(11), -11);
//should throw exception if key not in tree
	delete aTree;
}

// Assumes that remove is using greatest lower bound for removal.
// Assumes that remove is using least upper bound for removal.
// One of the previous comments is true.
TEST(BstTest, testRemove){
	Bst<int,int> *aTree = new Bst<int,int>(new NullTreeNode<int,int>(nullptr));
	aTree->add(17, -17);
	aTree->add(15,-15);
	aTree->add(11,-11);
	aTree->add(9,-9);
	aTree->add(13,-13);
	aTree->add(50,-50);
	aTree->add(37,-37);

	aTree->remove(15);
	EXPECT_FALSE(aTree->includes(15));
	nodeIndex = 0;
	aTree->inOrder(visitNode);
	EXPECT_EQ(visitedNodes[0],-9);
	EXPECT_EQ(visitedNodes[1], -11);
	EXPECT_EQ(visitedNodes[2],-13);
	EXPECT_EQ(visitedNodes[3],-17);
	EXPECT_EQ(visitedNodes[4], -37);
	EXPECT_EQ(visitedNodes[5],-50);

	aTree->remove(17);
	nodeIndex = 0;
	aTree->inOrder(visitNode);
	EXPECT_EQ(visitedNodes[0],-9);
	EXPECT_EQ(visitedNodes[1], -11);
	EXPECT_EQ(visitedNodes[2],-13);
	EXPECT_EQ(visitedNodes[3], -37);
	EXPECT_EQ(visitedNodes[4],-50);
	
	nodeIndex = 0;
	aTree->postOrder(visitNode);
	EXPECT_EQ(visitedNodes[0],-9);
	EXPECT_EQ(visitedNodes[1], -13);
	EXPECT_EQ(visitedNodes[2],-11);
	EXPECT_EQ(visitedNodes[3], -50);
	EXPECT_EQ(visitedNodes[4],-37);


	aTree->remove(9);
	nodeIndex = 0;
	aTree->inOrder(visitNode);
	EXPECT_EQ(visitedNodes[0], -11);
	EXPECT_EQ(visitedNodes[1],-13);
	EXPECT_EQ(visitedNodes[2], -37);
	EXPECT_EQ(visitedNodes[3],-50);
	
	nodeIndex = 0;
	aTree->preOrder(visitNode);
	EXPECT_EQ(visitedNodes[0],-37);
	EXPECT_EQ(visitedNodes[1], -11);
	EXPECT_EQ(visitedNodes[2],-13);
	EXPECT_EQ(visitedNodes[3], -50);

}

TEST(BstTest, testRemoveSingleNode){
	Bst<int,int> *aTree = new Bst<int,int>(new NullTreeNode<int,int>(nullptr));
	aTree->add(17, -17);
	aTree->remove(17);
	EXPECT_TRUE(aTree->isEmpty());
	delete aTree;
}

TEST(BstTest, testRemoveRootWithOneChild){
	Bst<int,int> *aTree = new Bst<int,int>(new NullTreeNode<int,int>(nullptr));
	aTree->add(17, -17);
	aTree->add(15, -15);
	aTree->remove(17);
	nodeIndex = 0;
	aTree->inOrder(visitNode);
	EXPECT_EQ(nodeIndex, 1);
	EXPECT_EQ(visitedNodes[0], -15);
	delete aTree;
}

TEST(BstTest, testRemoveNonRootWithTwoChildren){
	Bst<int,int> *aTree = new Bst<int,int>(new NullTreeNode<int,int>(nullptr));
	aTree->add(12, -12);
	aTree->add(4, -4);
	aTree->add(17, -17);
	aTree->add(2, -2);
	aTree->add(7, -7);
	aTree->add(0, 0);
	aTree->add(3, -3);
	aTree->add(6, -6);
	aTree->add(9, -9);
	aTree->remove(4);
	nodeIndex = 0;
	aTree->inOrder(visitNode);

	EXPECT_EQ(visitedNodes[0], 0);
	EXPECT_EQ(visitedNodes[1], -2);
	EXPECT_EQ(visitedNodes[2], -3);
	EXPECT_EQ(visitedNodes[3], -6);
	EXPECT_EQ(visitedNodes[4], -7);
	EXPECT_EQ(visitedNodes[5], -9);
	EXPECT_EQ(visitedNodes[6], -12);
	EXPECT_EQ(visitedNodes[7], -17);
}
