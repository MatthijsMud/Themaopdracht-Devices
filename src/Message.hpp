#ifndef DEVICES_MESSAGE_HPP
#define DEVICES_MESSAGE_HPP
#include <stdint.h>

class Message
{
public:
	explicit Message(uint16_t internalMessage);
	uint16_t getMessage() const;
	void SetPlayer(int player);
	void SetData(int weapon);
	void SetTime(int time);
	void StartMessage();

private:
	uint16_t internalMessage = 1 << 15;
	void RecalcControl();
};

#endif // DEVICES_MESSAGE_HPP
