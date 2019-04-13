#include "stdafx.h"
#include "ControlCenter.h"
ControlCenter::ControlCenter() {
}
ControlCenter::~ControlCenter() {
}
void ControlCenter::addMessage(string str) {
	this->message.push(str);
}
string ControlCenter::getMessage() {
	return "";
}