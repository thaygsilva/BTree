//Carlos Manoel Pedrosa de Oliveira TIA: 32068549
//Jones Santos Czinczel TIA:32089041
//Thayná Gomes da Silva TIA: 32092229

#include "BTree.h"
#include <iostream> 


int main() {

	setlocale(LC_ALL, "Portuguese");
	BTree* Groot = new BTree();

	std::cout << "Inserindo as chaves 3, 16, 2, 5, 1, 12. (Nessa ordem):" << std::endl;

	Groot->InsertKey(3);

	Groot->InsertKey(16);

	Groot->InsertKey(2);

	Groot->InsertKey(5);

	Groot->InsertKey(1);

	Groot->InsertKey(12);

	Groot->PrintInfo();
	std::cout << "\n---------------------------------------------\n" << std::endl;

	std::cout << "Inserindo a chave 99: " << std::endl;

	Groot->InsertKey(99);

	Groot->PrintInfo();

	std::cout << "\n---------------------------------------------\n" << std::endl;
	
	std::cout << "REMOVENDO A CHAVE 5: " << std::endl;

	Groot->Remove(5);

	Groot->PrintInfo();

	std::cout << "\n---------------------------------------------\n" << std::endl;

	std::cout << "REMOVENDO A CHAVE 2: " << std::endl;

	Groot->Remove(2);

	Groot->PrintInfo();

	std::cout << "\n---------------------------------------------\n" << std::endl;

	std::cout << "Buscando a chave 99:" << std::endl;
	Groot->SearchKey(99)->PrintNodeInfo();

	std::cout << "\n---------------------------------------------\n" << std::endl;

	std::cout << "Buscando a chave 1:" << std::endl;
	Groot->SearchKey(1)->PrintNodeInfo();

	std::cout << "\n---------------------------------------------\n" << std::endl;

	std::cout << "Buscando a chave 12:" << std::endl;
	Groot->SearchKey(12)->PrintNodeInfo();
}

/*
MATERIAIS DE REFERÊNCIA:
https://www.geeksforgeeks.org/introduction-of-b-tree-2/

https://www.geeksforgeeks.org/insert-operation-in-b-tree/

https://www.geeksforgeeks.org/delete-operation-in-b-tree/

https://www.programiz.com/dsa/deletion-from-a-b-tree

Material do Prof. Jean para entender a parte teórica.

*/

