//Carlos Manoel Pedrosa de Oliveira TIA: 32068549
//Jones Santos Czinczel TIA:32089041
//Thayná Gomes da Silva TIA: 32092229

#include "BTree.h"
#include <iostream>

BTree::BTree()
	:m_Root(nullptr)
{
}

BTree::~BTree() {

}

NodeBTree* BTree::GetRoot() const {
	return m_Root;
}

void BTree::SetRoot(NodeBTree* root) {
	m_Root = root;
}

bool BTree::IsEmpty() {
	if (m_Root != nullptr) {
		return false;
	}
	return true;
}

NodeBTree* BTree::SearchKey(int key) {
	return SearchKeyInternal(m_Root, key);
}

NodeBTree* BTree::SearchKeyInternal(NodeBTree* node, int key) {
	int i = 0;
	while (i < node->GetCountKeys() && key > node->GetKey()[i]) {
		i++;
	}

	if (node->GetKey()[i] == key) {
		return node;
	}

	if (node->IsLeaf()) {
		std::cout << "\nChave não encontrada!" << std::endl;
		return nullptr;
	}

	return SearchKeyInternal(node->GetChild(i), key);

}

void BTree::InsertKey(int key) {
	InsertKeyInternal(key);
}

void BTree::InsertKeyInternal(int key) {
	int t = int(ORDER / 2);
	if (IsEmpty()) {
		m_Root = new NodeBTree();
		m_Root->SetKey(key, 0);
		m_Root->IncreaseCountKeys();
		return;
	}

	else {
		if (m_Root->GetCountKeys() == (2 * t - 1)) {
			NodeBTree* temp = new NodeBTree();

			temp->SetChild(m_Root, 0);
			temp->SplitChild(0, m_Root);

			int i = 0;
			if (temp->GetKey()[0] < key) {
				i++;
			}
			temp->GetChild(i)->InsertInArrayNonFull(key);
			SetRoot(temp);

		}
		else {
			m_Root->InsertInArrayNonFull(key);

		}

	}

}
 
void BTree::Remove(int key) {
	if (IsEmpty()) {
		std::cout << "Árvore vazia, não há nada para remover." << std::endl;
	}

	GetRoot()->RemoveKey(key);

	if (GetRoot()->GetCountKeys() == 0) {
		NodeBTree* temp = m_Root;
		if (GetRoot()->IsLeaf()) {
			SetRoot(nullptr);
		}
		else {
			SetRoot(GetRoot()->GetChild(0));
		}

		delete temp;
	}
}

void BTree::PrintInfo() {
	std::cout << "Root: ";
	for (int i = 0; i < GetRoot()->GetCountKeys(); i++) {
		std::cout << GetRoot()->GetKey()[i] << " ";
	}
	std::cout << "\n";

	std::cout << "Percorrendo a árvore em ordem: ";
	GetRoot()->Traverse();
}

