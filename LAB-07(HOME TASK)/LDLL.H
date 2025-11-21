#ifndef LDLL_H
#define LDLL_H

#include <iostream>
#include <stdexcept>
using namespace std;

// Doubly Linked List Node
template <class T>
class DNode {
public:
	T info;
	DNode<T>* prev;
	DNode<T>* next;

	DNode() : info(), prev(nullptr), next(nullptr) {}
	DNode(T val) : info(val), prev(nullptr), next(nullptr) {}
};

// Doubly Linked List
template <class T>
class LDLL {
private:
	DNode<T>* head;
	DNode<T>* tail;

	// helper for reverse display (kept for API parity with LSLL)
	void reverse_display_helper(DNode<T>* curr) {
		if (!curr) return;
		reverse_display_helper(curr->next);
		cout << curr->info << " ";
	}

public:
	LDLL() : head(nullptr), tail(nullptr) {}

	// ===========================
	// Insertion Functions
	// ===========================
	void insertAtHead(T val) {
		DNode<T>* newNode = new DNode<T>(val);
		newNode->next = head;
		newNode->prev = nullptr;
		if (head) head->prev = newNode;
		head = newNode;
		if (!tail) tail = newNode;
	}

	void insertAtTail(T val) {
		DNode<T>* newNode = new DNode<T>(val);
		newNode->next = nullptr;
		newNode->prev = tail;
		if (!tail) {
			head = tail = newNode;
		} else {
			tail->next = newNode;
			tail = newNode;
		}
	}

	void insertBefore(T key, T val) {
		if (!head) return;
		if (head->info == key) {
			insertAtHead(val);
			return;
		}
		DNode<T>* curr = head->next;
		while (curr && curr->info != key) curr = curr->next;
		if (curr) {
			DNode<T>* newNode = new DNode<T>(val);
			DNode<T>* p = curr->prev;
			newNode->prev = p;
			newNode->next = curr;
			p->next = newNode;
			curr->prev = newNode;
		}
	}

	void insertAfter(T key, T val) {
		DNode<T>* curr = head;
		while (curr && curr->info != key) curr = curr->next;
		if (curr) {
			if (curr == tail) {
				insertAtTail(val);
			} else {
				DNode<T>* newNode = new DNode<T>(val);
				newNode->next = curr->next;
				newNode->prev = curr;
				curr->next->prev = newNode;
				curr->next = newNode;
			}
		}
	}

	// ===========================
	// Deletion Functions
	// ===========================
	void removeAtHead() {
		if (!head) return;
		DNode<T>* temp = head;
		head = head->next;
		if (head) head->prev = nullptr;
		else tail = nullptr;
		delete temp;
	}

	void removeAtTail() {
		if (!tail) return;
		DNode<T>* temp = tail;
		tail = tail->prev;
		if (tail) tail->next = nullptr;
		else head = nullptr;
		delete temp;
	}

	void remove(T val) {
		if (!head) return;
		if (head->info == val) { removeAtHead(); return; }
		if (tail->info == val) { removeAtTail(); return; }
		DNode<T>* curr = head->next;
		while (curr && curr->info != val) curr = curr->next;
		if (curr) {
			DNode<T>* p = curr->prev;
			DNode<T>* n = curr->next;
			p->next = n;
			if (n) n->prev = p;
			delete curr;
		}
	}

	void removeBefore(T val) {
		if (!head || head->info == val) return;
		DNode<T>* curr = head->next;
		while (curr && curr->info != val) curr = curr->next;
		if (!curr) return;
		DNode<T>* target = curr->prev; // node to remove
		if (target == head) {
			removeAtHead();
		} else {
			DNode<T>* p = target->prev;
			p->next = curr;
			curr->prev = p;
			delete target;
		}
	}

	void removeAfter(T val) {
		DNode<T>* curr = head;
		while (curr && curr->info != val) curr = curr->next;
		if (!curr || !curr->next) return;
		DNode<T>* target = curr->next;
		if (target == tail) {
			removeAtTail();
		} else {
			curr->next = target->next;
			target->next->prev = curr;
			delete target;
		}
	}

	// ===========================
	// Utility Functions
	// ===========================
	int search(T key) {
		DNode<T>* curr = head;
		while (curr) {
			if (curr->info == key) return 1;
			curr = curr->next;
		}
		return 0;
	}

	void update(T key, T val) {
		DNode<T>* curr = head;
		while (curr) {
			if (curr->info == key) { curr->info = val; return; }
			curr = curr->next;
		}
	}

	int countNodes() {
		int cnt = 0;
		DNode<T>* curr = head;
		while (curr) { ++cnt; curr = curr->next; }
		return cnt;
	}

	void display() {
		DNode<T>* curr = head;
		while (curr) { cout << curr->info << " "; curr = curr->next; }
		cout << endl;
	}

	void reverse_display() {
		// parity with LSLL: use helper (recursive from head)
		reverse_display_helper(head);
		cout << endl;
	}

	// ===========================
	// Reverse Entire List
	// ===========================
	void reverseList() {
		DNode<T>* curr = head;
		while (curr) {
			// swap prev and next
			DNode<T>* tmp = curr->prev;
			curr->prev = curr->next;
			curr->next = tmp;
			curr = curr->prev; // moved to original next
		}
		// swap head and tail
		DNode<T>* tmp = head;
		head = tail;
		tail = tmp;
	}

