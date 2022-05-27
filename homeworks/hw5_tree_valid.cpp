#include<iostream>
#include<string>
#include<unordered_map>

/*
 * Complete the 'sExpression' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING nodes as parameter.
 */

class Node
{
public:
    Node(){}
    char val{};
    int nchild{0};
    Node* parent{nullptr}, * left{nullptr}, * right{nullptr};

    std::string repr()
    {
        // std::cout << "Node repr()\n";
        std::string s;
        s.append(1, '(');
        s.append(1, val);
        s.append((left !=nullptr) ? left->repr()  : "");
        s.append((right!=nullptr) ? right->repr() : "");
        s.append(1, ')');
        return s;
    }

    int add_child(Node* nptr)
    {
        std::cout << val << "->" << nptr->val << '\n';
        if      (nchild==0) {left=nptr; ++nchild; return 0;}
        else if (nchild==1)
        {
            if (left==nptr) return 2;
            else
            {
                Node* temp{left};
                left = (nptr->val < temp->val) ? nptr : temp;
                right= (nptr->val > temp->val) ? nptr : temp;
                ++nchild;
                return 0;
            }
        } //success
        else return 1; // fail
    }
    int add_parent(Node* nptr)
    {
        if (parent!=nullptr) return 1;
        else {parent=nptr; return 0;}
    }
};

class Tree
{
public:
    Tree(){}
    std::unordered_map<char, Node*> bank;
    Node boxes[26]{};
    size_t idx{0};
    Node* root{};

    std::string repr()
    {
        // std::cout << "Tree repr()\n";
        return root->repr();
    }

    int store_node(char c)
    {
        if (bank.find(c)==bank.end())
        { // no node in bank
            boxes[idx].val=c;
            bank[c] = &boxes[idx];
            ++idx;
            return 0;
        }
        else return 1;
        // node is in bank
    }
    int find_parent()
    {
        int parent_count{0};
        for (size_t i{0}; i<idx; ++i)
        {
            if (boxes[i].parent==nullptr)
            {
                std::cout << boxes[i].repr() << '\n';
                root = &boxes[i];
                ++parent_count;
            }
        }
        return parent_count;
    }
};

/*
std::string test_tree()
{
    Tree t{};
    Node A{}, B{}, C{}, D{}, E{};
    A.left  = &B;
    A.right = &C;
    B.left  = &D;
    B.right = &E;
    A.val = 'A';
    B.val = 'B';
    C.val = 'C';
    D.val = 'D';
    E.val = 'E';

    t.root = &A;

    return t.repr();
}
*/

std::string sExpression(std::string nodes) {
    std::cout << nodes << '\n';

    bool from_flag{false}, to_flag{false};
    bool e1{false}, e2{false}, e3{false}, e4{false}, e5{false};
    Node* from_node{};

    Tree t{};

    for (auto& c : nodes)
    {
        if (from_flag)
        {
            from_flag = false;
            t.store_node(c);
            from_node = t.bank[c];
        }
        else if (to_flag)
        {
            to_flag = false;
            t.store_node(c);
            int temp{from_node->add_child(t.bank[c])};
            if      (temp==1) e1=true;
            else if (temp==2) e2=true;
            if (t.bank[c]->add_parent(from_node)) e3=true;
        }

        if (c=='(') from_flag=true;
        else if (c==',') to_flag=true;
    }
    int temp{t.find_parent()};
    if (temp==0) e3=true;
    if (temp>1)  e4=true;

    if      (e1) return "E1";
    else if (e2) return "E2";
    else if (e3) return "E3";
    else if (e4) return "E4";
        // else if (e5) return "E5";
    else return t.repr();
}

int tree_valid_main()
{
//    ofstream fout(getenv("OUTPUT_PATH"));

    std::string nodes;
//    getline(cin, nodes);
    std::cin >> nodes;

    std::string result = sExpression(nodes);
    std::cout << result << '\n';

//    fout << result << "\n";
//
//    fout.close();

    return 0;
}

