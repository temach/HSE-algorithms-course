#include <iostream>
#include "linked_list.h"

using namespace std;

bool sorted(int *arr, int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

void print(int* arr, int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

void print(LinkedList* lst, int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << lst->get(i) << ' ';
    }
    cout << endl;
}

bool check_sort(LinkedList* lst, int n) {
    for (int i=0; i < n-1; i++) {
        if (lst->get(i) > lst->get(i+1)) {
            return false;
        }
    }
    return true;
}


void copy_array_2(int *source, int *dest, int len) {
    while (len-- > 0) {
        dest[len] = source[len];
    }
}


int main()
{
    int N = 10;
    int a[N];

    int min = -50000;
    int max = 50000;
    int sort_loops = 1000;

    // check for 4
    int nb = 4;
    int b[] = {-18388,41158,-6998,-15039};
    LinkedList* mylst = LinkedList::create_from_array(b, nb);
    print(mylst, mylst->get_size());
    mylst->push_back(5);
    mylst->push_front(100);
    mylst->insert(1, 9999);
    print(mylst, mylst->get_size());
    cout << mylst->get(1) << endl;
    cout << mylst->get(3) << endl;
    cout << mylst->get(5) << endl;
    cout << mylst->get(6) << endl;
    mylst->erase(2);
    mylst->erase(2);
    mylst->erase(2);
    mylst->erase(1);
    mylst->erase(0);
    mylst->erase(0);
    mylst->sort();
    mylst->clear();
    print(mylst, mylst->get_size());
    mylst->insert(0, 32);
    mylst->push_back(5);
    mylst->insert(0, 32);
    mylst->sort();
    print(mylst, mylst->get_size());

    for (int i=0; i < sort_loops; i++) {
        int N = (rand() % (int)(15));
        int safe_orig[N];
        // fill array
        for (int j=0; j < N; j++) {
            a[j] = min + (rand() % (int)(max - min + 1));
        }
        // backup for debug
        copy_array_2(a, safe_orig, N);
        // try sorting it
        LinkedList* list = LinkedList::create_from_array(a, N);
        list->sort();
        // check that its correct
        bool res = check_sort(list, N);
        if (! res) {
            print(safe_orig, N);
            print(list, N);
            cout << "\n\n" << endl;
        }
    }

//    int nd = 10;
//    int d[] = {-18388,41158,46298,-31830,-6998,-15039,-16054,9173,40927,3986};
//    LinkedList* lst = LinkedList::create_from_array(d, nd);
//    lst->sort();
//    print(lst, nd);
//
//    // check for two elements
//    int nc = 2;
//    int c[] = {18388,-41158};
//    lst = LinkedList::create_from_array(c, nc);
//    lst->sort();
//    print(lst, nc);
//

    return 0;
}
