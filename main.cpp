#include <iostream>
#include <fstream>
using namespace std;

struct matrix1{
    int definition;
    int row;
    int column;
    matrix1(int definition, int row, int column) {
        this->definition = definition;
        this->row = row;
        this->column = column;
    }
};
struct Nodelist1{
    struct Node1{
        matrix1* data;
        Node1* next;
        Node1(matrix1& st) {
            data = &st;
        }
    };
    Node1* head = nullptr;
    Node1* tail = nullptr;
    void fill(matrix1* data);

    void print(){
        Node1* iter = head;
        cout << "|Matrix1|"<<endl;
        while(iter != nullptr){
            cout << "A"<<(iter->data->row) + 1 <<(iter->data->column) + 1<< " = "<< iter->data->definition<<endl;
            iter = iter->next;
        }
    }

};
void Nodelist1::fill(matrix1* data){
    Node1* node = new Node1(*data);
    if (head == nullptr){
        head = node;
        tail = node;
    }
    else{
        tail->next = node;
        tail = node;
    }
}

struct matrix2{
    int definition;
    int row;
    int column;
    matrix2(int definition, int row, int column) {
        this->definition = definition;
        this->row = row;
        this->column = column;
    }
};
struct Nodelist2{
    struct Node2{
        matrix2* data;
        Node2* next;
        Node2(matrix2& st) {
            data = &st;
        }
    };
    Node2* head = nullptr;
    Node2* tail = nullptr;
    void fill(matrix2* data);

    void print(){
        Node2* iter = head;
        cout << "|Matrix2|"<<endl;
        while(iter != nullptr){
            cout << "A"<<(iter->data->row) + 1 <<(iter->data->column) + 1<< " = "<< iter->data->definition<<endl;
            iter = iter->next;
        }
    }


};

void Nodelist2::fill(matrix2* data){
    Node2* node = new Node2(*data);
    if (head == nullptr){
        head = node;
        tail = node;
    }
    else{
        tail->next = node;
        tail = node;
    }
}

struct matrix_sum{
    int definition;
    int row;
    int column;
    matrix_sum(int definition, int row, int column) {
        this->definition = definition;
        this->row = row;
        this->column = column;
    }
};
struct Nodelist3{
    struct Node3{
        matrix_sum* data;
        Node3* next;
        Node3(matrix_sum& st) {
            data = &st;
        }
    };
    Node3* head = nullptr;
    Node3* tail = nullptr;
    void fill(matrix_sum* data);

    void print(){
        Node3* iter = head;
        cout << "|Matrix3|"<<endl;
        while(iter != nullptr){
            cout << "A"<<iter->data->row+1 <<iter->data->column+1<< " = "<< iter->data->definition<<endl;
            iter = iter->next;
        }
        cout << endl;
    }


};

void Nodelist3::fill(matrix_sum* data){
    Node3* node = new Node3(*data);
    if (head == nullptr){
        head = node;
        tail = node;
    }
    else{
        tail->next = node;
        tail = node;
    }
}


int num_row(std::ifstream &matrix) {
    matrix.open("matrix1.txt");
    char ch;
    int ch_row = 0;
    while(matrix.get(ch)){
        if(ch=='\n') break;
        if(isdigit(ch)) ch_row++;
    }
    matrix.close();
    return ch_row;
}



static void fill_print_f(Nodelist1 &list1, int **matrics, std::ifstream &matrix) {
    int definition = 0;
    int row = 0;
    int column = 0;
    for(int i = 0; i < num_row(matrix); i++){
//        for(int j = 0; j < num_row(matrix); j++){
//            definition = matrics[i][j];
//            row = i;
//            column = j;
//            if(definition != 0){
//                list1.fill(new matrix1(definition, row, column));
//            }
//        }
        for(int j = 0; j < num_row(matrix); j++){
            definition = matrics[i][j];
            row = i;
            column = j;
            list1.fill(new matrix1(definition, row, column));
        }
    }
    list1.print();
}

static void fill_print_s(Nodelist2 &list2, int **matrics_s, std::ifstream &matrix_s) {
    int definition = 0;
    int row = 0;
    int column = 0;
    for(int i = 0; i < num_row(matrix_s); i++){
//        for(int j = 0; j < num_row(matrix_s); j++){
//            definition = matrics_s[i][j];
//            row = i;
//            column = j;
//            if(definition != 0){
//                list2.fill(new matrix2(definition, row, column));
//            }
//        }
        for(int j = 0; j < num_row(matrix_s); j++){
            definition = matrics_s[i][j];
            row = i;
            column = j;
            list2.fill(new matrix2(definition, row, column));
        }
    }
    list2.print();
}

