#ifndef FSM_H
#define FSM_H
// #include <stdio.h>
#include <iostream>

typedef struct node {
	int size;
    bool status;
	struct node* next;
    struct node* previous;
} node_t;

typedef struct DLL {
	int count;		// count keeps track of how many items are in the DLL.
	int size;
	node_t* head;		// head points to the first node in our DLL.
    node_t * tail;          //tail points to the last node in our DLL.
} dll_t;


node_t* create_node(int data){
	node_t* node = new node_t;
	if (!node) return nullptr;
	node->size = data;
	node->next = nullptr;
	node->previous = nullptr;
	node->status = false;
	return node; 
}

dll_t* create_dll(int size){
	// Modify the body of this function as needed.
	dll_t* myDll = new dll_t;
	if (!myDll) return NULL;
	node_t* node = create_node(size);
	myDll->head = node;
	myDll->tail = node;
	myDll->count = 1;
	myDll->size = size;
	return myDll;
}

int dll_empty(dll_t* l){
	if (!l) return -1;
	if (!l->count)return 1;
	else return 0;
}

int dll_get(dll_t* l, int pos){
	if (!l) return -1;
	if (pos < 0 || pos > l->count) return 0;
	node_t* p = l->head;
	int i;
	for (i = 0; i < pos; i++) {
		p = p->next;
	}
	return p->size; 
}

int dll_push_front(dll_t* l, int item){
	if (!l)return -1;
	node_t* node = create_node(item);
	if(!node) return 0;
	if (l->size < item) return 0;
	if (!l->count) {
		l->head = node;
		l->tail = node;
		
	} else {
	l->head->previous = node;
	node->next = l->head;
	l->head = node;
	}
	l->count++;
	l->size -= item;
	return 1;
}

int dll_push_back(dll_t* l, int item){
	if (!l)return -1;
	node_t* node = create_node(item);
	if(!node) return 0;
	if (l->size < item) return 0;
	if (!l->count){
		l->head = node;
		l->tail = node;
	} else {
		l->tail->next = node;
		node->previous = l->tail;
		l->tail = node;
	}
	l->count++;
	l->size -= item;
	return 1;
}

int dll_pop_front(dll_t* t){
	if (!t)return -1;
	node_t* node = t->head;
	if (!node) return 0;
	if (t->count == 1) {
		t->head = NULL;
		t->tail = NULL;
	} else {
		t->head = t->head->next;
		t->head->previous = NULL;
		node->next = NULL;
	}
	t->count--;
	int node_item = node->size;
	t->size += node_item;
	return node_item; 
}


int dll_pop_back(dll_t* t){
	if (!t)return -1;
	node_t* node = t->tail;
	if (!node) return 0;
	if (t->count == 1) {
		t->head = NULL;
		t->tail = NULL;
	} else {
		t->tail = t->tail->previous;
		t->tail->next = NULL;
		node->previous = NULL;
	}
	t->count--;
	int node_item = node->size;
	t->size += node_item;
	return node_item; 
}

int dll_insert(dll_t* l, int pos, int item){
	if (!l) return -1;
	if(l->size < item) return -1;
	if (pos == l->count) {
		if (dll_push_back(l, item) == 1) return 1;
		else return 0;
	}
	if (pos == 0) {
		if (dll_push_front(l, item) == 1) return 1;
		else return 0;
	}
	if (pos < 0 || pos > l->count) return 0;
	node_t* node = create_node(item);
	if (!node) return 0;
	int i;
	node_t* pp = l->head;
	for (i = 1; i < pos; i++) {
		pp = pp->next;
	}
	node_t* np = pp->next;
	pp->next = node;
	node->previous = pp;
	node->next = np;
	np->previous = node;
	l->count++;
	l->size -= item;
	return 1; 
}


