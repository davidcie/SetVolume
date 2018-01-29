## Not _another_ volume app!
I created this solely because the excellent [EventGhost](http://eventghost.org) automation tool is only able to adjust *speaker* volume by default due to Windows API limitations and their aim to be Windows 2000/XP compatible. This is a little annoying if you regularly use a remote control and headphones, whose volume you'd be unable to adjust using the remote.

Should work on Windows Vista and newer, tested on Windows 7 and Windows 10. You need to have a recent version of [Visual C++ libraries](https://support.microsoft.com/en-gb/help/2977003/the-latest-supported-visual-c-downloads) installed (Visual Studio 2015 or newer) but chances are if you have any software on your PC, these libraries will have already been installed by other programs.

## Usage
* `SetVolume` or `SetVolume help` displays usage information.
* `SetVolume get` reports current default playback device volume as a percentage.
* `SetVolume set <percent>` sets current default playback device volume to a percentage.
* `SetVolume set +<percent>` increases default playback device volume by a specified percentage.
* `SetVolume set -<percent>` decreases default playback device volume by a specified percentage.
* `SetVolume mute` mutes default playback device.
* `SetVolume unmute` unmutes default playback device.
* `SetVolume togglemute` toggles mute for default playback device.

## Building
1. Install Microsoft Visual Studio 2015
1. Get the source.
1. Open solution &ndash; you should be prompted to install Windows 8.1 SDK if you have not done so yet. (Do not worry, the 8.1 SDK is backwards compatible down to Vista.)
1. Build!

## Credits
Based on and inspired by [code shared by Larry Osterman](https://blogs.msdn.microsoft.com/larryosterman/2007/03/06/how-do-i-change-the-master-volume-in-windows-vista/) of Microsoft.
