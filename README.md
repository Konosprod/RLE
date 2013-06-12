RLE
===

Example of Run Length Encoding. It only works on strings.

## Compress

Give a text or a file to the program, and it will compress it. 

## Decompress

Give a text or a file which has been compressed, and it will decomrpess it.


## Representation

I chose the following representation:
- [2 < number of occurrence < 9]@[caracter]

The number of occurrence can only be less than 9, otherwise, the program will divide the number. For example:

YYYYYYYYYYYY

Will be represented as:

9@Y3@Y

If the number of occurrence is less than 2, then, we don't make any changement. Indeed, it will make the string bigger than the original:

YYAABBCC

2@Y2@A2@B2@C

The compression is usefull only when there are patterns repeted several times.



