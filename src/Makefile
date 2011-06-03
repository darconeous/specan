# Copyright 2010 Travis Goodspeed, Michael Ossmann
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

CC = sdcc
LD = sdcc
CFLAGS	:= --no-pack-iram
LDFLAGS	:= --xram-loc 0xF000

all: specan.hex

install: specan.hex
	goodfet.cc erase
	goodfet.cc flash specan.hex

verify: specan.hex
	goodfet.cc verify specan.hex

clean:
	rm -f *.hex *.ihx *.rel *.asm *.lst *.rst *.sym *.lnk *.map *.mem

########################################
### Implicit Rules

%.rel : %.c
	$(CC) $(CFLAGS) -c $<

%.ihx: %.rel
	$(LD) $(LDFLAGS) $^

%.hex: %.ihx
	packihx <$< >$@

########################################
### Dependencies

display.rel : display.c display.h ioCCxx10_bitdef.h bits.h types.h 5x7.h
keys.rel : keys.c keys.h bits.h types.h
pm.rel : pm.c ioCCxx10_bitdef.h bits.h types.h
specan.rel: specan.c specan.h display.h keys.h pm.h ioCCxx10_bitdef.h
specan.ihx: specan.rel display.rel keys.rel pm.rel