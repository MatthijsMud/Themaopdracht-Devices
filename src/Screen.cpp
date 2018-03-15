#include "Screen.hpp"

void Screen::test(){
  oled.clear();
  d1 << "\f"
      << "LASER \nshooter";
  d2 << "\f"
      << "==============\n"
      << "user: Wouter\n"
      << "score: " << 42 << "\n"
      << "==============\n";

      //Screen::flush();

}

void Screen::gameParameterA(){
  oled.clear();
  d1 << "\f"
      << "spelernr\n"
      << hwlib::flush;      //Screen::flush();
}

void Screen::gameParameterACustom(int number){
  oled.clear();
  //std::string s = std::to_string(number);
  //s = s + "\n"
  d1 << "\f"
      << "spelernr\n"
      << number << "\n"
      << hwlib::flush;
  d2 << "\f"
      <<"press B\n"

      << hwlib::flush;      //Screen::flush();
}

void Screen::gameParameterB(){
  oled.clear();
  d1 << "\f"
      << "Weapon\n"
      << hwlib::flush;      //Screen::flush();
}

void Screen::gameParameterBCustom(int number){
  oled.clear();
  //std::string s = std::to_string(number);
  //s=s+"\n";
  d1 << "\f"
      << "Weapon\n"
      << number << "\n"
      << hwlib::flush;
  d2 << "\f"
      << "confirm press * \n"
      << "reset press #"
      << hwlib::flush;      //Screen::flush();
}

void Screen::initScreen(){
  oled.clear();
  d1 << "\f"
      << "Press A\n"
      << "To start\n"
      << hwlib::flush;
      //Screen::flush();
}


void Screen::flush(){
  oled.flush();
}
