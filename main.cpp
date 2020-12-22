#include <iostream>
#include <ctime>
#include "Tree.h"
#include "Node.h"

using namespace std;

int main()
{
    srand(time(0));
    Tree<int> t;
    int n;
    for (int i = 0; i < 10; ++i)
        t.insert(rand() % 50);
    t.Print();
    cout << endl << "size = " << t.GetSize() << " root is: " << t.GetRootVal()<< endl;
    cout << "1. delete, 2. insert, 3. left turn, 4. right turn\n\n";
    while (t.GetSize())
    {
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            {
                cin >> n;
                t.del(n);
                break;
            }
        case 2:
            {
                cin >> n;
                t.insert(n);
                break;
            }
        case 3:
            {
                t.LeftRootTurn();
                break;
            }
        case 4:
            {
                t.RightRootTurn();
                break;
            }
        default:
            {
                break;
            }
        }

        t.Print();
        cout << endl << "size = "<< t.GetSize() << " root is: " << t.GetRootVal() << endl;
    }
    return 0;
}
