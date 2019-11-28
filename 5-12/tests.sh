#!/bin/bash

function din () {
    echo "./out d $2";
    echo "$1" | ./out d $2;
}
function ein () {
    echo "./out e $2";
    echo "$1" | ./out e $2;
}
function out  () { printf "@$@\n\n"; }

printf "Test Suit"

echo "./out t $2";
echo "$1" | ./out t $2;


printf "?Input\n"
printf "!Result\n"
printf "@Expected\n\n"

printf "##########################\n"
printf "detab tests\n"
printf "##########################\n\n"

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
out "   H  e     l     l       o"


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


printf "##########################\n"
printf "entab tests\n"
printf "##########################\n\n"

ein "Hello"
out "Hello"

ein "        Hello"
out "#Hello"

ein "        Hello" "9 17"
out "#Hello"


ein "                Hello"
out "##Hello"
ein "                Hello" "9 17"
out "##Hello"

ein "       Hello"
out "       Hello"

ein "        Hello"
out "#Hello"

ein "         Hello"
out "# Hello"

ein "         Hello" "24"
out "#        Hello"

ein "         Hello" "4"
out "#      Hello"

ein "hello" "4"
out "hello"

ein "   Hello" "4"
out "#Hello"

ein "   H  e     l     l       o" "4 7 13 19"
out "#H#e#l#l#o"

#test tabstops too close
ein "   H  e     l     l    o" "4 7 13 19 20 24"
out "#H#e#l#l#o"

ein "Hello,  world"
out "Hello,#world"

ein "Hello, world" "8"
out "Hello,#world"

ein "Hello,  world" "9"
out "Hello,#world"

ein "Oh      world" "9"
ein "Oh      world"
out "Oh#world"

ein "Ohh     world" "9"
ein "Ohh     world"
out "Ohh#world"

ein "Ohhh    world" "9"
ein "Ohhh    world"
out "Ohhh#world"

ein "Ohhhh   world" "9"
ein "Ohhhh   world"
out "Ohhhh#world"

ein "Ohhhhh  world" "9"
ein "Ohhhhh  world"
out "Ohhhhh#world"

ein "Ohhhhhh world" "9"
ein "Ohhhhhh world"
out "Ohhhhhh#world"

ein "Ohhhhhhh        world" "9"
ein "Ohhhhhhh        world"
out "Ohhhhhhh#world"

ein "Ohhhhhhhh       world" "9"
ein "Ohhhhhhhh       world"
out "Ohhhhhhhh#world"
