#include "ControlCenter.h"
#include <queue>
using namespace std;

ControlCenter::ControlCenter()
{
    //ctor
}

ControlCenter::~ControlCenter()
{
    //dtor
}

void ControlCenter::addMessage(string str) {
    message.push(str);
}
