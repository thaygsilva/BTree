//Carlos Manoel Pedrosa de Oliveira TIA: 32068549
//Jones Santos Czinczel TIA:32089041
//Thayná Gomes da Silva TIA: 32092229

#include "NodeBTree.h"
#include <iostream>

NodeBTree::NodeBTree()
	:m_countKeys(0)
{
	m_keys = new int[ORDER - 1];
	m_Child = new NodeBTree * [ORDER];
	for (int i = 0; i < ORDER; i++) {
		if (i < ORDER - 1) {
			m_keys[i] = 0;
		}
		m_Child[i] = nullptr;

	}
}

NodeBTree::~NodeBTree() {
	m_Child = nullptr;
}

int* NodeBTree::GetKey() {
	return m_keys;
}

void NodeBTree::SetKey(int key, int i) {
	m_keys[i] = key;
}

NodeBTree* NodeBTree::GetChild(int i) {
	return m_Child[i];
}

void NodeBTree::SetChild(NodeBTree* child, int i) {
	m_Child[i] = child;
}

int NodeBTree::GetCountKeys() const {
	return m_countKeys;
}

void NodeBTree::IncreaseCountKeys() {
	m_countKeys++;
}

void NodeBTree::DecreaseCountKeys() {
	m_countKeys--;
}

bool NodeBTree::IsLeaf() {
	return m_Child[0] == nullptr;
}

void NodeBTree::InsertInArrayNonFull(int key) {
	int i = this->GetCountKeys() - 1;
	if (IsLeaf()) {
		while (i >= 0 && GetKey()[i] > key) {
			SetKey(GetKey()[i], i + 1);
			i--;
		}

		SetKey(key, i + 1);
		IncreaseCountKeys();
	}

	else {
		while (i >= 0 && GetKey()[i] > key) {
			i--;
		}

		if (GetChild(i + 1)->GetCountKeys() == ORDER - 1) {
			SplitChild(i + 1, GetChild(i + 1));

			if (GetKey()[i + 1] < key) {
				i++;
			}
		}
		GetChild(i + 1)->InsertInArrayNonFull(key);
	}

}

void NodeBTree::SplitChild(int j, NodeBTree* node) {
	NodeBTree* temp = new NodeBTree();
	int t = ORDER / 2;
	temp->m_countKeys = t - 1;

	for (int i = 0; i < (t - 1); i++) {
		temp->SetKey(node->GetKey()[i + t], i);
	}

	if (node->IsLeaf() == false) {
		for (int i = 0; i < t; i++) {
			temp->SetChild(node->GetChild(i + t), i);
		}
	}

	node->m_countKeys = t - 1;

	for (int i = GetCountKeys(); i >= j + 1; i--) {
		SetChild(GetChild(i), i + 1);
	}

	SetChild(temp, j + 1);

	for (int i = GetCountKeys() - 1; i >= j; i--) {
		m_keys[i + 1] = m_keys[i];
	}

	m_keys[j] = node->GetKey()[t - 1];

	IncreaseCountKeys();
}

void NodeBTree::Traverse() {
	int i;
	for (i = 0; i < GetCountKeys(); i++) {
		if (IsLeaf() == false) {
			GetChild(i)->Traverse();
		}
		std::cout << " " << GetKey()[i];
	}

	if (IsLeaf() == false) {
		GetChild(i)->Traverse();
	}
}

void NodeBTree::RemoveKey(int key) {
	int keyFound = FindKey(key);

	if (keyFound < GetCountKeys() && GetKey()[keyFound] == key) {
		if (IsLeaf()) {
			RemoveFromLeaf(keyFound);
		}
		else {
			RemoveFromNonLeaf(keyFound);
		}
	}
	else {
		if (IsLeaf()) {
			std::cout << "A chave não existe." << std::endl;
			return;
		}
		bool flag = ((keyFound == GetCountKeys()) ? true : false);

		if (GetChild(keyFound)->GetCountKeys() < (ORDER/2))
			Fill(keyFound);

		if (flag && keyFound > GetCountKeys())
			GetChild(keyFound - 1)->RemoveKey(key);
		else
			GetChild(keyFound)->RemoveKey(key);
	}
	return;

}

int NodeBTree::FindKey(int key) {
	int idx = 0;
	while (idx < GetCountKeys() && GetKey()[idx] < key) {
		++idx;
	}

	return idx;
}

void NodeBTree::RemoveFromLeaf(int key) {
	for (int i = key + 1; i < GetCountKeys(); ++i) {
		SetKey(GetKey()[i], i - 1);
	}
	DecreaseCountKeys();
}

