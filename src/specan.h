/*
 * Copyright 2010 Michael Ossmann
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

/*
 * There is one channel per column of the display.  The radio is tuned to one
 * channel at a time and RSSI is displayed for that channel.
 */
#define NUM_CHANNELS 132

/*
 * wide mode (default): 44 MHz on screen, 333 kHz per channel
 * narrow mode: 6.6 MHz on screen, 50 kHz per channel
 */
#define WIDE 0
#define NARROW 1
#define ULTRAWIDE 2

/*
 * Normal IM-ME devices have a 26 MHz crystal, but
 * some of them are shipping with 27 MHz crystals.
 * Use this preprocessor macro to compensate if your
 * IMME is so afflicted. See this link for more info:
 * <http://madscientistlabs.blogspot.com/2011/03/fix-for-im-me-specan-frequency-offset.html>
 */
#ifndef FREQ_REF
#define FREQ_REF	(26000000)
#endif

/*
 * short mode (default): displays RSSI >> 2
 * tall mode: displays RSSI
 */
#define SHORT 0
#define TALL 1

/* vertical scrolling */
#define SHORT_STEP  16
#define TALL_STEP   4
#define MAX_VSCROLL 208
#define MIN_VSCROLL 0

/* frequencies in MHz */
#define DEFAULT_FREQ     915
#define WIDE_STEP        5
#define NARROW_STEP      1
#define ULTRAWIDE_STEP   10
#define WIDE_MARGIN      13
#define NARROW_MARGIN    3
#define ULTRAWIDE_MARGIN 42

/* frequency bands supported by device */
#define BAND_300 0
#define BAND_400 1
#define BAND_900 2

/* band limits in MHz */
#define MIN_300  281
#define MAX_300  361
#define MIN_400  378
#define MAX_400  481
#define MIN_900  749
#define MAX_900  962

/* band transition points in MHz */
#define EDGE_400 369
#define EDGE_900 615

/* VCO transition points in Hz */
#define MID_300  318000000
#define MID_400  424000000
#define MID_900  848000000

/*
 * The original channel spacing values were
 * all uniformally scaled by 0.99976 from the
 * values described in the readme. I've pulled
 * it out here for experimentation purposes.
 */
#ifndef SPACING_FUDGE
#define SPACING_FUDGE		(1.0)
#endif

/* channel spacing in Hz */
#define NARROW_SPACING		(u32)(50000*SPACING_FUDGE)	// 50kHz
#define WIDE_SPACING		(u32)(200000*SPACING_FUDGE)	// 200kHz
#define ULTRAWIDE_SPACING	(u32)(666667*SPACING_FUDGE)	// 667kHz

#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))

/* bitmaps */
static const u8 narrow_ruler[] = {
	0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02,
	0xFE, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02,
	0x3E, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02,
	0xFE, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02,
	0x3E, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02,
	0xFE, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02,
	0x3E, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02,
	0xFE, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02,
	0x3E, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02,
	0xFE, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02,
	0x3E, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02,
	0xFE, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02,
	0x3E, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02, 0x0E, 0x02,
	0xFE, 0x02, 0x0E, 0x02, 0x0E, 0x02
};

static const u8 wide_ruler[] = {
	0x02,
	0x0E, 0x02, 0x02, 0x02, 0x02, 0x0E, 0x02, 0x02, 0x02, 0x02,
	0x0E, 0x02, 0x02, 0x02, 0x02,
	0xFE, 0x02, 0x02, 0x02, 0x02, 0x0E, 0x02, 0x02, 0x02, 0x02,
	0x0E, 0x02, 0x02, 0x02, 0x02, 0x0E, 0x02, 0x02, 0x02, 0x02,
	0x0E, 0x02, 0x02, 0x02, 0x02,
	0x3E, 0x02, 0x02, 0x02, 0x02, 0x0E, 0x02, 0x02, 0x02, 0x02,
	0x0E, 0x02, 0x02, 0x02, 0x02, 0x0E, 0x02, 0x02, 0x02, 0x02,
	0x0E, 0x02, 0x02, 0x02, 0x02,
	0xFE, 0x02, 0x02, 0x02, 0x02, 0x0E, 0x02, 0x02, 0x02, 0x02,
	0x0E, 0x02, 0x02, 0x02, 0x02, 0x0E, 0x02, 0x02, 0x02, 0x02,
	0x0E, 0x02, 0x02, 0x02, 0x02,
	0x3E, 0x02, 0x02, 0x02, 0x02, 0x0E, 0x02, 0x02, 0x02, 0x02,
	0x0E, 0x02, 0x02, 0x02, 0x02, 0x0E, 0x02, 0x02, 0x02, 0x02,
	0x0E, 0x02, 0x02, 0x02, 0x02,
	0xFE, 0x02, 0x02, 0x02, 0x02, 0x0E, 0x02, 0x02, 0x02, 0x02,
	0x0E, 0x02, 0x02, 0x02, 0x02, 0x0E,
	/* extra to accommodate offset starting point */
	0x02, 0x02, 0x02, 0x02,
	0x0E, 0x02, 0x02, 0x02, 0x02,
	0x3E, 0x02, 0x02, 0x02, 0x02, 0x0E, 0x02, 0x02, 0x02, 0x02,
	0x0E, 0x02, 0x02, 0x02, 0x02, 0x0E
};

