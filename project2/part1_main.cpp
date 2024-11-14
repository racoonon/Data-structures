#include "PriorityQueue.hpp"
#include <iostream>

using namespace std;

int main() {
	static const int MAX_INSTRUCTIONS = 1000;

	int d, N;
	cin >> d >> N;

	PriorityQueue pq(d);

	for (int i = 0; i < N; i++) { // N개의 cmd 실행
		char cmd;
		cin >> cmd;
		
		if (cmd == 'I') {
			int p; // priority
			cin >> p;
			pq.insertHeap(p);
		}

		else if (cmd == 'P') {
			int A = pq.topHeap(); // empty 시 이미 empty queue임을 print
			if (A != 0) {
				cout << A << endl;
				pq.popHeap(); } // print 후 실제로 pop
			 
		}

		else if (cmd == 'T') {
			int A = pq.topHeap();
			if (A != 0) cout << A << endl; // print 후 pop X
		}

		else if (cmd == 'S') {
			cout << pq.sizeHeap() << endl;
		}

		else if (cmd == 'E') {
			cout << pq.emptyHeap() << endl;
		}
	}

	return 0;
}