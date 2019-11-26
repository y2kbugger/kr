#!/bin/bash

function din () {
    echo "./out d $2";
    echo "$1" | ./out d $2;
}
function ein () {
    echo "./out e $2";
    echo "$1@" | ./out e $2; 
}
function out  () { printf "@$@\n\n"; }

printf "Test Suit"

echo "./out t $2";
echo "$1" | ./out t $2;

exit

printf "?Input\n"
printf "!Result\n"
printf "@Expected\n\n"

printf "detab tests\n\n"

din "Hello"
out "Hello"

din "#Hello"
out "        Hello"
din "#Hello" "9 17"
out "        Hello"

din "##Hello"
out "                Hello"
din "##Hello" "9 17"
out "                Hello"

din "       Hello"
out "       Hello"

din "        Hello"
out "        Hello"

din "         Hello"
out "         Hello"

din "         Hello" "24"
out "         Hello"

din "         Hello" "4"
out "         Hello"

din "hello" "4"
out "hello"

din "#Hello" "4"
out "   Hello"
din "#H#e#l#l#o" "4 7 13 19"
out "   H  e     l     l        o"


#test tabstops too close
din "#H#e#l#l#o" "4 7 13 19 20 24"
out "   H  e     l     l    o"

din "Hello,#world"
out "Hello,  world"

din "Hello,#world" "8"
out "Hello, world"

din "Hello,#world" "9"
out "Hello,  world"

din "Oh#world" "9"
din "Oh#world"
out "Oh      world"

din "Ohh#world" "9"
din "Ohh#world"
out "Ohh     world"

din "Ohhh#world" "9"
din "Ohhh#world"
out "Ohhh    world"

din "Ohhhh#world" "9"
din "Ohhhh#world"
out "Ohhhh   world"

din "Ohhhhh#world" "9"
din "Ohhhhh#world"
out "Ohhhhh  world"

din "Ohhhhhh#world" "9"
din "Ohhhhhh#world"
out "Ohhhhhh world"

din "Ohhhhhhh#world" "9"
din "Ohhhhhhh#world"
out "Ohhhhhhh        world"

din "Ohhhhhhhh#world" "9"
din "Ohhhhhhhh#world"
out "Ohhhhhhhh       world"

exit

din "Hello, #world" "2 4 6 8 10 12 14 16 18"
out "Hello,   world"

din "	Hello, world"
out "        Hello, world"

din "	Hello, world" "2 2 2 2 2"
out "  Hello, world"

din "	Hello, world" "4 4 4 4 4"
out "    Hello, world"

din "		Hello, world"

din "		Hello, world"

din "		Hello, world"

din "    Hello, world"

din "     Hello, world"

din "      Hello, world"

din "       Hello, world"

din "        Hello, world"

din "         Hello, world"

din "          Hello, world"

din "           Hello, world"


printf "entab tests\n\n"

echo "Hello" | ./out e
printf "@Hello\n\n"

echo    "       Hello" | ./out e
printf "@       Hello\n\n"

echo    "        Hello" | ./out e
printf "@#Hello\n\n"

echo    "Hello, world" | ./out e
echo    "	Hello, world" | ./out e
echo    "		Hello, world" | ./out e
echo    "		Hello, world" | ./out e
echo    "		Hello, world" | ./out e
echo    "    Hello, world" | ./out e
echo    "     Hello, world" | ./out e
echo    "      Hello, world" | ./out e
echo    "       Hello, world" | ./out e
echo    "        Hello, world8" | ./out e
echo    "         Hello, world" | ./out e
echo    "          Hello, world" | ./out e
echo    "           Hello, world" | ./out e
