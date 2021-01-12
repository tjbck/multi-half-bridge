/**
 * @file        TLE94112-platf-ino.hpp
 * @brief       TLE94112-platf-ino.hpp Arduino Hardware Platforms
 * @date        Mai 2020
 * @version     2.0.0
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef TLE94112_PLATF_INO_HPP_
#define TLE94112_PLATF_INO_HPP_

#include "../../../config/tle94112-conf.hpp"

#if (TLE94112_FRAMEWORK == TLE94112_FRMWK_ARDUINO)

#include "../pal/TLE94112-pal-ino.hpp"

/**
 * @addtogroup platfIno
 * @{
 *
 * @brief Arduino Hardware Platform Pins
 * 
 * This class provides a simple API for connecting the TLE94112 shield via SPI.
 * The 12 halfbridges, the PWM units and the registers are set and controlled
 * from the library.
 */

/*!
 * Standard chip select pin for first TLE94112 shield
 */
#define TLE94112_PIN_CS1     10

/*!
 * Standard chip select pin for second TLE94112 shield
 * To use a second shield with different CS pin you have
 * to remove the 0 Ohm resistor R7 and solder it to R8
 */
#define TLE94112_PIN_CS2     9

/*!
 * Standard TLE94112 enable pin
 */
#define TLE94112_PIN_EN      8

#
class Tle94112Ino: virtual public TLE94112Ino
{
	public:
		//! \brief standard constructor with default pin assignment
		Tle94112Ino(void);

		/*!
		 * \brief constructor with individual pin assignment
		 *
		 * \param csPin  pin number of the CS pin
		 */
		Tle94112Ino(uint8_t csPin);

		//! \brief enables and initializes the TLE94112
		void begin(void);

		//! \brief deactivates all outputs and disables the TLE94112
		void end(void);

};
/** @} */

#endif /** TLE94112_FRAMEWORK **/
#endif /** TLE94112_PLATF_INO_HPP_ **/