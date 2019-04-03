#include <queue>
using namespace std;
class ControlCenter
{
public:
	ControlCenter() {

	}
	void addMessage(string str) {
		message.push(str);
	}
private:
	queue <string> message;
};

