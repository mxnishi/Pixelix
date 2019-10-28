/* MIT License
 *
 * Copyright (c) 2019 Andreas Merkle <web@blue-andi.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*******************************************************************************
    DESCRIPTION
*******************************************************************************/
/**
 * @brief  LED matrix
 * @author Andreas Merkle <web@blue-andi.de>
 */

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "LedMatrix.h"

/******************************************************************************
 * Compiler Switches
 *****************************************************************************/

/******************************************************************************
 * Macros
 *****************************************************************************/

/** Get number of array elements. */
#define ARRAY_NUM(__arr)    (sizeof(__arr) / sizeof((__arr)[0]))

/******************************************************************************
 * Types and classes
 *****************************************************************************/

/******************************************************************************
 * Prototypes
 *****************************************************************************/

/******************************************************************************
 * Local Variables
 *****************************************************************************/

/* Initialize LED matrix instance. */
LedMatrix LedMatrix::m_instance;

/** Pixel representation of the LED matrix */
static CRGB gMatrixBuffer[Board::LedMatrix::width * Board::LedMatrix::height];

/******************************************************************************
 * Public Methods
 *****************************************************************************/

/******************************************************************************
 * Protected Methods
 *****************************************************************************/

/******************************************************************************
 * Private Methods
 *****************************************************************************/

LedMatrix::LedMatrix() :
    FastLED_NeoMatrix(  gMatrixBuffer,
                        Board::LedMatrix::width,
                        Board::LedMatrix::height,
                        MATRIX_TYPE_DEFAULT)
{
    /* Setup LED matrix and limit max. power. */
    FastLED.addLeds<NEOPIXEL, Board::Pin::ledMatrixDataOutPinNo>(gMatrixBuffer, ARRAY_NUM(gMatrixBuffer)).setCorrection(TypicalLEDStrip);
    FastLED.setMaxPowerInVoltsAndMilliamps(Board::LedMatrix::supplyVoltage, Board::LedMatrix::supplyCurrentMax);
}

LedMatrix::~LedMatrix()
{
}

uint32_t LedMatrix::getColor(int16_t x, int16_t y)
{
    CRGB&       pixel   = gMatrixBuffer[XY(x, y)];
    uint32_t    red     = pixel.red;
    uint32_t    green   = pixel.green;
    uint32_t    blue    = pixel.blue;

    return (red << 16) | (green << 8) | (blue << 0);
}

/******************************************************************************
 * External Functions
 *****************************************************************************/

/******************************************************************************
 * Local Functions
 *****************************************************************************/
