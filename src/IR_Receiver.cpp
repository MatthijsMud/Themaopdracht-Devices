#include "IR_Receiver.hpp"

bool IR_Receiver::getValue(){
   return tsop_signal.get() == 1;
}
