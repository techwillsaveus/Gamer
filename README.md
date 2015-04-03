# DIY Gamer Kit Arduino Library

This software is for the [DIY Gamer Kit](http://www.techwillsaveus.com/shop/diy-kits/diy-gamer-kit-arduino/).

The library is essential for using your DIY Gamer Kit to:

- Draw graphics on the screen
- Make animations
- Code apps and games

## Installation

1. Install Arduino if you haven't already (the Arduino IDE). You can follow the instructions on how to do that [here](http://www.techwillsaveus.com/resources/arduino-software/)

2. Download this library using [this](https://github.com/ivanmaeder/Gamer/archive/master.zip) link (or with the **Download ZIP** button in GitHub)

3. Extract the folder from the zip file and rename it to `Gamer`

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

The easiest way to test that the library has been successfully installed, follow these steps:

1. Open or restart the Arduino IDE

2. Got to **File &#8594; Examples &#8594; Gamer** and choose one of the example programs (e.g., **Snake**)

3. Click on the **Verify** button to compile the example, and if it complies correctly, you're good to go!

If the library is not installed properly you will probably get errors saying something like `Symbol not found`. In this case make sure you have unzipped the library correctly and put it in the correct folder.

## Games

The following games are included in the examples folder of this library:

- Breakout
- Flappy Bird
- Snake

## Contributions and Bug Fixes

For contributing to the library or the games, first checkout the `dev` branch. It contains the latest development version of the code.

We look at all pull requests on the this branch.

For instructions on making changes and submitting them as pull requests, see these resources:

- [Using pull requests](https://help.github.com/articles/using-pull-requests/)
- [Fork A Repo](https://help.github.com/articles/fork-a-repo/)