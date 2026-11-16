#include <iostream>
#include <cmath>
using namespace std;
struct node {
    char element;
    node* left=NULL;
    node* right=NULL;
    node(char value){
        element=value;
        left=NULL;
        right=NULL;
    }
};
template<class type>
class stack{
private:
    struct node{
        type data;
        node* next;
    };
public:
    node* top;
    void push(type elem){
        node* temp= new node();
        temp->data=elem;
        temp->next=NULL;
        if(top != NULL)
            temp->next=top;
        top=temp;
    }
    type pop(){
        type value;
        if(top==NULL) {
            cout << "the stack is empty" << endl;
        }
        else{
            node* firstNode=top;
            top=firstNode->next;
            value=firstNode->data;
            delete firstNode;
            return value;
        }
    }
    type peek(){
        if(top==NULL){
            cout<<"stack is empty"<<endl;
        }
        else{
            return top->data;
        }
    }
    bool isEmpty(){
        if(top == NULL)
            return true;
        else
            return false;
    }
    void display(){
        node * temp=top;
        if(top==NULL){
            cout<<"stack is empty";
        }
        while (temp != NULL ) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout<<"\n";
    }
};
bool isDigit(char elem){
    if((elem-'0' >= 0) && (elem-'0' <= 9))
        return true;
    else
        return false;
}
bool isOperator(char elem){
    if(elem == '*' || elem == '/' || elem=='^' || elem=='+'||elem=='-')
        return true;
    else
        return false;
}
int toDigit(char elem){
    return elem-'0';
}
void preOrder(node *root){
    string sum;
    if(root==NULL)
        return;
    cout<<root->element<<endl;
    preOrder(root->left);
    preOrder(root->right);
}
int operations(int leftSide, char operation, int rightSide){
    if (operation == '+')
        return leftSide + rightSide;

    if (operation == '-')
        return leftSide - rightSide;

    if (operation == '*')
        return leftSide * rightSide;

    if ( operation == '/')
        return leftSide / rightSide;

    if ( operation == '^')
        return pow(leftSide , rightSide);
}
int evaluateExpressionTree(node* root) {

    if (!root)
        return 0;

    if (!root->left && !root->right)
        return toDigit(root->element);

    int treeLeftSide  = evaluateExpressionTree(root->left);
    int treeRightSide = evaluateExpressionTree(root->right);

    operations(treeLeftSide, root->element, treeRightSide);
}

void expressionTree(string prefix){
    stack<node*> myStack{};
    for( int i=prefix.length()-1; i >= 0; i--){
        if (isDigit(prefix[i])){
            node* treeNode= new node(prefix[i]);
            myStack.push(treeNode);
        }
        else if(isOperator(prefix[i])){
            node* treeNode= new node(prefix[i]);
            treeNode->left=myStack.pop();
            treeNode->right= myStack.pop();
            myStack.push(treeNode);
        }
        else{
            cout<<"invalid expression"<<endl;
            return;
        }
    }
    cout<<evaluateExpressionTree(myStack.peek())<<endl;
}

int main() {
    cout<<"Case 1: \n"<<"the evaluation of prefix expression: (+3*4/82)\n";
    expressionTree("+3*4/82");
    cout<<"Case 2: \n"<<"the evaluation of prefix expression: (+*59/93)\n";
    expressionTree("+*59/93");
    cout<<"Case 3: \n"<<"the evaluation of prefix expression: (++^82*97/84)\n";
    expressionTree("++^82*97/84");
    cout<<"Case 4: \n"<<"the evaluation of prefix expression: (+*/9954)\n";
    expressionTree("+*/9954");
    cout<<"Case 5: \n"<<"the evaluation of prefix expression: (-^*9925)\n";
    expressionTree("-^*9925");
    return 0;
}