int dll_remove(dll_t* l, int pos){
	if (!l) return -1;
	if (pos < 0 || pos >= l->count) return 0;
	if (pos == 0) return dll_pop_front(l);
	if (pos == l->count-1) return dll_pop_back(l);
	node_t* pp = l->head;
	int i;
	for (i = 1; i < pos; i++) {
		pp = pp->next;
	}
	node_t* node = pp->next;
	node_t* np = node->next;
	pp->next = np;
	np->previous = pp;
	node->previous = NULL;
	node->next = NULL;
	int node_item = node->size;
	l->count--;
	l->size += node_item;
	return node_item;
}

int dll_size(dll_t* t){
	if (!t) return -1;
	return t->count; 
}

node_t* get_freelist(dll_t* l){
	node_t* dummy = new node_t;
	node_t* pp = new node_t; // previous pointer
	node_t* cp = new node_t; // current pointer
	node_t* p = l->head;
	while (p){
		if (p->status) p = p->next;
		else {
			dummy->next = p;
			pp = p;
			p = p->next;
			break;
		}
	}
	while (p) {
		if (p->status) p = p->next;
		else{
			pp->next = p;
			pp = p;
			p = p->next;
		}
	}
	return dummy->next;
}

// type can be B(best fit), W(worst fit), F(first fit)
int malloc(char type, int data_size, dll_t* l){
	node_t* p = l->head;
	int num = 0;
	if (type == 'F') {
		while (p) {
			if (data_size > p->size || p->status == true) {
				p = p->next;
				num++;
			}
			else {
				break; //travse part of chunks. the performance is fast
			}
		}
	} else if (type == 'B') {
		node_t* bp = new node_t;
		int bpos = -1;
		int min_gap = INT_MAX;
		// traverse all of chunks, proformance would be slow.
		while(p) {
			if (data_size > p->size || p->status == true) {
				p = p->next;
				num++;
			}
			else {
				int cur_gap = p->size - data_size;
				if (cur_gap < min_gap){
					min_gap = cur_gap;
					bp = p;
					bpos = num;
				}
				p = p->next;
				num++;
			}			
		}
		if(bpos != -1) {
			p = bp;
			num = bpos;
		}
	} else if (type == 'W') {
		node_t* wp = new node_t;
		int wpos = -1;
		int max_gap = INT_MIN;
		// traverse all of chunks, proformance would be slow.
		while(p) {
			if (data_size > p->size || p->status == true) {
				p = p->next;
				num++;
			}
			else {
				int cur_gap = p->size - data_size;
				if (cur_gap > max_gap){
					max_gap = cur_gap;
					wp = p;
					wpos = num;
				}
				p = p->next;
				num++;
			}			
		}
		if(wpos != -1) {
			p = wp;
			num = wpos;
		}
	}

	if (p) {
		node_t* pre = p->previous;
		node_t* next = p->next;
		node_t* task = create_node(data_size);
		task->status = true;
		node_t* space = create_node(p->size - data_size);
		task->next = space;
		space->previous = task;
		task->previous = task;
		l->size -= data_size;
		l->count += 1;

		if(pre) {
			pre->next = task;
			task->previous = pre;
		} else l->head = task;

		if(next) {
			space->next = next;
			next->previous = space;
		} else l->tail = space;
		printf("Malloc successfully in the NO.%d chunk! The task size is %d\n", num, data_size);
		return num;
	}

	printf("Malloc failed, there is not enough space!\n");
	return -1;
}

void print_freelist(node_t* p) {
	int n = 0;
	while (p) {
		printf("free space NO.%d, size: %d\n", n++, p->size);
		p = p->next;
	}
}

int free(dll_t* l, int pos){
	int num = 0;
	if (pos < num || pos >= l->count) {
		printf("Invalid free! Out of range!\n");
		return -1;
	}
	node_t* p = l->head;
	while (num != pos) {
		p = p->next;
		num++;
	}
	
	if (!p->status){
		printf("Invalid free! Nothing to free!\n");
		return -1;
	} else {
		p->status = false;
		l->size += p->size;
		printf("Free the NO.%d chunk successfully! Size is %d.\n", pos, p->size);
	}

	return pos;
}


#endif