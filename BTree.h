//Carlos Manoel Pedrosa de Oliveira TIA: 32068549
//Jones Santos Czinczel TIA:32089041
//Thayná Gomes da Silva TIA: 32092229

#ifndef __BTREE_H__
#define __BTREE_H__
 
#include "NodeBTree.h"

class BTree {
public:
	BTree();
	~BTree();

	NodeBTree* GetRoot() const;
	void SetRoot(NodeBTree* root);

	bool IsEmpty();

	NodeBTree* SearchKey(int key);
	void InsertKey(int key);
	void Remove(int key);
	void PrintInfo();

private:
	NodeBTree* m_Root;
	NodeBTree* SearchKeyInternal(NodeBTree* node, int key);
	void InsertKeyInternal(int key);
};

#endif