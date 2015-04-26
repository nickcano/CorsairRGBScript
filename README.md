# CorsairRGBScript
CorsairRGBScript is an engine that enables control of Corsair RGB Keyboard lighting through a small Lua API. It currently only supports the K70 RGB Keyboard, but the K95 is an easy addition (I just don't have one to test with).

This is a small project that I did in a few hours, so there's likely to be bugs and missing features

## Usage
To use the application, simply drop a keyboard Lua script onto the executable (many example scripts are included).

**NOTE:** before using, you need to [install the libusb drivers](https://github.com/libusb/libusb/wiki/Windows#Driver_Installation).

## Building
If you're using Visual Studio 2010, it should build just fine.

I've included headers and libraries for both *libusb* and *Lua*, so you won't have to seek out the proper library versions and compile them yourself. **These are compiled by Visual Studio 2010, and you may have to recompile them if you're using something else**.

## Big Thanks
A big thanks to [Palmr](https://github.com/Palmr)! I used his [LibCorsairRGB](https://github.com/Palmr/LibCorsairRGB) as a foundation for interfacing with the keyboard. I only cleaned up the code, put it in OOP wrappers, and added a Lua engine around it.
