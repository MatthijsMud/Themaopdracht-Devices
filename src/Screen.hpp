#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "hwlib.hpp"
#include <string>

class Screen{
	public:
		//! screen for when the player is hit
		//! @param lifes the remaining lifes the player has
		//! @param who by who the player was shot
		void GCHit(int lifes, int who);

		//! countdown screen so the player can run away from the starting point
		//! @param countdown the remaining time the player can run away
		void GCCountdown(int countdown);

		//! upper half of the screen with the lifes
		//! @param lifes the remaining lifes
		void GCMain1(int lifes);

		//! bottom half of the screen with the remaining game time
		//! @param timeleft the remaing game time
		void GCMain2(int timeleft);

		//! screen for GameParameterController when key A is pressed
    void gameParameterA();

		//! screen for GameParameterController when key A is pressed
		//! @param number the playernumber the player pressed
    void gameParameterACustom(int numer);

		//! screen for GameParameterController when key B is pressed
    void gameParameterB();

		//! screen for GameParameterController when key B is pressed
		//! @param number the weaponstrength the player pressed
    void gameParameterBCustom(int number);

		//! screen for GameParameterController when key C is pressed
		void gameParameterC();

		//! screen for GameParameterController when key C is pressed
		void gameParameterC1();

		//! screen for GameParameterController when key C is pressed
		//! the number the player pressed
		void gameParameterC2();

		//! screen for GameParameterController when key C is pressed
		//! the gametime the player pressed
		void gameParameterCCustom(int number);

		//! initial screen when the arduino has started
    void initScreen();

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