static const u8 ultrawide_ruler[] = {
	0x0E, 0x02, 0x02, 0x0E, 0x02, 0x02,
	0xFE, 0x02, 0x02, 0x0E, 0x02, 0x02, 0x0E, 0x02, 0x02,
	0x0E, 0x02, 0x02, 0x0E, 0x02, 0x02,
	0xFE, 0x02, 0x02, 0x0E, 0x02, 0x02, 0x0E, 0x02, 0x02,
	0x0E, 0x02, 0x02, 0x0E, 0x02, 0x02,
	0xFE, 0x02, 0x02, 0x0E, 0x02, 0x02, 0x0E, 0x02, 0x02,
	0x0E, 0x02, 0x02, 0x0E, 0x02, 0x02,
	0xFE, 0x02, 0x02, 0x0E, 0x02, 0x02, 0x0E, 0x02, 0x02,
	0x0E, 0x02, 0x02, 0x0E, 0x02, 0x02,
	0xFE, 0x02, 0x02, 0x0E, 0x02, 0x02, 0x0E, 0x02, 0x02,
	0x0E, 0x02, 0x02, 0x0E, 0x02, 0x02,
	0xFE, 0x02, 0x02, 0x0E, 0x02, 0x02, 0x0E, 0x02, 0x02,
	0x0E, 0x02, 0x02, 0x0E, 0x02, 0x02,
	0xFE, 0x02, 0x02, 0x0E, 0x02, 0x02, 0x0E, 0x02, 0x02,
	0x0E, 0x02, 0x02, 0x0E, 0x02, 0x02,
	0xFE, 0x02, 0x02, 0x0E, 0x02, 0x02, 0x0E, 0x02, 0x02,
	0x0E, 0x02, 0x02, 0x0E, 0x02, 0x02,
	0xFE, 0x02, 0x02, 0x0E, 0x02, 0x02
};

static const u8 update_order[] = {
	0,11,22,33,44,55,66,77,88,99,
	110,121,1,12,23,34,45,56,
	67,78,89,100,111,122,2,13,
	24,35,46,57,68,79,90,101,
	112,123,3,14,25,36,47,58,
	69,80,91,102,113,124,4,15,
	26,37,48,59,70,81,92,103,
	114,125,5,16,27,38,49,60,
	71,82,93,104,115,126,6,17,
	28,39,50,61,72,83,94,105,
	116,127,7,18,29,40,51,62,
	73,84,95,106,117,128,8,19,
	30,41,52,63,74,85,96,107,
	118,129,9,20,31,42,53,64,
	75,86,97,108,119,130,10,21,
	32,43,54,65,76,87,98,109,
	120,131,
};

/* Keeping track of all this for each channel allows us to tune faster. */
typedef struct {
	/* frequency setting */
	u8 freq2;
	u8 freq1;
	u8 freq0;
	
	/* frequency calibration */
	u8 fscal3;
	u8 fscal2;
	u8 fscal1;

	/* signal strength */
	u8 ss;
	u8 max;
} channel_info;

void clear();
void plot(u8 col);
void putchar(char c);
u8 getkey();
void draw_ruler();
void draw_freq();
void radio_setup();
void set_filter();
void set_radio_freq(u32 freq);
void calibrate_freq(u32 freq, u8 ch);
u16 set_center_freq(u16 freq);
void tune(u8 ch);
void set_width(u8 w);
void poll_keyboard();
void main(void);
