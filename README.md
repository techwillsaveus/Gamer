# DIY Gamer Kit Arduino Library

This software is for the [DIY Gamer Kit](http://www.techwillsaveus.com/shop/diy-kits/diy-gamer-kit-arduino/).

The library is essential for using your DIY Gamer Kit to:

- Draw graphics on the screen
- Make animations
- Code apps and games

## Installation

1. Install **Arduino 1.0.6** (at the moment newer versions of Arduino will **not** work!). You can get this software [here](http://arduino.cc/en/Main/OldSoftwareReleases)

2. Download this library using [this](https://github.com/ivanmaeder/Gamer/archive/master.zip) link

3. Unzip the library and rename the resulting folder to `Gamer` (if it's not already called `Gamer`)

4. Put the `Gamer` folder inside the Arduino libraries folder. The location of this folder will depend on your operating system:

	Operating System|Folder
	----------------|----------------------------------
	Windows         |`My Documents\Arduino\libraries`
	Mac OS X        |`Documents/Arduino/libraries`
	Linux           |`~/Documents/Arduino/libraries`

The exact folder on your computer may be a little different. That's OK.

Almost there!

To test that the library is set up correctly, follow the steps below.

### Testing Your Installation

The easiest way to test that the library has been successfully installed, is to follow these steps:

1. Open or restart the Arduino IDE (if Arduino was open when you installed the library, it **must** be restarted)

2. Got to **File &#8594; Examples &#8594; Gamer** and choose one of the example programs (e.g., **Snake**)

3. Click on the **Verify** button to compile the example, and if it compiles correctly (it should say "Done compiling"), you're good to go!

If the library is not installed properly you will probably get errors saying something like `Symbol not found`. In this case make sure you have unzipped the library correctly and put it in the correct folder.

## Games

The following games are included in the examples folder of this library:

- Breakout
- Flappy Bird
- Snake

## Contributions and Bug Fixes

For contributing to the library or games, first checkout the `dev` branch. It contains the latest development version of the code.

We look at all pull requests on the `dev` branch.

For anything else, write to us at `support@techwillsaveus.com`.