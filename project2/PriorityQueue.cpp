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
    if (direction == 1) { // min heap일 때 
        while (pos > 0) {
            int parent_pos = (pos - 1) / 2;
            if (heap[pos] < heap[parent_pos]) {// parent보다 작으면 swap 
                swapPQ(pos, parent_pos);
                pos = parent_pos;
            }
            else break;
        }
    }
    else if (direction == -1) { // max heap일 때
        while (pos > 0) {
            int parent_pos = (pos - 1) / 2;
            if (heap[pos] > heap[parent_pos]) {// parent보다 크면 swap 
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
    if (direction == 1) { // min heap일 때
        while (pos < heap_size) {
            int left_pos = 2 * pos + 1;
            int right_pos = 2 * pos + 2;
            int current;
            if ((left_pos >= heap_size) && (right_pos >= heap_size)) break; // 두 자식 노드 index가 모두 범위 벗어나면 break;

            current = pos; // 현재 부모 노드를 cur에 저장
            if ((left_pos < heap_size) && (heap[current] > heap[left_pos]))
                current = left_pos;
            if ((right_pos < heap_size) && (heap[current] > heap[right_pos]))
                current = right_pos;
            // 왼쪽, 오른쪽 자식 중에 더 작은 값을 찾기

            if (current == pos) break;
            // 부모 노드가 자식보다 작은 상황일 때, pos는 변함없으므로 종료
            swapPQ(current, pos);
            pos = current;
        }
    }
    else if (direction == -1) { // max heap일 때
        while (pos < heap_size) {
            int left_pos = 2 * pos + 1;
            int right_pos = 2 * pos + 2;
            int current;
            if ((left_pos >= heap_size) && (right_pos >= heap_size)) break; // 두 자식 노드 index가 모두 범위 벗어나면 break;

            current = pos; // 현재 부모 노드를 cur에 저장
            if ((left_pos < heap_size) && (heap[current] < heap[left_pos]))
                pos = left_pos;
            if ((right_pos < heap_size) && (heap[current] < heap[right_pos]))
                pos = right_pos;
            // 왼쪽, 오른쪽 자식 중에 더 큰 값을 찾기

            if (current == pos) break;
            // 부모 노드가 자식보다 작은 상황일 때, pos는 변함없으므로 종료
            swapPQ(current, pos);
            pos = current;
        }
    }
}


void PriorityQueue::insertHeap(int e) { // Insert a new entry to the queue.
    // TO-DO
    heap.push_back(e); // 가장 마지막 node 추가
    heap_size += 1;
    upHeap(heap_size - 1);
}


int PriorityQueue::popHeap() {  // Pop its top entry. If the queue is empty, then print "Empty queue.".
    // TO-DO
    if (heap_size == 0) {
        std::cout << "Empty queue." << std::endl;
        return 0;
    }

    int ans = heap[0]; // root의 데이터 저장
    heap[0] = heap[heap_size - 1]; // 맨 마지막 node의 값을 root에 저장
    heap.pop_back(); // 맨 마지막 node 삭제
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
        if (docs[pos].getPriority() < docs[parent_pos].getPriority()) {// parent보다 작으면 swap 
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
        if ((left_pos >= heap_size) && (right_pos >= heap_size)) break; // 두 자식 노드 index가 모두 범위 벗어나면 break;

        current = pos; // 현재 부모 노드를 cur에 저장
        if ((left_pos < heap_size) && (docs[current].getPriority() > docs[left_pos].getPriority()))
            current = left_pos;
        if ((right_pos < heap_size) && (docs[current].getPriority() > docs[right_pos].getPriority()))
            current = right_pos;
        // 왼쪽, 오른쪽 자식 중에 더 작은 값을 찾기

        if (current == pos) break;
        // 부모 노드가 자식보다 작은 상황일 때, pos는 변함없으므로 종료
        swapDoc(current, pos);
        pos = current;
    }
}


void Printer::insertDoc(std::string id, std::string title, int priority) {  // Insert a new doc. (modifiable)
    // TO-DO
    Document new_doc(id, title, priority);
    docs.push_back(new_doc); // 가장 마지막 node 추가
    heap_size += 1;
    upHeap(heap_size - 1);
}


void Printer::popDoc() {    // Pop its top doc. (modifiable)
    // TO-DO
    if (emptyPrinter()) {
        return; // 어차피 사용 안함
    }

    docs[0] = docs[heap_size - 1]; // 맨 마지막 node의 값을 root에 저장
    docs.pop_back(); // 맨 마지막 node 삭제
    heap_size -= 1;
    downHeap(0);
}


Document Printer::topDoc() const {  // Returns the document with the highest priority.
    // TO-DO
    if (emptyPrinter()) {
        return Document("0", "0", 1); // 어차피 사용 안함
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
