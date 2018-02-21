#ifndef DEVICES_MESSAGE_HPP
#define DEVICES_MESSAGE_HPP

class Message
{
public:
	Message(explicit uint16_t Message);
	uint16_t getMessage();
	void SetPlayer(int player);
	void SetData(int weapon);
	void SetTime(int time);
	void StartMessage();

private:
	uint16_t Message = 1<<15;
	RecalcControl();
};

#endif // DEVICES_MESSAGE_HPP
