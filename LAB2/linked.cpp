#include "linked.h"

LINKED_node* created_LINKED() {
	LINKED_node* HEAD = new LINKED_node;
	HEAD -> next = NULL;
	return HEAD;
}

void LINKED_Insert(LINKED_node* HEAD, LINKED_node* data_node) {
	LINKED_node* p, * q;
	p = HEAD->next;
	q = HEAD;
	while (p != NULL && p->index <= data_node->index) {
		q = p;
		p = p->next;
	}
	q->next = data_node;
	data_node->next = p;
}

void LINKED_Query(LINKED_node* HEAD, int* LINKED_Query) {
	LINKED_node* p;
	for (int i = 0; i < 10; i++) {
		p = HEAD->next;
		while (p != NULL) {
			if (p->index == LINKED_Query[i]) {
				cout << LINKED_Query[i] << ":" << p->mac << endl;
				break;
			}
			p = p->next;
		}
	}
}

void LINKED_Delete(LINKED_node* HEAD, int* LINKED_Delete) {
	LINKED_node* p, * q;
	for (int i = 0; i < 10; i++) {
		p = HEAD;
		q = p->next;
		while (q != NULL) {
			if (q->index == LINKED_Delete[i]) {
				cout << LINKED_Delete[i] << ":" << q->mac << endl;
				p->next = q->next;
				free(q);
			}
			p = p->next;
			q = p->next;
		}
	}
}