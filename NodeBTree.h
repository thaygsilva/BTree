//Carlos Manoel Pedrosa de Oliveira TIA: 32068549
//Jones Santos Czinczel TIA:32089041
//Thayná Gomes da Silva TIA: 32092229

#ifndef __NODEBTREE_H__
#define __NODEBTREE_H__

# define ORDER 4

class NodeBTree {
public:
	NodeBTree();
	~NodeBTree(); 

	int* GetKey();
	void SetKey(int key, int i);

	NodeBTree* GetChild(int i);
	void SetChild(NodeBTree* child, int i);

	int GetCountKeys() const;

	bool IsLeaf();

	void InsertInArrayNonFull(int key);
	void SplitChild(int i, NodeBTree* node);
	void Traverse();

	void IncreaseCountKeys();
	void DecreaseCountKeys();

	void RemoveKey(int key);
	int FindKey(int key);
	void RemoveFromLeaf(int key);
	void RemoveFromNonLeaf(int key);

	void PrintNodeInfo();
private:
	int* m_keys;
	NodeBTree** m_Child;
	int m_countKeys;
	int GetPredecessor(int key);
	int GetSuccessor(int key);
	void Merge(int key);
	void Fill(int key);
	void BorrowFromPrev(int key);
	void BorrowFromNext(int key);

};

#endif

