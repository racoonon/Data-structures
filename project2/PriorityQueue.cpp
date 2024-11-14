#include "PriorityQueue.hpp"


// Part 1: Basic operations of priority queue (40 pts)
PriorityQueue::PriorityQueue(int dir) {   // Constructor.
    // TO-DO
    direction = dir;
    heap_size = 0;
}


PriorityQueue::~PriorityQueue() {   // Destructor.
    // TO-DO
}


void PriorityQueue::swapPQ(int idx1, int idx2) {    // Swaps the elements at the specified indices in the heap.
    // TO-DO
    int temp = heap[idx1];
    heap[idx1] = heap[idx2];
    heap[idx2] = temp;
}


void PriorityQueue::upHeap(int idx) {   // Adjust the heap by moving the specified element upwards.
    // TO-DO
    int pos = idx;
    if (direction == 1) { // min heap�� �� 
        while (pos > 0) {
            int parent_pos = (pos - 1) / 2;
            if (heap[pos] < heap[parent_pos]) {// parent���� ������ swap 
                swapPQ(pos, parent_pos);
                pos = parent_pos;
            }
            else break;
        }
    }
    else if (direction == -1) { // max heap�� ��
        while (pos > 0) {
            int parent_pos = (pos - 1) / 2;
            if (heap[pos] > heap[parent_pos]) {// parent���� ũ�� swap 
                swapPQ(pos, parent_pos);
                pos = parent_pos;
            }
            else break;
        }
    }
}


void PriorityQueue::downHeap(int idx) { // Adjust the heap by moving the specified element downwards.
    // TO-DO
    int pos = idx;
    if (direction == 1) { // min heap�� ��
        while (pos < heap_size) {
            int left_pos = 2 * pos + 1;
            int right_pos = 2 * pos + 2;
            int current;
            if ((left_pos >= heap_size) && (right_pos >= heap_size)) break; // �� �ڽ� ��� index�� ��� ���� ����� break;

            current = pos; // ���� �θ� ��带 cur�� ����
            if ((left_pos < heap_size) && (heap[current] > heap[left_pos]))
                current = left_pos;
            if ((right_pos < heap_size) && (heap[current] > heap[right_pos]))
                current = right_pos;
            // ����, ������ �ڽ� �߿� �� ���� ���� ã��

            if (current == pos) break;
            // �θ� ��尡 �ڽĺ��� ���� ��Ȳ�� ��, pos�� ���Ծ����Ƿ� ����
            swapPQ(current, pos);
            pos = current;
        }
    }
    else if (direction == -1) { // max heap�� ��
        while (pos < heap_size) {
            int left_pos = 2 * pos + 1;
            int right_pos = 2 * pos + 2;
            int current;
            if ((left_pos >= heap_size) && (right_pos >= heap_size)) break; // �� �ڽ� ��� index�� ��� ���� ����� break;

            current = pos; // ���� �θ� ��带 cur�� ����
            if ((left_pos < heap_size) && (heap[current] < heap[left_pos]))
                pos = left_pos;
            if ((right_pos < heap_size) && (heap[current] < heap[right_pos]))
                pos = right_pos;
            // ����, ������ �ڽ� �߿� �� ū ���� ã��

            if (current == pos) break;
            // �θ� ��尡 �ڽĺ��� ���� ��Ȳ�� ��, pos�� ���Ծ����Ƿ� ����
            swapPQ(current, pos);
            pos = current;
        }
    }
}


void PriorityQueue::insertHeap(int e) { // Insert a new entry to the queue.
    // TO-DO
    heap.push_back(e); // ���� ������ node �߰�
    heap_size += 1;
    upHeap(heap_size - 1);
}


int PriorityQueue::popHeap() {  // Pop its top entry. If the queue is empty, then print "Empty queue.".
    // TO-DO
    if (heap_size == 0) {
        std::cout << "Empty queue." << std::endl;
        return 0;
    }

    int ans = heap[0]; // root�� ������ ����
    heap[0] = heap[heap_size - 1]; // �� ������ node�� ���� root�� ����
    heap.pop_back(); // �� ������ node ����
    heap_size -= 1;
    downHeap(0);
    return ans;
}


