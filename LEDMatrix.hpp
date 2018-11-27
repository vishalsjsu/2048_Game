/*
 * LEDMatrix.hpp
 *
 *  Created on: November 11, 2018
 *      Author: Vishal
 */

#ifndef LEDMATRIX_HPP_
#define LEDMATRIX_HPP_

#include "gpio.hpp"
#include "singleton_template.hpp"
#include "stdio.h"

typedef struct {
    LPC1758_GPIO_Type A;
    LPC1758_GPIO_Type B;
    LPC1758_GPIO_Type C;
    LPC1758_GPIO_Type D;
    LPC1758_GPIO_Type E;

    LPC1758_GPIO_Type latch;
    LPC1758_GPIO_Type oe;
    LPC1758_GPIO_Type clk;

    LPC1758_GPIO_Type r1;
    LPC1758_GPIO_Type g1;
    LPC1758_GPIO_Type b1;
    LPC1758_GPIO_Type r2;
    LPC1758_GPIO_Type g2;
    LPC1758_GPIO_Type b2;
}LEDMatrixDisplayPincon;

enum Colors {
    Off,
    Red,
    Green,
    x1,
    Blue,
    Pink,
    x2,
    White
};

enum ColorPlanes {
    RedPlane,
    GreenPlane,
    BluePlane
};

class LEDMatrix : public SingletonTemplate<LEDMatrix> {
    public:
        LEDMatrix() {}
        friend class SingletonTemplate<LEDMatrix>;

        GPIO *A, *B, *C, *D, *E, *latch, *oe, *clk, *r1, *g1, *b1, *r2, *g2, *b2;
        uint64_t writeBuffer[64][3]; //Use this buffer for writing data into it
        uint64_t readBuffer[64][3];  //Use this buffer to read data from it and dump onto display

    public:
        void init(LEDMatrixDisplayPincon &);
        void enableDisplay();
        void disableDisplay();
        void enableLatch();
        void disableLatch();
        void clearFrameBuffers();
        void selectRow(uint8_t row);
        void clearPixel(int row, int col);
        void setPixel(int row, int col, Colors color);
        void setRowData(uint8_t row, Colors color, uint64_t = 0xFFFFFFFFFFFFFFFF);
        void setRowDataRaw(uint8_t row, ColorPlanes plane, uint64_t data);
        void fillFrameBuffer(uint64_t data, Colors color);
        void updateReadBuffer();
        void updateDisplay();
};

#endif /* LEDMATRIX_HPP_ */