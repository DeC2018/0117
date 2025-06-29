#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}
    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    Node* connect(Node* root) {
        if (root == NULL) return NULL;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int count = q.size();
            Node* temp = NULL;

            for (int i = 0; i < count; i++) {
                Node* curr = q.front();
                q.pop();

                if (temp != NULL) temp->next = curr;
                temp = curr;

                if (curr->left != NULL) q.push(curr->left);
                if (curr->right != NULL) q.push(curr->right);
            }
        }

        return root;
    }

    vector<string> serialize(Node* root) {
        vector<string> result;
        if (root == NULL) return result;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int count = q.size();
            vector<string> level;

            for (int i = 0; i < count; i++) {
                Node* curr = q.front();
                q.pop();
                level.push_back(to_string(curr->val)); // Convert integer to string

                if (curr->left != NULL) q.push(curr->left);
                if (curr->right != NULL) q.push(curr->right);
            }

            result.insert(result.end(), level.begin(), level.end());
            result.push_back("#");
        }

        return result;
    }
};

int main() {
    Solution solution;

    // Example 1
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->left->right = new Node(5);
    root1->right->right = new Node(7);

    Node* connectedRoot1 = solution.connect(root1);
    vector<string> output1 = solution.serialize(connectedRoot1);

    cout << "Input: root = [1,2,3,4,5,null,7]" << endl;
    cout << "Output: [";
    for (size_t i = 0; i < output1.size(); ++i) {
        cout << output1[i];
        if (i != output1.size() - 1) {
            cout << ",";
        }
    }
    cout << "]" << endl;

    // Example 2
    Node* root2 = NULL;
    Node* connectedRoot2 = solution.connect(root2);
    vector<string> output2 = solution.serialize(connectedRoot2);

    cout << "Input: root = []" << endl;
    cout << "Output: [";
    for (size_t i = 0; i < output2.size(); ++i) {
        cout << output2[i];
        if (i != output2.size() - 1) {
            cout << ",";
        }
    }
    cout << "]" << endl;

    return 0;
}