int PriorityQueue::topHeap() const {    // Return its top entry. If the queue is empty, then print "Empty queue.".
    // TO-DO
    if (emptyHeap()) {
        std::cout << "Empty queue." << std::endl;
        return 0;
    }

    return heap[0];
}


int PriorityQueue::sizeHeap() const {   // Return size of queue.
    // TO-DO
    return heap_size;
}


bool PriorityQueue::emptyHeap() const { // Check if the queue is empty. `1` for empty queue.
    // TO-DO
    return heap.empty();
}



// Part 2: Document printer implementation with priority queue (60 pts)
Document::Document(std::string ID, std::string TITLE, int PRIORITY) {   // Constructor.
    // TO-DO
    id = ID;
    title = TITLE;
    priority = PRIORITY;
}


std::string Document::getId() const {   // Getter.
    // TO-DO
    return id;
}


std::string Document::getTitle() const {    // Getter.
    // TO-DO
    return title;
}


int Document::getPriority() const { // Getter.
    // TO-DO
    return priority;
}


Printer::Printer() {    // Constructor.
    // TO-DO
    heap_size = 0;
}


Printer::~Printer() {   // Destructor.
    // TO-DO
}


void Printer::swapDoc(int idx1, int idx2) { // Swaps the elements at the specified indices in the printer.
    // TO-DO
    Document temp = docs[idx1];
    docs[idx1] = docs[idx2];
    docs[idx2] = temp;
}


void Printer::upHeap(int idx) { // Adjust the heap by moving the specified element upwards.
    // TO-DO
    int pos = idx;
    while (pos > 0) {
        int parent_pos = (pos - 1) / 2;
        if (docs[pos].getPriority() < docs[parent_pos].getPriority()) {// parent���� ������ swap 
            swapDoc(pos, parent_pos);
            pos = parent_pos;
        }
        else break;
    }
}


void Printer::downHeap(int idx) {   // Adjust the heap by moving the specified element downwards.
    // TO-DO
    int pos = idx;
    while (pos < heap_size) {
        int left_pos = 2 * pos + 1;
        int right_pos = 2 * pos + 2;
        int current;
        if ((left_pos >= heap_size) && (right_pos >= heap_size)) break; // �� �ڽ� ��� index�� ��� ���� ����� break;

        current = pos; // ���� �θ� ��带 cur�� ����
        if ((left_pos < heap_size) && (docs[current].getPriority() > docs[left_pos].getPriority()))
            current = left_pos;
        if ((right_pos < heap_size) && (docs[current].getPriority() > docs[right_pos].getPriority()))
            current = right_pos;
        // ����, ������ �ڽ� �߿� �� ���� ���� ã��

        if (current == pos) break;
        // �θ� ��尡 �ڽĺ��� ���� ��Ȳ�� ��, pos�� ���Ծ����Ƿ� ����
        swapDoc(current, pos);
        pos = current;
    }
}


void Printer::insertDoc(std::string id, std::string title, int priority) {  // Insert a new doc. (modifiable)
    // TO-DO
    Document new_doc(id, title, priority);
    docs.push_back(new_doc); // ���� ������ node �߰�
    heap_size += 1;
    upHeap(heap_size - 1);
}


void Printer::popDoc() {    // Pop its top doc. (modifiable)
    // TO-DO
    if (emptyPrinter()) {
        return; // ������ ��� ����
    }

    docs[0] = docs[heap_size - 1]; // �� ������ node�� ���� root�� ����
    docs.pop_back(); // �� ������ node ����
    heap_size -= 1;
    downHeap(0);
}


Document Printer::topDoc() const {  // Returns the document with the highest priority.
    // TO-DO
    if (emptyPrinter()) {
        return Document("0", "0", 1); // ������ ��� ����
    }

    return docs[0];
}

int Printer::sizePrinter() const {  // Returns the size of the queue.
    // TO-DO
    return heap_size;
}


bool Printer::emptyPrinter() const {    // Check if the queue is empty. `1` for empty queue.
    // TO-DO
    return docs.empty();
}
