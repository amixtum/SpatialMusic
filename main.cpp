#include "Engine.h"
#include <ctime>

using namespace std;
using namespace sf;

int main()
{
    srand (time(NULL));
    Engine test_run("Test Run");
    test_run.Init();
}
