/*
 * DatFont8x16.h
 *
 *  Created on: Jun 18, 2019
 *      Author: che
 */

#ifndef DATFONT8X16_H_
#define DATFONT8X16_H_


////////////////////////////////////////////////////////////////////////////////
//
// Defines.
//
////////////////////////////////////////////////////////////////////////////////

#define FONT8X16_WIDTH                               8   //!< font width
#define FONT8X16_HEIGHT                             16   //!< font height
#define FONT8X16_BYTES_PER_CHAR                     16   //!< bytes per character
#define FONT8X16_CHAR_OFFSET                        16   //!< offset to first character
#define FONT8X16_CHAR_COUNT                        224   //!< number of characters
#define FONT8X16_UNDERLINE                        0x40   //!< underline indicator

/** special characters */
#define FONT8X16_UPARROW                          0x10   //!< up arrow
#define FONT8X16_DOWNARROW                        0x11   //!< down arrow
#define FONT8X16_LEFTARROW                        0x12   //!< left arrow
#define FONT8X16_RIGHTARROW                       0x13   //!< right arrow
#define FONT8X16_PRINTER                          0x14   //!< printer symbol
#define FONT8X16_ENTER                            0x15   //!< enter symbol
#define FONT8X16_MENU                             0x16   //!< menu symbol
#define FONT8X16_NOTOKLEFT                        0x17   //!< not ok symbol left half
#define FONT8X16_NOTOKRIGHT                       0x18   //!< not ok symbol right half
#define FONT8X16_OKLEFT                           0x19   //!< ok symbol left half
#define FONT8X16_OKRIGHT                          0x1A   //!< ok symbol right half
#define FONT8X16_DEGREE                           0x1B   //!< degree symbol
#define FONT8X16_INTERNALBATTERYFULL              0x1C   //!< internal battery full symbol
#define FONT8X16_INTERNALBATTERYALMOSTEMPTY       0x1D   //!< internal battery almost symbol
#define FONT8X16_INTERNALBATTERYEMPTY             0x1E   //!< internal battery empty symbol
#define FONT8X16_BLOCK                            0x1F   //!< block symbol

////////////////////////////////////////////////////////////////////////////////
//
// Externals.
//
////////////////////////////////////////////////////////////////////////////////

extern const UINT8 Font8x16[ FONT8X16_CHAR_COUNT ][ FONT8X16_BYTES_PER_CHAR ];

#endif /* DATFONT8X16_H_ */