	// ===========================
	// Find Middle Node
	// ===========================
	DNode<T>* getMiddleNode() {
		if (!head) return nullptr;
		DNode<T>* slow = head;
		DNode<T>* fast = head;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow;
	}

	// ===========================
	// Reverse from given node (helper for standalone chains)
	// Note: Not used internally; provided for API parity.
	// ===========================
	DNode<T>* reverseFrom(DNode<T>* start) {
		DNode<T>* curr = start;
		DNode<T>* last = nullptr;
		while (curr) {
			DNode<T>* nxt = curr->next;
			curr->next = curr->prev;
			curr->prev = nxt;
			last = curr;
			curr = nxt;
		}
		return last; // new head of this reversed chain
	}

	// ===========================
	// Palindrome Check (two-pointer, no mutation)
	// ===========================
	bool isPalindrome() {
		if (!head || !head->next) return true;
		DNode<T>* left = head;
		DNode<T>* right = tail;
		while (left && right && left != right && right->next != left) {
			if (left->info != right->info) return false;
			left = left->next;
			right = right->prev;
		}
		return true;
	}

	// ===========================
	// Additional APIs for parity with chaudry.cpp usage
	// ===========================
	// Return a NEW reversed list (caller owns pointer)
	LDLL<T>* reverselist() {
		LDLL<T>* res = new LDLL<T>();
		for (DNode<T>* curr = head; curr; curr = curr->next) {
			res->insertAtHead(curr->info);
		}
		return res;
	}

	// Remove K-th node (1-based)
	void removeKthNode(int k) {
		if (k <= 0 || !head) return;
		if (k == 1) { removeAtHead(); return; }
		DNode<T>* curr = head;
		int idx = 1;
		while (curr && idx < k) { curr = curr->next; ++idx; }
		if (!curr) return;
		if (curr == tail) { removeAtTail(); return; }
		DNode<T>* p = curr->prev;
		DNode<T>* n = curr->next;
		if (p) p->next = n;
		if (n) n->prev = p;
		delete curr;
	}

	// Unsorted duplicate removal convenience wrapper
	void removeDuplicates() { removeDuplicatesUnsorted(); }

	// Concatenate another list to this one; empties 'other'
	void merge(LDLL<T>& other) {
		if (!other.head) return;
		if (!head) {
			head = other.head;
			tail = other.tail;
		} else {
			tail->next = other.head;
			other.head->prev = tail;
			tail = other.tail;
		}
		other.head = other.tail = nullptr;
	}

	// Swap nodes by swapping their values
	void swapNodes(T val1, T val2) {
		if (val1 == val2) return;
		DNode<T>* n1 = head;
		DNode<T>* n2 = head;
		while (n1 && n1->info != val1) n1 = n1->next;
		while (n2 && n2->info != val2) n2 = n2->next;
		if (!n1 || !n2) return;
		T tmp = n1->info; n1->info = n2->info; n2->info = tmp;
	}

	// Simple bubble sort by data values
	void sort() {
		if (!head || !head->next) return;
		bool swapped;
		do {
			swapped = false;
			for (DNode<T>* i = head; i && i->next; i = i->next) {
				if (i->info > i->next->info) {
					T tmp = i->info; i->info = i->next->info; i->next->info = tmp;
					swapped = true;
				}
			}
		} while (swapped);
	}

	// Return middle element's value
	T findMiddle() {
		if (!head) throw std::runtime_error("List is empty");
		DNode<T>* mid = getMiddleNode();
		return mid->info;
	}

	// Accessor for tail pointer (used by some clients)
	DNode<T>* getTail() { return tail; }

	// ===========================
	// Remove Duplicates (Sorted)
	// ===========================
	void removeDuplicatesSorted() {
		if (!head) return;
		DNode<T>* curr = head;
		while (curr && curr->next) {
			if (curr->info == curr->next->info) {
				DNode<T>* dup = curr->next;
				curr->next = dup->next;
				if (dup->next) dup->next->prev = curr;
				else tail = curr;
				delete dup;
			} else {
				curr = curr->next;
			}
		}
	}

	// ===========================
	// Remove Duplicates (Unsorted)
	// ===========================
	void removeDuplicatesUnsorted() {
		if (!head) return;
		for (DNode<T>* curr = head; curr; curr = curr->next) {
			DNode<T>* runner = curr->next;
			while (runner) {
				if (runner->info == curr->info) {
					DNode<T>* toDelete = runner;
					runner = runner->next;
					// unlink toDelete
					if (toDelete->prev) toDelete->prev->next = toDelete->next;
					if (toDelete->next) toDelete->next->prev = toDelete->prev;
					if (toDelete == tail) tail = toDelete->prev;
					delete toDelete;
				} else {
					runner = runner->next;
				}
			}
		}
	}

	// ===========================
	// Merge Two Sorted Lists (Static)
	// ===========================
	static LDLL<T> mergeSortedLists(LDLL<T>& l1, LDLL<T>& l2) {
		LDLL<T> result;
		DNode<T>* p1 = l1.head;
		DNode<T>* p2 = l2.head;
		while (p1 && p2) {
			if (p1->info <= p2->info) { result.insertAtTail(p1->info); p1 = p1->next; }
			else { result.insertAtTail(p2->info); p2 = p2->next; }
		}
		while (p1) { result.insertAtTail(p1->info); p1 = p1->next; }
		while (p2) { result.insertAtTail(p2->info); p2 = p2->next; }
		return result;
	}

	// ===========================
	// Destructor
	// ===========================
	~LDLL() {
		while (head) removeAtHead();
	}
};

#endif

