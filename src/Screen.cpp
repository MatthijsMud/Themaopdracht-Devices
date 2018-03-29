#include "Screen.hpp"

void Screen::GCCountdown(int countdown){
  oled.clear();
  d1 << "\f"
      << "RUN AWAY"
      << hwlib::flush;
  d2 << "\f"
      << countdown
      << hwlib::flush;
}

void Screen::GCHit(int lifes, int who){
  oled.clear();
  d1 << "\f"
      << "HIT"
      << hwlib::flush;
  d2 << "\f"
      << "by: " << who << "\n"
      << lifes << " lifes left"
      << hwlib::flush;
}

void Screen::GCMain1(int lifes){
  d1 << "\f"
      << lifes << " lifes"
      << hwlib::flush;
}
void Screen::GCMain2(int timeleft){
  d2 << "\f"
      << "remaining time \n"
      << timeleft << " minutes"
      << hwlib::flush;
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
      <<"press * to confirm\n"

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
      << "press * to confirm \n"
      << hwlib::flush;      //Screen::flush();
}

void Screen::gameParameterC(){
  oled.clear();
  //std::string s = std::to_string(number);
  //s=s+"\n";
  d1 << "\f"
      << "GameTime\n"
      << hwlib::flush;
}

void Screen::gameParameterCCustom(int number){
  oled.clear();
  //std::string s = std::to_string(number);
  //s=s+"\n";
  d1 << "\f"
      << "GameTime\n"
      << number << "\n"
      << hwlib::flush;
  d2 << "\f"
      << "confirm press # \n"
      << hwlib::flush;      //Screen::flush();
}

void Screen::gameParameterC1(){
  oled.clear();
  //std::string s = std::to_string(number);
  //s=s+"\n";
  d3 << "\f"
      << "press # to send \n"
      << "gametime" << "\n"
      << hwlib::flush;
  d4 << "\f"
      << "press * to send \n"
      << "startcommand" << "\n"
      << hwlib::flush;
}

void Screen::gameParameterC2(){
  oled.clear();
  //std::string s = std::to_string(number);
  //s=s+"\n";
  d3 << "\f"
      << "press * to send \n"
      << "startcommand" << "\n"
      << hwlib::flush;

}

void Screen::initScreen(){
  oled.clear();
  d3 << "\f"
      << "Press A\n"
      << "change player\n"
      << hwlib::flush;
  d4 << "\f"
      << "Press B\n"
      << "change weapon\n"
      << hwlib::flush;
      //Screen::flush();
}
