/*!
 * \file        Tle94112-pal-ino.cpp
 * \name        Tle94112-pal-ino.cpp - Arduino library to control Infineon's DC Motor Control Shield with Tle94112
 * \author      Infineon Technologies AG
 * \copyright   2019 Infineon Technologies AG
 * \version     1.5.0
 * \brief       This file has to be included in projects that use Infineon's DC Motor Control Shield with TLE94112
 * \ref         pal_arduino
 *
 * SPDX-License-Identifier: MIT
 *
 */


#include "TLE94112-pal-ino.hpp"

//SPI address commands
#define TLE94112_CMD_WRITE          0x80;
#define TLE94112_CMD_CLEAR          0x80;

#define TLE94112_STATUS_INV_MASK    (Tle94112::TLE_POWER_ON_RESET)

/*! \brief time in milliseconds to wait for chipselect signal raised */
#define TLE94112_CS_RISETIME        2

void Tle94112::writeReg(uint8_t reg, uint8_t mask, uint8_t shift, uint8_t data)
{
	uint8_t address = mCtrlRegAddresses[reg];
	uint8_t toWrite = mCtrlRegData[reg] & (~mask);
	toWrite |= (data << shift) & mask;
	mCtrlRegData[reg] = toWrite;
	
	address = address | TLE94112_CMD_WRITE
	cs->disable();
	uint8_t byte0 = mBus->transfer(address);
	uint8_t byte1 = mBus->transfer(toWrite);
	cs->enable();
	timer->delayMilli(TLE94112_CS_RISETIME);
}

uint8_t Tle94112::readStatusReg(uint8_t reg)
{
	//read the whole register
	return readStatusReg(reg, 0xFF, 0);
}

uint8_t Tle94112::readStatusReg(uint8_t reg, uint8_t mask, uint8_t shift)
{
	uint8_t address = mStatusRegAddresses[reg];

	cs->disable();
	uint8_t byte0 = mBus->transfer(address);
	uint8_t received = mBus->transfer(0xFF); //send dummy byte while receiving
	cs->enable();
	timer->delayMilli(TLE94112_CS_RISETIME);

	received = (received & mask) >> shift;
	
	return received;
}

void Tle94112::clearStatusReg(uint8_t reg)
{
	uint8_t address = mStatusRegAddresses[reg];

	address = address | TLE94112_CMD_CLEAR;
	cs->disable();
	uint8_t byte0 = mBus->transfer(address);
	uint8_t byte1 = mBus->transfer(0); //clear register by writing 0x00
	cs->enable();
	timer->delayMilli(TLE94112_CS_RISETIME);
}
