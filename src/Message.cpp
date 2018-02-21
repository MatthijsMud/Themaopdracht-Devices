#include "Message.hpp"

void SetPlayer(int player){
	message |= player << 10;
	RecalcControl();
}
void SetData(int weapon){
	message |= weapon << 5;
	RecalcControl();
}
void SetTime(int time){
	message = time << 6;
	RecalcControl();
}
void StartMessage(){
	message = 1<<15;
	RecalcControl(message);
}

void RecalcControl(){
	for(int i = 0; i < 5; i++){
		message |= ( message >> (14-i % 16)) & 1 ^ message >> (9-i % 16)) & 1 ) << 4-i;
	}
}

uint16_t getMessage(){
	return message;
}
