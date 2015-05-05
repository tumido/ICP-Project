#include <iostream>
#include "include/GameManager.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    MazeCard swag("L");
    swag.turnRight();
    cout << swag.canGo(MazeCard::LEFT) << endl;
    return 0;
}
