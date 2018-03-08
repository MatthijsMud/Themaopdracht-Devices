#include "Message.hpp"

void Message::SetPlayer(int player){
	internalMessage |= player << 10;
	RecalcControl();
}
void Message::SetData(int weapon){
	internalMessage |= weapon << 5;
	RecalcControl();
}
void Message::SetTime(int time){
	internalMessage = time << 6;
	RecalcControl();
}
void Message::StartMessage(){
	internalMessage = 1<<15;
	RecalcControl();
}

void Message::RecalcControl(){
	for(int i = 0; i < 5; i++){
		internalMessage |= (( internalMessage >> (14-i % 16)) & 1) ^ ((internalMessage >> (9-i % 16)) & 1 ) << (4-i);
	}
}

uint16_t Message::getMessage() const{
	return internalMessage;
}
