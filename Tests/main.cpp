#include "UnitTests.h"

int main(int arc, char** argv)
{
	int nbFailures = TestUnit::GetInstance().RunTestGroups();
	return nbFailures == 0 ? 0 : 1;
}