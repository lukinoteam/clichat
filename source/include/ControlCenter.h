#ifndef CONTROLCENTER_H
#define CONTROLCENTER_H

#include <string>
#include <queue>

using namespace std;

class ControlCenter
{
    public:
        ControlCenter();
        virtual ~ControlCenter();
        void addMessage(string str);
    private:
        queue <string> message;
};

#endif // CONTROLCENTER_H
