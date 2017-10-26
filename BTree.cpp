#include <iostream>
#include <vector>

#define MAXSZ 4

using namespace std;

class TempNode;

class BNode {
    std::vector<int> n;
    std::vector<BNode*> ptrs;
    BNode* parent;

public:
    BNode() {
        parent = nullptr;
    }
    BNode(const vector<int>& n_, const vector<BNode*> ptr) : n(n_), ptrs(ptr) {}
    BNode(int i, BNode* l , BNode* r) {
        n.push_back(i);
        ptrs.push_back(l);
        ptrs.push_back(r);
    }

    BNode* find(int);
    bool contains(int x) {
        for (int i = 0; i < n.size(); i++) {
            if(x == n[i])
                return true;
        }
        return false;
    }
    TempNode* insert(int);
    TempNode* add(int x, BNode* l = nullptr, BNode* r = nullptr);
    TempNode* split();
    BNode* getParent() {
        return parent;
    }

    void addParent(BNode* b) {
        parent = b;
    }

    int getMax();
    void print() {
        for(int i = 0; i < n.size(); i++)
            cout << n[i] << " ";
        cout << "\n";

        for (int i = 0; i < ptrs.size(); i++) {
            ptrs[i]->print();
        }
    }
};

struct TempNode {
    int val;
    BNode* left, *right;
};

TempNode* BNode::split() {
    TempNode* tn = new TempNode();
    if (ptrs.size()) {
        tn->left = new BNode(vector<int>(n.begin(), n.begin() + n.size()/2),
                             vector<BNode*>(ptrs.begin(), ptrs.begin() + n.size()/2));
        tn->right = new BNode(vector<int>(n.begin() + n.size()/2 + 1, n.end()),
                              vector<BNode*>(ptrs.begin() + n.size()/2 + 1, ptrs.end()));
    } else {
        tn->left = new BNode(vector<int>(n.begin(), n.begin() + n.size()/2),
                             vector<BNode*>(ptrs));
        tn->right = new BNode(vector<int>(n.begin() + n.size()/2 + 1, n.end()),
                              vector<BNode*>(ptrs));
    }

    tn->val = n[n.size()/2];
    return tn;
}

BNode* BNode::find(int x) {
    int i;
    if (ptrs.size() == 0)
        return this;

    for (i = 0; i < n.size(); i++) {
        if (n[i] == x)
            return this;
        else if (n[i] > x)
            break;
    }

    return ptrs[i]->find(x);
}

TempNode* BNode::add(int x, BNode* l, BNode* r) {
    int i;
    for (i = 0; i < n.size(); i++) {
        if (n[i] == x)
            return nullptr;
        else if(n[i] > x)
            break;
    }

    n.insert(n.begin()+i, x);
    if (l && r) {
        l->addParent(this);
        r->addParent(this);
        ptrs[i] = l;
        ptrs.insert(ptrs.begin() + i + 1, r);
    }

    if (n.size() > MAXSZ)
        return split();

    return nullptr;
}

TempNode* BNode::insert(int x) {
    BNode* bn = find(x);
    TempNode* tn = bn->add(x);
    while (tn && bn->getParent()) {
        tn = bn->getParent()->add(tn->val, tn->left, tn->right);
        bn = bn->getParent();
    }
    return tn;
}


class BTree {
    BNode* root;
public:
    BTree() {
        root = new BNode();
    }
    bool search(int);
    void insert(int);
    void print() { root->print(); }
};

bool BTree::search(int x) {
    return root->find(x)->contains(x);
}


void BTree::insert(int x) {
    TempNode* newNd = root->insert(x);
    if (newNd) {
        root = new BNode(newNd->val, newNd->left, newNd->right);
        newNd->left->addParent(root);
        newNd->right->addParent(root);
    }
}

int main(int argc, char const *argv[]) {

    int op = 1;
    BTree btree;

    int ele;

    while(op < 4) {
        cout << "1.Insert 2.Search 3.Print\n";
        cin >> op;
        switch (op) {
            case 1:
                cout << "Enter the elemet to be inserted : ";
                cin >> ele;
                btree.insert(ele);
                break;
            case 2:
                cout << "Enter the element to be searched : ";
                cin >> ele;
                if (btree.search(ele)) {
                    cout << "Found \n";
                } else {
                    cout << "Not found \n";
                }
                break;
            case 3:
                btree.print();
                break;
        }
    }
}
