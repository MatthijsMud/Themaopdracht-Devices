#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "hwlib.hpp"
#include <string>

class Screen{
	public:
		void GCHit(int lifes, int who);
		void GCCountdown(int countdown);
		void GCMain1(int lifes);
		void GCMain2(int timeleft);
    void gameParameterA();
    void gameParameterACustom(int numer);
    void gameParameterB();
    void gameParameterBCustom(int number);
		void gameParameterC();
		void gameParameterC1();
		void gameParameterC2();
		void gameParameterCCustom(int number);
    void initScreen();
    void flush();

	private:

    hwlib::target::pin_oc scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
    hwlib::target::pin_oc sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
    hwlib::i2c_bus_bit_banged_scl_sda i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );

    // use the buffered version
    hwlib::glcd_oled oled = hwlib::glcd_oled( i2c_bus, 0x3c );


    hwlib::window_part w1 = hwlib::window_part(
      oled,
      hwlib::location( 0, 0 ),
      hwlib::location( 128, 32));
    hwlib::window_part w2 = hwlib::window_part(
      oled,
      hwlib::location( 0, 32 ),
      hwlib::location( 128, 32));

      hwlib::font_default_16x16 f1 = hwlib::font_default_16x16();
      hwlib::window_ostream d1 = hwlib::window_ostream( w1, f1 );

      hwlib::font_default_8x8 f2 = hwlib::font_default_8x8();
      hwlib::window_ostream d2 = hwlib::window_ostream( w2, f2 );


			hwlib::window_ostream d3 = hwlib::window_ostream( w1, f2 );
			hwlib::window_ostream d4 = hwlib::window_ostream( w2, f2 );
};

#endif