static void sum(const Nodelist1 &list1, const Nodelist2 &list2, Nodelist3 &list3) {
    Nodelist1::Node1* iter1 = list1.head;
    Nodelist2::Node2* iter2 = list2.head;
    int definition1, row, column, definition2, sum;
    while(iter1 != nullptr){
        definition1 = iter1->data->definition;
        definition2 = iter2->data->definition;
        row = iter1->data->row;
        column = iter1->data->column;
        sum = definition1 + definition2;
        list3.fill(new matrix_sum(sum, row, column));
        iter1 = iter1->next;
        iter2 = iter2->next;
    }
    list3.print();
}

static void matrix_compression(char *matr_compr, int **matrics_multiplication, int size1) {
    int k = 0;
    for(int i = 0; i < size1; i++){
        for(int j = 0; j < size1; j++){
            if(matrics_multiplication[i][j]%10 == 0){
                matr_compr[k] = matrics_multiplication[i][j] + '0';
                k++;
            }else{
                matr_compr[k] = matrics_multiplication[i][j]/10 + '0';
                k++;
                matr_compr[k] = matrics_multiplication[i][j]%10 + '0';
                k++;
            }
        }
    }
    cout << endl << matr_compr;
    int counter = 1;
    ofstream matrix_compression;
    matrix_compression.open("matrix_compression.txt");
    for(int i = 0; i < size1*size1; i++){
        if(matr_compr[i] == matr_compr[i+1]){
            while(matr_compr[i] == matr_compr[i+1]){
                counter++;
                i++;
            }
            matrix_compression<<"["<<matr_compr[i-1]<<"]"<<counter;
            counter = 1;
        }else{
            matrix_compression<<"["<<matr_compr[i]<<"]"<<counter;
        }
    }
}

static void multiplication(int **matrics_f, int **matrics_s, int size1) {
    int **matrics_multiplication;
    matrics_multiplication = new int* [size1];
    for (int i = 0; i < size1; i++)
    {
        matrics_multiplication[i] = new int[size1];
        for (int j = 0; j < size1; j++)
        {
            matrics_multiplication[i][j] = 0;
            for (int k = 0; k < size1; k++)
                matrics_multiplication[i][j] += matrics_f[i][k] * matrics_s[k][j];
        }
    }

    for(int i = 0; i < size1; i++){
        for(int j = 0; j < size1; j++){
            cout << matrics_multiplication[i][j]<<" ";
        }
        cout << endl;
    }
    char* matr_compr = new char[size1*size1];

    matrix_compression(matr_compr, matrics_multiplication, size1);
}

void read_matrix(){
    ifstream matrix_f;
    ifstream matrix_s;
    int size1 = num_row(matrix_f);
    int size2 = num_row(matrix_s);

    int** matrics_f = new int* [size1];
    for(int count = 0; count < size1; count++)
        matrics_f[count] = new int[size1];

    int ch_num = 0;
    matrix_f.open("matrix1.txt");

    if(!matrix_f.is_open()){
        cout << "File opening error!"<<endl;
    }else{
        char ch;
        int i = 0;
        int j = 0;
        while(matrix_f.get(ch)){
            if(isdigit(ch)){
                matrics_f[i][j] = ch - '0';
                j++;
            }
            if(ch == '\n'){
                i++;
                j = 0;
            }
            ch_num++;
        }
    }

    int** matrics_s = new int* [size2];
    for(int count = 0; count < size2; count++)
        matrics_s[count] = new int[size2];

    ch_num = 0;
    matrix_s.open("matrix2.txt");

    if(!matrix_f.is_open()){
        cout << "File opening error!"<<endl;
    }else{
        char ch;
        int i = 0;
        int j = 0;
        while(matrix_s.get(ch)){
            if(isdigit(ch)){
                matrics_s[i][j] = ch - '0';
                j++;
            }
            if(ch == '\n'){
                i++;
                j = 0;
            }
            ch_num++;
        }
    }
    matrix_f.close();
    matrix_s.close();

//fill_poll
    Nodelist1 list1;
    Nodelist2 list2;
    Nodelist3 list3;
    fill_print_f(list1, matrics_f, matrix_f);
    cout << endl;
    fill_print_s(list2, matrics_s, matrix_s);

    sum(list1, list2, list3);
    multiplication(matrics_f, matrics_s, size1);
}

int main(){
    read_matrix();
}
