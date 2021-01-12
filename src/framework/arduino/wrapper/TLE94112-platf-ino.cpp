/**
 * @file        TLE94112-platf-ino.cpp
 * @brief       TLE94112-platf-ino.cpp Arduino Hardware Platforms
 * @date        Mai 2020
 * @version     2.0.0
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "TLE94112-platf-ino.hpp"

#if (TLE94112_FRAMEWORK == TLE94112_FRMWK_ARDUINO)


Tle94112Ino::Tle94112Ino(void):Tle94112()
{
	Tle94112Ino(TLE94112_PIN_CS1);
}

Tle94112Ino::Tle94112Ino(uint8_t csPin):Tle94112()
{
	Tle94112::en = new GPIOIno(TLE94112_PIN_EN, OUTPUT, GPIOIno::POSITIVE );
	Tle94112::cs = new GPIOIno(csPin, OUTPUT, GPIOIno::POSITIVE );
	Tle94112::timer = new TimerIno();
	Tle94112::sBus = new SPICIno();
}

void Tle94112Ino::begin(void)
{
	mEnabled = false;
	Tle94112::sBus->init();
	Tle94112::en->init();
	Tle94112::en->enable();
	Tle94112::cs->init();
	Tle94112::cs->enable();
	Tle94112::timer->init();
	mEnabled = true;
	init();
}

void Tle94112Ino::end(void)
{
	mEnabled = false;
	Tle94112::en->disable();
	Tle94112::cs->disable();
	Tle94112::timer->stop();
	Tle94112::sBus->deinit();
}

#endif /** TLE94112_FRAMEWORK **/
