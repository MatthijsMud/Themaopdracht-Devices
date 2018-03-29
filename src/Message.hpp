#ifndef DEVICES_MESSAGE_HPP
#define DEVICES_MESSAGE_HPP
//! @file 
//! @author 

#include <stdint.h>

// Forward declaration.
namespace hwlib
{
	class ostream;
}

//! Serves as an abstraction for the raw data that is exchanged between 
//! different devices.
class Message
{
public:
	//! Constructs a message with the startbit set.
	Message();
	// Construct a message from received databits.
	explicit Message(uint16_t internalMessage);

	// Allow copying of a message, as it is basically a plain old datatype.
	Message(const Message & other) = default;
	Message & operator= (const Message & other) = default;
	
	
	//! Gets the underlying data including the checksum. 
	//!
	//! The result of this function is intended to be used for a protocol that
	//! can send it to another device.
	//!
	//! @return Gets the bits that make up the message.
	uint16_t getMessage() const;
	
	//! Gets the id of the player sending the message.
	uint16_t getPlayer() const;
	//! Sets the id of the player sending the message.
	//!
	//! Setting this property also updates the checksum.
	//!
	//! @see Message::calculateChecksum()
	void setPlayer(uint16_t player);
	
	//! Gets the data that is sent. The value has little meaning on its own.
	uint16_t getData() const;
	
	//! Sets the payload data.
	//!
	//! The meaning of the payload can differ based on the player's id, and/or
	//! a sequence of bits at the start. This alos updates the checksum.
	//!
	//! @see Message::calculateChecksum()
	void setData(uint16_t data);
	
	//! Gets the time (in minutes) that the match will take.
	uint16_t getTime() const;
	//! Sets the payload data to be the time in minutes.
	//!
	//! @param time Time (in minutes) that the game should run.
	//! @see Message::setData(uint16_t data)
	void setTime(uint16_t time);
	
	//! Sets up the bits for start message (player 0, data 0).
	//!
	//! @see Message::setPlayer(uint16_t player)
	//! @see Message::setData(uint16_t data)
	void setStartMessage();
	//! Whether the message is a start command.
	bool isStartMessage() const;
	
	//! Whether the checksum matches the payload.
	bool isValid() const;

private:
	//! Gets the value of the bit at specified postion (counted from the MSB).
	//!
	//! @return value of bit at the specified position.
	bool bit(uint8_t position) const;
	
private:
	uint16_t internalMessage = 1 << 15;
	//! Sets the bits of the checksum based on the result of an exlusive or of 
	//! other bits in the message.
	void calculateChecksum();
};

//! Writes the message to an output stream for logging purposes.
//!
//! The format is written as "Message{XXXXXXXXXXXXXXXX}", where the X gets 
//! replaced by the value of the bit at the specified position.
//!
//! @param lhs Output stream to which to write the message.
//! @param rhs Message to write to the stream.
//! @return The outputstream in lhs, useful for chaining.
hwlib::ostream & operator<<(hwlib::ostream & lhs, const Message & rhs);

#endif // DEVICES_MESSAGE_HPP