void NodeBTree::RemoveFromNonLeaf(int key) {
	int keyFound = GetKey()[key];


	if (GetChild(key)->GetCountKeys() >= (ORDER/2))
	{
		int predecessor = GetPredecessor(key); 
		SetKey(predecessor, key);
		GetChild(key)->RemoveKey(predecessor);
	}
	else if (GetChild(key+1)->GetCountKeys() >= (ORDER/2))
	{
		int successor = GetSuccessor(key);
		SetKey(successor, key);
		GetChild(key+1)->RemoveKey(successor);
	}

	else
	{
		Merge(key);
		GetChild(key)->RemoveKey(keyFound);
	}
	return;
}

int NodeBTree::GetPredecessor(int key) {
	NodeBTree* cur = GetChild(key);
	while (!cur->IsLeaf()) {
		cur = cur->GetChild(cur->GetCountKeys());
	}

	return cur->GetKey()[cur->GetCountKeys() - 1];
}

int NodeBTree::GetSuccessor(int key) {

	NodeBTree* cur = GetChild(key + 1);
	while (!cur->IsLeaf()) {
		cur = cur->GetChild(0);
	}

	return cur->GetKey()[0];
}

void NodeBTree::Merge(int key) {
	NodeBTree* child = GetChild(key);
	NodeBTree* sibling = GetChild(key + 1);

	child->SetKey(GetKey()[key], ((ORDER / 2) - 1));

	for (int i = 0; i < sibling->GetCountKeys(); ++i) {
		child->SetKey(sibling->GetKey()[i], (i + (ORDER / 2)));
	}

	if (!child->IsLeaf()) {
		for (int i = 0; i <= sibling->GetCountKeys(); ++i)
			child->SetChild(sibling->GetChild(i),i+(ORDER/2) );
	}

	for (int i = key + 1; i < GetCountKeys(); ++i) {
		SetKey(GetKey()[i], i - 1);
	}

	for (int i = key + 2; i <= GetCountKeys(); ++i) {
		SetChild(GetChild(i), i - 1);
	}

	child->m_countKeys += sibling->GetCountKeys() + 1;
	DecreaseCountKeys();

	delete(sibling);
}

void NodeBTree::Fill(int key) {
	if (key != 0 && GetChild(key - 1)->GetCountKeys() >= (ORDER/2)) BorrowFromPrev(key);

	else if (key != GetCountKeys() && GetChild(key + 1)->GetCountKeys() >= (ORDER / 2)) BorrowFromNext(key);

	else {
		if (key != GetCountKeys()) {
			Merge(key);
		}
		else {
			Merge(key - 1);
		}
	}
}

void NodeBTree::BorrowFromPrev(int key) {
	NodeBTree* child = GetChild(key);
	NodeBTree* sibling = GetChild(key - 1);

	for (int i = child->GetCountKeys() - 1; i >= 0; i--) child->SetKey(child->GetKey()[i], i + 1);

	if (!child->IsLeaf()) {
		for (int i = child->GetCountKeys(); i >= 0; --i) {
			child->SetChild(child->GetChild(i), i + 1);
		}
	}
	child->SetKey(GetKey()[key - 1], 0);

	if (!child->IsLeaf()) {
		child->SetChild(sibling->GetChild(sibling->GetCountKeys()), 0);
	}
	SetKey(sibling->GetKey()[sibling->GetCountKeys() - 1], key - 1);

	child->IncreaseCountKeys();
	sibling->DecreaseCountKeys();

	return;
}

void NodeBTree::BorrowFromNext(int key) {
	NodeBTree* child = GetChild(key);
	NodeBTree* sibling = GetChild(key + 1);

	if (!(child->IsLeaf()))
		child->SetChild(sibling->GetChild(0), child->GetCountKeys() + 1);

	SetKey(sibling->GetKey()[0], key);

	for (int i = 1; i < sibling->GetCountKeys(); ++i) {
		sibling->SetKey(sibling->GetKey()[i], i - 1);
	}

	if (!sibling->IsLeaf()) {
		for (int i = 1; i <= sibling->GetCountKeys(); ++i)
			sibling->SetChild(sibling->GetChild(i), i - 1);
	}

	child->IncreaseCountKeys();
	sibling->DecreaseCountKeys();

	return;
}

void NodeBTree::PrintNodeInfo() {
	std::cout << "\nINFORMAÇÕES DO NÓ: " << std::endl;
	std::cout << "Quantidade de chaves no nó:  " << GetCountKeys() << std::endl;
	std::cout << "Chaves no nó:  ";
	for (int i = 0; i < GetCountKeys(); i++) {
		std::cout << GetKey()[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "É folha?: ";
	if (IsLeaf()) {
		std::cout << "Sim." << std::endl;
	}
	else {
		std::cout << "Não." << std::endl;
	}
}

