void shufflemerge (LSLL& list1, LSLL& list2)
    {
        if (!list1.head) {
            head = list2.head;
            return;
        }
        if (!list2.head) {
            head = list1.head;
            return;
        }
        Node<T>* temp1 = list1.head;
        Node<T>* temp2 = list2.head;
        head = new Node<T>(temp1->info);
        Node<T>* temp3 = head;
        temp1 = temp1->next;
        int i = 2;

        while (temp1 || temp2) {
            if (i % 2 == 0) {
                temp3->next = new Node<T>(temp1->info);
                temp3 = temp3->next;
                temp1 = temp1->next;
            } else if (temp2) {
                temp3->next = new Node<T>(temp2->info);
                temp3 = temp3->next;
                temp2 = temp2->next;
            }
            i++;
        }
        temp3->next = nullptr;

        list1.head = nullptr;
        list2.head = nullptr;
    }

void shufflemerge (LSLL& list1, LSLL& list2)
    {
        Node<T> *temp1 = list1.head;
        Node<T> *temp2 = list2.head;
        if(!(temp1))
        {
            head=list2.head;
            list2.head=nullptr;
            return;
        }
        if(!(temp2))
        {
            head=list1.head;
            list1.head=nullptr;
            return;
        }
        Node<T>* tail = nullptr;
        while(temp1!=nullptr && temp2!=nullptr)
        {
            if(!head)
            {
                head = temp1;
                tail = head;
                temp1 = temp1->next;
                tail->next = nullptr;
            }
            else
            {
                tail->next = temp1;
                tail = tail->next;
                temp1 = temp1->next;
                tail->next = nullptr;
            }
            if(!head)
            {
                head = temp2;
                tail = head;
                temp2 = temp2->next;
                tail->next = nullptr;
            }
            else
            {
                tail->next = temp2;
                tail = tail->next;
                temp2 = temp2->next;
                tail->next = nullptr;
            }
        }
        list1.head = nullptr;
        list2.head = nullptr;
    }
