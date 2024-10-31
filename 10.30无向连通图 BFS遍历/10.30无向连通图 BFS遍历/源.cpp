#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Node {
	int data;
	Node* next;
	Node(int givenData) {
		this->data = givenData;
		next = nullptr;
	}
};

void Insert(Node*& head, int givenData) { //尾部插入
	Node* newNode =new Node(givenData);
	if (head == nullptr) {
		head = newNode;
	}
	else {
		Node* current = head;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = newNode;
	}
}

void BFS(Node* head, vector<bool>& visited, vector<int>& result,const vector<Node*>& vertexArr) {
	if (head == nullptr) {
		return;
	}
	queue<Node*> q;
	q.push(head);
	visited[head->data] = true;
	while (!q.empty()) {
		Node* current = q.front();
		q.pop();
		result.push_back(current->data);
		vector<int> neighbors;
		while (current->next != nullptr) {
			current = current->next;
			neighbors.push_back(current->data);
		}
		sort(neighbors.begin(), neighbors.end());
		for (int neighbor : neighbors) {
			if (!visited[neighbor]) {
				visited[neighbor] = true;
				q.push(vertexArr[neighbor]);
			}
		}
	}
}

int main() {
	int m;
	while (cin >> m) {
		for (int i = 0; i < m; i++) {
			int n, e, s;
			cin >> n >> e >> s;
			vector<Node*> vertexArr;
			for (int a = 0; a < n; a++) {
				vertexArr.push_back(new Node(a));
			}
			for (int a = 0; a < e; a++) {
				int startVertex, endVertex = 0;
				cin >> startVertex >> endVertex;
				Insert(vertexArr[startVertex], endVertex);
				Insert(vertexArr[endVertex], startVertex); //无向图需要双向连接
			}
			vector<bool> visited(n,false);
			vector<int> result;
			BFS(vertexArr[s], visited, result, vertexArr);
			for (int j = 0; j < result.size(); j++) {
				if (j != result.size() - 1) {
					cout << result[j] << " ";
				}
				else {
					cout << result[j];
				}
			}
			cout << endl;
		}
	}
	return 0;
}