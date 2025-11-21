void merge(CDLL<T>& l1,CDLL<T>& l2) {
        if (!l1.head) return;
        if (!l2.head) { 
            l2.head = l1.head; 
            l2.tail = l1.tail; 
            l1.head = l1.tail = nullptr; 
            return; }

        tail->next = l1.head;
        l1.head->prev = l2.tail;
        l1.tail->next = l2.head;
        head->prev = l1.tail;
        l2.tail = l1.tail;
        l1.head = l1.tail = nullptr;
    }



    CDLL<T> mergeSortedLists(CDLL<T>& l1, CDLL<T>& l2) {
        CDLL<T> res;
        int n1 = l1.countNodes();
        int n2 = l2.countNodes();
        CDNode<T>* p1 = l1.head;
        CDNode<T>* p2 = l2.head;
        int i1 = 0, i2 = 0;
        while ((p1 && i1 < n1) || (p2 && i2 < n2)) {
            if (p2 == nullptr || i2 >= n2 || (p1 && i1 < n1 && p1->info <= p2->info)) {
                res.insertAtTail(p1->info); p1 = p1->next; ++i1;
            } else {
                res.insertAtTail(p2->info); p2 = p2->next; ++i2;
            }
        }
        return res;
    }