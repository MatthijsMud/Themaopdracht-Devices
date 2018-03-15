#include "Message.hpp"

#include <hwlib.hpp>

Message::Message():
// Set the startbit of the message by default.
internalMessage{1 << 15}
{
	
}

Message::Message(uint16_t internalMessage):
	internalMessage{internalMessage}
{
	
}

uint16_t Message::getMessage() const
{
	return internalMessage;
}

uint16_t Message::getPlayer() const
{
	return (internalMessage >> 10) & 31;
}

void Message::setPlayer(uint16_t player){
	// Player takes 5 bits starting at position [1] (counting from the most 
	// significant bit). The maximimum value that can be expressed is 31.
	
	// Reset the player bits (X-00000-XXXXX-XXXXX).
	internalMessage &= ~(31 << 10);
	internalMessage |= player << 10;
	calculateChecksum();
}

uint16_t Message::getData() const
{
	// Get masked data (X-?????-XXXXX).
	return (internalMessage >> 5) & 31;
}

void Message::setData(uint16_t data){
	// Data takes 5 bits starting at position [6] (from most significant bit).
	// 
	// Reset the data bits (X-XXXXX-00000-XXXXX).
	internalMessage &= ~(31 << 5);
	internalMessage |= data << 5;
	calculateChecksum();
}
void Message::setTime(uint16_t time){
	setData(time);
}
void Message::setStartMessage(){
	setPlayer(0);
	setTime(0);
}

bool Message::isStartMessage() const
{
	// The gamemaster (id 0) is the only one that can issue the start command.
	return getPlayer() == 0 && getData() == 0;
}

void Message::calculateChecksum(){
	// Reset the checksum bits (X-XXXXX-XXXXX-00000).
	internalMessage	&= ~(31 << 0);
	for(int i = 0; i < 5; i++){
		internalMessage |= (( internalMessage >> (14-i % 16)) & 1) ^ ((internalMessage >> (9-i % 16)) & 1 ) << (4-i);
	}
}


hwlib::ostream & operator<< (hwlib::ostream & lhs, const Message & rhs)
{
	uint16_t data = rhs.getMessage();
	lhs << "Message{";
	for (unsigned int i=16; i; --i)
	{
		lhs << ((data >> (i-1)) & 1); 
	}
	lhs << "}";
	return lhs;
}
