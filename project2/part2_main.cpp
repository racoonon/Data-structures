#include "PriorityQueue.hpp"
#include <iostream>

using namespace std;

int main() {
	static const int MAX_INSTRUCTIONS = 1000;

	int T;
	cin >> T;

	while (T > 0) { // test case ����
		Printer PT;
		int N; // �� test case�� ���� cmd ����
		cin >> N;

		for (int i = 0; i < N; i++) { // N���� cmd ����
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
				else {// empty �� �̹� empty queue���� print
					cout << PT.topDoc().getId() << " " << PT.topDoc().getTitle() << endl;
					PT.popDoc(); // print �� ������ pop
				}
			}

			else if (cmd == 'T') {
				if (PT.emptyPrinter()) {
					cout << "Empty queue." << endl;
				}
				else {// empty �� �̹� empty queue���� print
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
				PT.popDoc(); // root�� ������ ���� �����Ƿ� pop�ϰ� �ٽ� minheap �����
				M--;
			}
			cout << PT.topDoc().getId() << " " << PT.topDoc().getTitle() << endl;
		}

		T--;

	}
	return 0;
}