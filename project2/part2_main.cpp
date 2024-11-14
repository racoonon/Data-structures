#include "PriorityQueue.hpp"
#include <iostream>

using namespace std;

int main() {
	static const int MAX_INSTRUCTIONS = 1000;

	int T;
	cin >> T;

	while (T > 0) { // test case 개수
		Printer PT;
		int N; // 각 test case에 대한 cmd 개수
		cin >> N;

		for (int i = 0; i < N; i++) { // N개의 cmd 실행
			char cmd;
			cin >> cmd;

			if (cmd == 'I') {
				string id, title;
				int p;
				cin >> id >> title >> p;
				PT.insertDoc(id, title, p);
			}

			else if (cmd == 'P') {
				if (PT.emptyPrinter()) {
					cout << "Empty queue." << endl;
				}
				else {// empty 시 이미 empty queue임을 print
					cout << PT.topDoc().getId() << " " << PT.topDoc().getTitle() << endl;
					PT.popDoc(); // print 후 실제로 pop
				}
			}

			else if (cmd == 'T') {
				if (PT.emptyPrinter()) {
					cout << "Empty queue." << endl;
				}
				else {// empty 시 이미 empty queue임을 print
					cout << PT.topDoc().getId() << " " << PT.topDoc().getTitle() << endl;
				}
			}

			else if (cmd == 'S') {
				cout << PT.sizePrinter() << endl;
			}

			else if (cmd == 'E') {
				cout << PT.emptyPrinter() << endl;
			}
		}
		
		// Mth document print
		int M;
		cin >> M;
		if (M > PT.sizePrinter()) { cout << "M > printer.size()" << endl; }
		else {
			while (M > 1) {
				PT.popDoc(); // root는 무조건 가장 작으므로 pop하고 다시 minheap 만들기
				M--;
			}
			cout << PT.topDoc().getId() << " " << PT.topDoc().getTitle() << endl;
		}

		T--;

	}
	return 0;
}