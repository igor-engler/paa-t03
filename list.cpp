#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

class Node{
    public:
    int data;
    Node* next;
};

Node* newNode(int data){
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void sortedInsert(Node** head, Node* newNode, long long int &cont_insert){
    Node** current = head;
    while(*current!=NULL && (*current)->data < newNode->data){
        cont_insert++;
        current = &((*current)->next);
    }
    newNode->next = *current;
    *current = newNode;
}

void printList(Node* head){
    Node* tmp = head;
    while(tmp!=NULL){
        std::cout<<tmp->data<<" ";
        tmp = tmp->next;
    }
    //std::cout<<"NULL"<<std::endl;
}

std::vector<int>listToVec(Node* head){
    Node* tmp = head;
    std::vector<int> result;
    while(tmp!=NULL){
        result.push_back(tmp->data);
        tmp = tmp->next;
    }
    return result;
}


int binarySearch(std::vector<int>vec, int low, int high, int num, long long int &cont_search){
    if(low <= high){
        int mid = low +(high-low)/2;
        cont_search++;
        if (vec[mid] == num){
            //cont_search++;
            //std::cout<<num<<" found\n";
            return mid;
        }
        if(vec[mid] < num){
            return binarySearch(vec, low, mid-1, num, cont_search);
            //low = mid + 1;
        }
        else{
            return binarySearch(vec, mid+1, high, num, cont_search);
            //high = mid  -1;
        }
    }
    //std::cout<<num<<" not found\n";
    return -1;
}

int main(){
    long long int cont_insert = 0, cont_search = 0;
    std::ifstream file("Construir15000.txt");

    Node* head = NULL;

    int num;
    auto start = std::chrono::steady_clock::now();
    while(!file.eof()){
        file >> num;
        sortedInsert(&head, newNode(num), cont_insert);
    }
    auto end = std::chrono::steady_clock::now();
    auto millis = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start);
    std::cout<<"list creation: "<<millis.count()<<" ms"<<std::endl;
    std::cout<<"comparisons: "<<cont_insert<<std::endl;

    //printList(head);
    std::cout<<std::endl;

    std::vector<int> new_vec = listToVec(head);

    std::ifstream file2("Consultar15000.txt");
    start = std::chrono::steady_clock::now();
    while(!file2.eof()){
        file2 >> num;
        //std::cout<<num2<<std::endl;
        binarySearch(new_vec, 0, new_vec.size()-1, num, cont_search);
    }
    end = std::chrono::steady_clock::now();
    millis = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start);
    std::cout<<"Search time: "<<millis.count()<<" ms"<<std::endl;
    std::cout<<"comparisons: "<<cont_search<<std::endl;

    return 0;
}