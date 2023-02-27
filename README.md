
Made uisng OpenGl and SDL2.

I am programming this on Clion which has OpenGL natively installed. You will need to get OpenGl for this program to work. You will also need SDL2, the link is below. 

Link to SDL2:
https://github.com/libsdl-org/SDL/releases/tag/release-2.26.3

For windows get the mingw version. 

If you are having compiler issues make sure your pathing and naming is correct under the CMakeLists.txt file.

Also I did a cheeky move where I put the SDL2.dll into my cmake folder to get around some pathing issues. So you might have an issue with that unless you do the same.
