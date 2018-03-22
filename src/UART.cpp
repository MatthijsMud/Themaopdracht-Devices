#include "UART.hpp"

UART::sendMessage(const char* theMessage){
    messageReceiver >> theMessage;
}