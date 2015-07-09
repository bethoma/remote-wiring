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

#pragma once
#include "RemoteDevice.h"

namespace Microsoft {
namespace Maker {
namespace RemoteWiring {

namespace Servo {

public ref class ServoControl sealed
{
public:

	ServoControl(
		RemoteWiring::RemoteDevice ^ device_
		) :
		_device( device_ )
	{
		_firmata = _device->_firmata;
	}

	void
	attach(
		uint8_t pin_,
		uint16_t minPulse_,
		uint16_t maxPulse_
	);

	void
	write(
		uint8_t value_
		);
	
	int
	read();

	bool
	attached();
	

private:
	
	//a reference to the device this servo is associated with
	RemoteWiring::RemoteDevice ^ _device;
	Firmata::UwpFirmata ^_firmata;

	uint8_t _pin;
	uint8_t _lastWrite;
};

} // namespace Servo
} // namespace RemoteWiring
} // namespace Maker
} // namespace Microsoft
