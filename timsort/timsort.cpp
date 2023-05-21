#include <iostream>
#include <algorithm>
#include <cstdlib>


using namespace std;
#define SIZE 10

class Stack
{
    pair<int, int>* arr;
    int top;
    int capacity;

public:
    Stack(int size = SIZE);      
    ~Stack();                       

    void push(int x, int y);
    void pop();
    pair<int, int> topElement();

    int size();
    bool isEmpty();
    bool isFull();
};

Stack::Stack(int size)
{
    arr = new pair<int, int>[size];
    capacity = size;
    top = -1;
}

Stack::~Stack() {
    delete[] arr;
}

void Stack::push(int x, int y)
{
    if (isFull())
    {
        cout << "Overflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
    arr[++top].first = x;
    arr[top].second = y;
}

void Stack::pop()
{
    // check for stack underflow
    if (isEmpty())
    {
        cout << "Underflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
    arr[top--];
}

pair<int, int> Stack::topElement()
{
    if (!isEmpty()) {
        return arr[top];
    }
    else {
        exit(EXIT_FAILURE);
    }
}

int Stack::size() {
    return top + 1;
}

bool Stack::isEmpty() {
    return top == -1;              
}

bool Stack::isFull() {
    return top == capacity - 1; 
}

class List
{
public:
    ~List();

    List();

    void clear();

    void insert(int index, int value);

    void removeAt(int index);

    void pop_front();

    void pop_back();

    void push_front(int data);

    void push_back(int data);

    int GetSize() { return size; }

    void PrintList(List list);

    int& operator[](const int index);

private:

    class Node {
    public:
        Node* pnext;
        int data;
        Node(int data = -1, Node* pnext = nullptr)
        {
            this->data = data;
            this->pnext = pnext;
        }
    };
    int size;
    Node* head;
};

List::List()
{
    size = 0;
    head = nullptr;
}

List::~List()
{

}

void List::push_back(int data) {
    if (head == nullptr)
    {
        head = new Node(data);
    }
    else
    {
        Node* current = head;
        while (current->pnext != nullptr)
        {
            current = current->pnext;
        }
        current->pnext = new Node(data);
    }
    size++;
}

void List::pop_back()
{
    removeAt(size - 1);
}

void List::push_front(int data)
{
    head = new Node(data, head);
    size++;
}

void List::removeAt(int index)
{
    if (index == 0)
        pop_front();
    else
    {
        Node* current = this->head;
        for (int i = 0; i < index - 1; i++)
            current = current->pnext;
        Node* toDelete = current->pnext;
        current->pnext = toDelete->pnext;
        delete toDelete;
        size--;
    }

}

void List::insert(int index, int value)
{

    int counter = 0;
    Node* current = this->head;
    while (index != counter && current != nullptr)
    {
        current = current->pnext;
        counter++;
    };
    Node* temp = new Node(value, current->pnext);
    current->pnext = temp;
    size++;
}

void List::pop_front()
{
    Node* temp = head;

    head = head->pnext;

    delete temp;

    size--;
}

void List::clear()
{
    while (size)
        pop_front();
}

int& List::operator[](const int index)
{
    int counter = 0;
    Node* current = this->head;
    while (current != nullptr)
    {
        if (index == counter)
            return current->data;
        current = current->pnext;
        counter++;
    }
}

void List::PrintList(List list) {
    for (int i = 0; i < size; i++)
        cout << i<<" " << list[i] << "\n";

}

void reverse(List arr,int start, int end)
{
    for (int low = start, high = end - 1; low < high; low++, high--) {
        swap(arr[low], arr[high]);
    }
}


int GetMinrun(int n)
{
    int r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

int binarySearch(List a, int item, int low, int high)
{
    if (low == a.GetSize())
        return -1;
    if (high <= low)
        return (item > a[low]) ?
        (low + 1) : low;

    int mid = (low + high) / 2;

    if (item == a[mid])
        return mid + 1;

    if (item > a[mid])
        return binarySearch(a, item,
            mid + 1, high);
    return binarySearch(a, item, low,
        mid - 1);
}

int Galloping(List arr, int ArrayPointer, int ArraySize, int i,int b) {
    int q = 0;
    q = binarySearch(arr, i, ArrayPointer, (ArrayPointer + ArraySize-b));
    
    if (q >= 0)
    {
        if (q != ArrayPointer)
            int a = 0;
        return q-ArrayPointer;
    }
    else if (arr[ArrayPointer + ArraySize-1-b] <= i)
        return ArraySize;
    else
    {
        q = 0;
        while (arr[ArrayPointer + q] <= i)
            q++;
        return q;
    }
}

void insertionSort(List a, int start, int end)
{
    int i, loc, j, selected;

    for (i = start; i < end; ++i)
    {
        j = i - 1;
        selected = a[i];

        loc = binarySearch(a, selected, start, j);                    

        while (j >= loc && j!=-1)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = selected;
    }
}
void merge(List array, int firstArrayPointer, int firstArraySize, int secondArrayPointer, int SecondArraySize)
{
    List temp;
    for (int i = 0; i < firstArraySize; i++)
        temp.push_back(array[firstArrayPointer + i]);
    int pointerLeft = firstArrayPointer;
    int pointerRight = secondArrayPointer;
    int i = 0;
    int b = 0;
    List sorted;
    int GallopIdentF = 0;
    int GallopIdentS = 0;
    
    while (secondArrayPointer != SecondArraySize+pointerRight && i != temp.GetSize())
    {
        if (temp[i] < array[secondArrayPointer])
        {
           sorted.push_back(temp[i]);
           i++;
           GallopIdentF++;
           GallopIdentS = 0;
           if (GallopIdentF >= 7)
           {
               int q = Galloping(array, firstArrayPointer + i, firstArraySize-i, array[pointerRight+b],i);
               for (int r = 0; r < q - i; r++)
               {
                   sorted.push_back(temp[r+i]);
                   i++;
               }
               GallopIdentF = 0;
           }
        }
        else
        {
            sorted.push_back(array[secondArrayPointer]);
            secondArrayPointer++;
            b++;
            GallopIdentF=0;
            GallopIdentS++;
            if (GallopIdentS >= 7)
            {
                int q=Galloping(array, secondArrayPointer, SecondArraySize, array[pointerLeft+i],b);
                for (int r = 0; r < q - b; r++)
                {
                    sorted.push_back(array[pointerRight+b + r]);
                    secondArrayPointer++;
                }
                GallopIdentS = 0;
            }

        }
    }
    while (secondArrayPointer != SecondArraySize+pointerRight)
    {
        sorted.push_back(array[secondArrayPointer]);
        secondArrayPointer++;
    }
        while (i != temp.GetSize())
        {
            sorted.push_back(temp[ i ]);
            i++;
        }

        for (int i = 0; i < firstArraySize + SecondArraySize; i++)
            array[pointerLeft + i] = sorted[i];
}
void timSort(List arr, int n)
{
    int minrun=GetMinrun(n);
    int RunElemsCount = 1;
    int pointer = 0;
    int start = 0;
    while (pointer<n-1) {                              
        if (arr[pointer] > arr[pointer + 1])
        {
            while (arr[pointer] > arr[pointer + 1])
            {
                pointer++; RunElemsCount++;
                if (pointer == n-1)
                    break;
            }
            reverse(arr, start, pointer+1);
        }
        else if (arr[pointer] <= arr[pointer + 1])
        {
            while (arr[pointer] <= arr[pointer + 1])
            {
                pointer++; RunElemsCount++;
                if (pointer == n-1)
                    break;
            }
        }
        if (RunElemsCount < minrun)
            pointer = start + minrun-1;
        if (pointer >= n)
            pointer = n - 1;
        RunElemsCount = 1;
        insertionSort(arr, start, pointer+1); 
        pointer++;
        start = pointer;
    }
    Stack s;
    int cur = 0;
    while (cur < n) {
        int c1 = cur;
            for (int i = cur; i < n-1; i++)
            {
                if (arr[c1] <= (arr[c1 + 1]))
                    c1++;
                else
                    break;
            }
            s.push(c1 - cur + 1, cur);
        cur = c1 + 1;
        while (s.size() >= 3) {
            pair<int, int> x = s.topElement();
            s.pop();
            pair<int, int> y = s.topElement();
            s.pop();
            pair<int, int> z = s.topElement();
            s.pop();
            if (z.first > x.first + y.first && y.first > x.first) {
                s.push(z.first,z.second);
                s.push(y.first,y.second);
                s.push(x.first,x.second);
                break;
            }
            else if (z.first > x.first) {
                merge(arr,y.second, y.first, x.second, x.first);
                s.push(z.first, z.second);
                s.push( x.first + y.first, y.second );
            }
            else {
                merge(arr, z.second, z.first, y.second, y.first);
                s.push(z.first + y.first, z.second );
                s.push(x.first, x.second);
            }   
        }
    }
    while (s.size() != 1) {
        pair<int, int> x = s.topElement();
        s.pop();
        pair<int, int> y = s.topElement();
        s.pop();
        if (x.second < y.second) swap(x, y);
        merge(arr, y.second, y.first, x.second, x.first);
        s.push( y.first + x.first, y.second );
    }
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d  ", arr[i]);
    printf("\n");
}

int main()
{
    setlocale(LC_ALL, "Rus");
    List arr;
    int input;

    int i = 0;
    int array[600]{ 60, 96, 6, 75, 83, 26, 89, 11, 95, 70, 27, 2, 90, 80, 86, 100, 56, 34, 91, 96, 75, 27, 22, 30, 84, 84, 6, 54, 85, 18, 4, 68, 84, 16, 99, 81, 58, 60, 77, 54, 9, 96, 97, 49, 28, 47, 45, 6, 43, 14, 14, 15, 14, 55, 95, 9, 79, 25, 91, 42, 82, 60, 77, 46, 57, 38, 61, 14, 50, 100, 28, 95, 95, 14, 46, 83, 65, 31, 41, 74, 37, 22, 48, 34, 95, 37, 33, 11, 31, 57, 79, 68, 36, 13, 15, 8, 94, 53, 46, 14, 9, 59, 8, 48, 38, 0, 99, 52, 43, 98, 90, 28, 65, 18, 37, 42, 68, 49, 19, 93, 4, 89, 87, 39, 39, 2, 43, 28, 15, 30, 71, 59, 32, 0, 52, 59, 40, 13, 62, 71, 90, 41, 37, 79, 2, 10, 48, 45, 89, 70, 37, 18, 70, 62, 67, 22, 65, 82, 11, 11, 27, 87, 44, 68, 10, 65, 38, 26, 31, 51, 100, 26, 30, 27, 64, 36, 83, 41, 91, 47, 63, 68, 75, 30, 68, 70, 36, 100, 22, 78, 97, 14, 84, 9, 75, 67, 93, 46, 28, 50, 12, 60, 35, 47, 25, 12, 89, 35, 90, 53, 30, 91, 32, 3, 99, 40, 62, 65, 26, 32, 98, 89, 9, 78, 1, 15, 59, 38, 9, 80, 80, 64, 87, 44, 45, 96, 74, 61, 100, 78, 28, 18, 7, 78, 35, 40, 73, 6, 32, 77, 11, 2, 55, 28, 4, 9, 86, 2, 41, 24, 0, 79, 38, 74, 35, 28, 2, 19, 60, 26, 78, 65, 29, 88, 88, 23, 40, 98, 53, 97, 57, 88, 69, 3, 23, 50, 8, 97, 36, 41, 14, 70, 53, 86, 3, 95, 91, 94, 51, 11,160, 183, 172, 180, 134, 161, 135, 183, 121, 101, 111, 109, 198, 184, 119, 116, 165, 150, 168, 132, 112, 119, 165, 121, 151, 114, 130, 198, 131, 150, 135, 161, 119, 110, 134, 169, 161, 133, 147, 157, 108, 144, 128, 128, 164, 139, 192, 185, 101, 171, 129, 107, 155, 108, 197, 188, 157, 186, 149, 153, 127, 178, 118, 151, 130, 142, 155, 124, 125, 153, 169, 198, 190, 154, 113, 164, 169, 150, 129, 167, 189, 189, 113, 196, 199, 116, 141, 172, 194, 107, 145, 153, 155, 160, 158, 183, 169, 193, 146, 198, 199, 106, 118, 200, 126, 176, 153, 143, 171, 136, 177, 140, 112, 120, 105, 112, 182, 169, 138, 134, 198, 186, 187, 169, 148, 102, 166, 121, 193, 129, 166, 178, 163, 123, 195, 101, 109, 106, 102, 150, 154, 199, 181, 183, 191, 110, 122, 161, 196, 159, 141, 142, 147, 190, 127, 188, 174, 104, 157, 168, 173, 191, 123, 143, 200, 150, 158, 150, 149, 192, 109, 177, 106, 117, 118, 126, 192, 198, 164, 150, 196, 148, 173, 139, 178, 173, 108, 102, 182, 186, 196, 164, 165, 157, 199, 103, 178, 110, 146, 184, 119, 184, 145, 189, 128, 100, 178, 134, 108, 187, 188, 158, 146, 125, 167, 190, 110, 180, 192, 176, 126, 158, 195, 113, 155, 135, 129, 104, 151, 173, 156, 119, 107, 100, 179, 142, 197, 108, 138, 190, 167, 149, 154, 132, 164, 142, 117, 145, 150, 197, 121, 102, 159, 159, 170, 145, 130, 169, 198, 186, 200, 188, 114, 187, 144, 148, 163, 192, 121, 143, 195, 187, 160, 188, 173, 139, 126, 185, 122, 150, 176, 130, 116, 143, 189, 116, 157, 185, 115, 138, 149, 138, 167, 171, 185, 123, 180, 124, 115, 157 };
    while (i < 600)
    {
        arr.push_back(array[i]);
        i++;
    }
   /* while (cin >> input)
        arr.push_back(input);*/
    int q = clock();
    timSort(arr, arr.GetSize());
    int t = clock();
    arr.PrintList(arr);
    std::cout << "Для вычисления понадобилось "
        << t << " тиков времени или "
        << ((float)t) / CLOCKS_PER_SEC << " секунд\n" << ((float)q) / CLOCKS_PER_SEC;
    return 0;
}