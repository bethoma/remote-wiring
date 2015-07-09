/*
    Copyright(c) Microsoft Open Technologies, Inc. All rights reserved.

    The MIT License(MIT)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files(the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions :

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#include "pch.h"
#include "ServoControl.h"

using namespace Microsoft::Maker::Firmata;
//using namespace Microsoft::Maker::RemoteWiring;
using namespace Microsoft::Maker::RemoteWiring::Servo;


//******************************************************************************
//* Public Methods
//******************************************************************************

void
ServoControl::attach(
	uint8_t pin_,
	uint16_t minPulse_,
	uint16_t maxPulse_
	) 
{
	_firmata->lock();
	_firmata->beginSysex(static_cast<uint8_t>(SysexCommand::SERVO_CONFIG));
	_firmata->appendSysex(pin_);
	_firmata->appendSysex(minPulse_ & 0xFF);
	_firmata->appendSysex(minPulse_ >> 8);
	_firmata->appendSysex(maxPulse_ & 0xFF);
	_firmata->appendSysex(maxPulse_ >> 8);
	_firmata->endSysex();
	_firmata->unlock();
	_pin = pin_;
}

void
ServoControl::write(
	uint8_t value_
	) 
{
	_firmata->lock();
	_firmata->beginSysex(static_cast<uint8_t>(SysexCommand::EXTENDED_ANALOG));
	_firmata->appendSysex(value_);
	_firmata->endSysex();
	_firmata->unlock();
	_lastWrite = value_;
}


int
ServoControl::read()
{
	return _lastWrite;
}

bool
ServoControl::attached()
{
	//if (_device->_pin_mode[_pin] == 0x04)
	_device->setPinMode(PinMode::ANALOG);
	{
		return true;
	}
	return false;
}

//******************************************************************************
//* Private Methods
//******************************************************************************

