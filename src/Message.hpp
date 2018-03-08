#ifndef DEVICES_MESSAGE_HPP
#define DEVICES_MESSAGE_HPP
#include <stdint.h>

class Message
{
public:
	Message();
	// Construct a message from received databits.
	explicit Message(uint16_t internalMessage);
<<<<<<< HEAD
	uint16_t getMessage() const;
	void SetPlayer(int player);
	void SetData(int weapon);
	void SetTime(int time);
	void StartMessage();
=======
	// Allow copying of a message, as it is basically a plain old datatype.
	Message(const Message & other) = default;
	Message & operator= (const Message & other) = default;
	
	
	//! Gets the underlying data including the checksum. 
	//!
	//! The result of this function is intended to be used for a protocol that
	//! can send it to another device.
	uint16_t getMessage() const;
	
	uint16_t getPlayer() const ;
	void setPlayer(uint16_t player);
	
	//! Gets the data that is sent. The value has little meaning on its own.
	uint16_t getData() const;
	//
	void setData(uint16_t data);
	
	//! Gets the time (in minutes) that the match will take.
	uint16_t getTime() const;
	//! 
	//! @param time Time (in minutes) that the game should run.
	void setTime(uint16_t time);
	
	//!
	void setStartMessage();
	//! Whether the message is a start command.
	bool isStartMessage() const;
>>>>>>> 098e48d25ff5beb3dd2a218ecb70d04f007eeb7a

private:
	uint16_t internalMessage = 1 << 15;
	void calculateChecksum();
};

#endif // DEVICES_MESSAGE_HPP
