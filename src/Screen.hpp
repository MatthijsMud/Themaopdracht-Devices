#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "hwlib.hpp"
#include <string>

class Screen{
	public:
		void test();

    void gameParameterA();
    void gameParameterACustom(int);
    void gameParameterB();
    void gameParameterBCustom(int);
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
};

#endif
