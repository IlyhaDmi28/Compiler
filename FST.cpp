#include "FST.h"

namespace FST {
	Node::Node(short reletion_count, Relation relation, ...) {
		this->reletion_count = reletion_count;

		relations = new Relation[reletion_count];
		for (short i = 0; i < reletion_count; i++) {
			relations[i].nNode = (&relation + i)->nNode;
			relations[i].tSymbol = (&relation + i)->tSymbol;
		}
	}

	FST::FST(char* string, short states_count, Node node, ...)
	{
		this->string = string;
		this->states_count = states_count;

		nodes = new Node[states_count];
		for (short i = 0; i < states_count; i++)
		{
			nodes[i].relations = (&node + i)->relations;
			nodes[i].reletion_count = (&node + i)->reletion_count;
		}

		position = 0;

		maybe_states = new short[states_count];

		for (short i = 0; i < states_count; i++) maybe_states[i] = 0;
	}

	bool Execute(FST& fst)
	{
		std::stack<Node> State_stack;				// ���� ���������
		std::vector<Relation*> Checked_relations;	// ������ ����������� ���������

		Node Current;					// �������������� ������

		short string_offset,			// ������ �� ������ (��� ��������� ����������)
			current_state_index,		// ������ ��������������� ���������
			next_state_index,			// ������ ���������� ��������� ��� ���������
			global_state_index = 0;	    // ������ ��������� �� �������� ��� ���������

		bool Fall_Flag,					// ���� ������������ ��� ����� �� ���� ������ � ������� (���������� string_offset � next_state_index)
			HaveTranslate_Flag,			// ���� ������������ ������� �� ��������� ��������
			LambdaReached_Flag = false,	// ���� ������������ �������� �� �� ������
			TranslateConfirmed_Flag;	// ���� �������������� ������� ��������

		// ����� ������ 
		for (; fst.string[fst.position] != '\0'; fst.position++)
		{
			State_stack = std::stack<Node>();
			State_stack.push(fst.nodes[global_state_index]);

			Checked_relations = std::vector<Relation*>();

			next_state_index = global_state_index;
			string_offset = 0;
			HaveTranslate_Flag = false;

			// ��������� ���������
			while (!State_stack.empty())
			{
				current_state_index = next_state_index;

				Fall_Flag = false;

				Current = State_stack.top();

				// ���� ��� ������ ��������� �� � ���� ������� �������
				TranslateConfirmed_Flag = (current_state_index == global_state_index ? true : false);

				// ���� �� ����� �� ������ ��� ������ �������
				if (fst.string[fst.position + string_offset] == '\0') {
					fst.maybe_states[fst.states_count - 1]++;

					if (!LambdaReached_Flag && current_state_index == fst.states_count - 1)
						LambdaReached_Flag = true;

					break;
				}

				// �������� ���������
				for (int i = 0; i < Current.reletion_count; i++)
				{
					// ���� �� ����� ������� � ������ ��������
					// � ������� ������� �������� ��� � ���� ����������� ���������
					if (Current.relations[i].tSymbol == fst.string[fst.position + string_offset] &&
						!Constain(Checked_relations, &Current.relations[i])) {

						HaveTranslate_Flag = true;

						// ���� �� ���� ����� ���������� �� ��������� � ����� �������
						if (Current.relations[i].nNode != current_state_index) {

							// ���� ������� �� ����������
							if (!TranslateConfirmed_Flag) {
								fst.maybe_states[current_state_index]++;

								TranslateConfirmed_Flag = true;
							}

							next_state_index = Current.relations[i].nNode;

							Fall_Flag = true;
							string_offset++;

							State_stack.push(fst.nodes[Current.relations[i].nNode]);
						}
						// ���� �������
						else {
							fst.maybe_states[current_state_index]++;

							global_state_index = current_state_index;

							TranslateConfirmed_Flag = true;
						}

						Checked_relations.push_back(&Current.relations[i]);
					}
				}

				// ���� �� ����� ��������� ��������� ���������
				if (!Fall_Flag) {
					next_state_index--;
					string_offset--;

					State_stack.pop();
				}
			}

			// ���� �� �� ����� ������ ����� �� ����� ������ ����������
			// �� ��� ������ ��� ������� ���� �� �� �������� ������
			if (!HaveTranslate_Flag && !LambdaReached_Flag) return false;
		}

		return LambdaReached_Flag;
	}
}