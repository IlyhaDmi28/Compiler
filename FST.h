#pragma once
#include <stack>
#include <vector>

namespace FST {
	struct Relation
	{
		char tSymbol;
		short nNode;

		Relation() : tSymbol(' '), nNode(-1) { }

		Relation(char tSymbol, short nNode) : tSymbol(tSymbol), nNode(nNode) { }
	};

	struct Node
	{
		short reletion_count;
		Relation* relations;

		Node() : reletion_count(0), relations(nullptr) { }

		Node(short reletion_count, Relation relation, ...);
	};

	struct FST
	{
		char* string;

		short position;
		short states_count;

		Node* nodes;

		short* maybe_states;

		FST(char* string, short states_count, Node node, ...);
	};

	bool Execute(FST& fst);

	template <typename T>
	bool Constain(std::vector<T> vec, T item) {
		for (int i = 0; i < vec.size(); i++)
		{
			if (vec[i] == item) return true;
		}

		return false;
	}
}
