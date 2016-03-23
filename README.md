## Not _another_ volume app!
I created this solely because the excellent [EventGhost](http://eventghost.org) automation tool is only able to adjust *speaker* volume by default due to Windows API limitations and their aim to be Windows 2000/XP compatible. This is a little annoying if you regularly use a remote control and headphones, whose volume you'd be unable to adjust using the remote.

Should work on Windows Vista and newer. Tested on Windows 7 and Windows 10.

## Usage
* `SetVolume` reports the current default playback device volume as a percentage
* `SetVolume <percent>` sets the current default playback device volume (0..100)
* `SetVolume +<percent>` increases default playback device volume by a specified percentage (0..100)
* `SetVolume -<percent>` decreases default playback device volume by a specified percentage (0..100)

## Building
1. Install [Microsoft Windows SDK for Vista](https://www.microsoft.com/en-us/download/details.aspx?id=14477)
2. Install Microsoft Visual Studio 2010
3. Get the source.
3. Build!

## Credits
Based on and inspired by [code shared by Larry Osterman](https://blogs.msdn.microsoft.com/larryosterman/2007/03/06/how-do-i-change-the-master-volume-in-windows-vista/) of Microsoft.
