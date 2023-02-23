# terminal-graphics
I wrote this thing because I had to use TurboC in college for an introduction to computer graphics class and I despise TurboC (for the lack of a vim mode, obviously). So I wrote this single header library (if you could even call it that) that exposes an 
interface identical to turboC's `graphics.h` but creates an SFML window and draws pixels to it instead.

## dependencies
You need to have SFML on your computer. If you're using a linux machine then it should already be in your package manager called something like
`libsfml-dev` or just `sfml`. Install it like you would with any other package.
If you're on macOS then you should be able to install it using homebrew: `brew install sfml`
If you're on windows, you'll have to manually install it by downloading the archive for either MSVC or mingw. Locating and linking libraries on windows is a bit tricky so just follow the instructions on [https://sfml-dev.org](sfml-dev.org).
