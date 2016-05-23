nesutils
========

nesutils is a collection of utilities programs for querying and
manipulating iNES files. Details about the iNES file format can
be found [here](http://wiki.nesdev.com/w/index.php/INES).

nes-head
--------

Usage:

    nes-head < ines-file.nes

This program reads an NES file and parses the header informaion.
This program takes no arguments.
The NES file is read from stdin.
The header information is written to stdout.

extract-chr
-----------

Usage:

    extract-chr [CHR-ROM index] < ines-file.nes > chr-data-file.chr

extract-chr extracts a single 8KB CHR-ROM segment from an iNES file.
The CHR-ROM index is optional. The default index is 0.
The iNES file is read from stdin.
The CHR-ROM data is written to stdout.


chr-to-bmp
----------

Usage:

    chr-to-bmp <chr-rom-filename> <pallette-filename> <MSB> [--grid] > bitmap.bmp

chr-to-bmp renders the tiles in the provided CHR-ROM file for display.
The first pattern table is displayed in a 128x128 square on the left.
The second pattern table is displayed in a 128x128 square on the right.

The CHR-ROM file should contain a raw dump of the 8KB CHR-ROM.
No header info should be included in the file.

The palette is just a text file with 16 hex numbers separate by whitespace.
The numbers are of the format 0xYY where YY must be from 00 to 3F.

MSB means the value of the 2 Most Significant Bits of the palette index.
These would be found in the Attribute Table or Sprite Table on the NES.
The MSB value must be 0, 1, 2, or 3.

If a sixth parameter is given, then the program will display a grid.
The grid can help one determine the boundaries of the tiles.
