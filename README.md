Compilation:

Make sure you are using a compiler that supports c++ 20 

Standard:

        mkdir build
        cd build
        cmake -S .. -B .
        cmake --build .

WebGL:

        mkdir build
        cd build
        emcmake cmake -S ../src -B .
        cmake --build .

Alternativately, if cmake does not work:

em++ main.cpp Krill/external/glad/src/glad.c -s USE_SDL=2 -s WASM=1 -s FULL_ES3=1 -o out.html --shell-file minimal.html
em++ main.cpp Krill/external/glad/src/glad.c -s USE_GLFW=3 -s WASM=1 -s FULL_ES3=1 -o out.html --shell-file minimal.html

