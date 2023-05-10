#include <iostream>
#include<string.h>
using namespace std;
class Node{
public:
    int id;
    string name;
    double balance;
    Node* next;
    Node* previous;
};
 
Node* push(Node* tail_ref, int newid, string newname, double newbalance)
{
    Node* node = new Node();
    node->id = newid;
    node->name = newname;
    node->balance = newbalance;
    node->next = nullptr;
    node->previous = tail_ref;
    tail_ref->next = node;
    tail_ref = node;
    return tail_ref;
}

Node* pop(Node* tail_ref){
    tail_ref = tail_ref->previous;
    return tail_ref;
}

Node* findNode(Node* head_ref, int newid){
    Node* traverser = head_ref;
    while(traverser != nullptr){
        if(traverser->id == newid){
            return traverser;
        }
        traverser = traverser->next;
    }
    Node* nullnode = NULL;
    nullnode->name = "Client DNE in Database";
    return nullnode;
}

Node* deleteNode(Node* head_ref, Node* tail_ref, int newid)
{
    Node* target = findNode(head_ref, newid);
    if(target == head_ref){
        delete target;
        return head_ref->next;
    } else if(target == tail_ref){
        tail_ref = target->previous;
        delete target;
        return tail_ref;
    } else{
        target->previous->next = target->next;
        target->next->previous = target->previous;
        delete target;
        return tail_ref;
    }
}
void printNode(Node* node){
    cout << node->id << ", " << node->name << ", " << node->balance << "\n";
}

void sort(Node* head_ref){
    Node* traverser = head_ref;
    Node* temp = NULL;
    while(traverser != nullptr){
        if(traverser->balance < traverser->next->balance){
            temp = traverser->next;
            traverser->next = traverser;
            traverser = temp;
        }
        traverser = traverser->next;
    }
}
void printAll(Node* head_ref){
    Node* traverser = head_ref;
    while(traverser != nullptr){
        printNode(traverser);
        traverser = traverser->next;
    }
}
 
// Driver code
int main(){
    Node* head = NULL;
    Node* tail = NULL;
    Node* find;
    int choice, choice2, id;
    string name;
    double balance;
    while(choice != 7){
        cout << "Please Choose one of the options below. \n";
        cout << "1: add a client \n";
        cout << "2: view a specific client \n";
        cout << "3: update client balance \n";
        cout << "4: remove a client \n";
        cout << "5: Sort by Balance \n";
        cout << "6: View all Clients \n";
        cout << "7: quit \n Choice: ";
        cin >> choice;
        switch(choice){
            case 1:
                cout << "Enter the Client's ID: \n";
                cin >> id;
                cout << "Enter the Client's Name: \n";
                cin >> name;
                cout << "Enter the Client's Balance: \n";
                cin >> balance;
                if(head == NULL){
                    Node* node = new Node();
                    node->id = id;
                    node->name = name;
                    node->balance = balance;
                    node->next = nullptr;
                    node->previous = nullptr;
                    head = node;
                    tail = node;
                }else{
                    tail = push(tail, id, name, balance);
                }
                break;
            case 2:
                cout << "Enter the Client's ID: \n";
                cin >> id;
                find = findNode(head, id);
                if(find->name.compare("Client DNE in Database") == 0){
                    cout << "Client Does Not Exist in Database \n";
                }else{
                    printNode(find);
                }
                break;
            case 3:
                cout << "Enter the Client's ID: \n";
                cin >> id;
                if(findNode(head, id)->name.compare("Client DNE in Database") == 0){
                    cout << "Client Does Not Exist in Database \n";
                }else{
                    cout << "Client " << id << " found with a balance of $" << findNode(head, id)->balance << "\nPlease Enter A New Balance\n";
                    cin >> balance;
                    choice2 = 0;
                    while(choice2 != 1 && choice2 != 2){
                        cout << "Please Confirm:\n Changing Account " << id << "'s Balance from " << findNode(head, id)->balance << " to " << balance << "\n";
                        cout << "1. Confirm \n2. Cancel\n";
                        cin >> choice2;
                        if(choice2 != 1 && choice2 != 2){
                            cout << "Incorrect Confirmation Option\n";
                        }
                    }
                    if(choice2 = 1){
                    findNode(head, id)->balance = balance;
                    }
                }
                break;
            case 4:
                cout << "Enter the Client's ID: \n";
                cin >> id;
                if(id == head->id && head != tail){
                    head = deleteNode(head, tail, id);
                    break;
                }
                if(id == tail->id && head != tail){
                    tail = deleteNode(head, tail, id);
                    break;
                }
                deleteNode(head, tail, id);
                break;
            case 5:
                sort(head);
                break;
            case 6:
                printAll(head);
                break;
            case 8:
                Node* node = new Node();
                    node->id = 1;
                    node->name = "REED";
                    node->balance = 342.12;
                    node->next = nullptr;
                    node->previous = nullptr;
                    head = node;
                    tail = node;
                tail = push(tail, 2, "cooper", 4132.19);
                tail = push(tail, 3, "stan", 2145.20);
                tail = push(tail, 4, "dan", 21456.20);
                tail = push(tail, 5, "roger", 214512.20);
                tail = push(tail, 6, "rebecca", 214.20);
        }
    }
    return 0;
}
