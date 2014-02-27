# Electric Imp Random Number demo

This is an illustrative demo of interfacing the Electric Imp with a website.

## Outline

When executed correctly, the following happens:

1. The device - Imp + Arduino - sends a message the Imp Agent every three seconds, asking for a random number.
2. The Imp Agent, on receiving that message, makes a GET request to a public webserver, and receives JSON in return.
3. The Agent sends a message to the Device, with the JSON bundled up as a Table object
4. On receiving that message, the Device spits the number out to its screen.

The functionality is not the point, given Squirrel's built in `rand()` function. The point is: we're making a query from a device to the internet and back again, using sensible protocols (HTTP, JSON, and a simple structure for the serial message). It can then be extended into other examples.

## Requirements

In terms of hardware, you'll need an Arduino Uno, an Imp placed inside a [Sparkfun Imp Shield](http://www.sparkfun.com/products/11401), and an [SPI OLED display](http://www.adafruit.com/products/661) to display the results.

It's assumed you know how to BlinkUp your Imp and get code across to it.

In terms of software, we use the Adafruit libraries for their OLED, and Steve Cogswell's [ArduinoSerialCommand](https://github.com/scogswell/ArduinoSerialCommand) library to process commands. (We use this because it offers a simple, straightforward and extensible protocol, rather than reading bytes by hand.)

The website is a small PHP page that serves up JSON - again, it could be a string, but this is more representative of a real-world usage (where there might be more data being transmitted.)

## Setup

Put the PHP file somewhere it can be accessed over the internet - either on a server with `mod_php` installed that you own, or executing on a local machine tunnelled to the internet via something like [ngrok](http://ngrok.com). Put the contents of `agent.nut` and `device.nut` into the appropriate panels in your Electric Imp IDE and build them - be sure to replace `example.com` with a webserver with your device in.

In terms of hardware, the SPI OLED is wired as in [Adafruit's own instructions](http://learn.adafruit.com/monochrome-oled-breakouts/wiring-128x32-spi-oled-display).

## Usage

"Ready" should appear on the screen. Once data starts flowing in, the screen will begin updating.

## Room for improvement

This assumes the http data is always correct; a try/catch loop in the `http` methods in the Squirrel code would make this much more robust. Similarly, the Serial code just hurls data down UART without necessarily considering if the Arduino's ready to receive.