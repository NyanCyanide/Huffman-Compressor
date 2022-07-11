@echo off
title Configuring File 
echo Configuring! Please Wait...
gcc -Wall "client.c" "encode.c" "decode.c" "huffman.c" -o "Huffman.exe"
echo.
echo Executable Created!
echo Usage: ./Huffman.exe __type__ __filepath__
echo.
echo For further information and documentation read README.md or visit https://github.com/NyanCyanide/Huffman-Compressor
echo.
powershell 
exit
