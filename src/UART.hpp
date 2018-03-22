#ifndef UART_HPP
#define UART_HPP

class UART {
private:
    hwlib::ostream & messageReceiver;
public: 
    UART(hwlib::ostream & messageStream) : messageReceiver{ messageStream }{}
    /*
    Requires PC counterpart to expect messages somehow from the defined COM port. 
    */
    void sendMessage(const char* theMessage); // send scores to PC
}

#endif