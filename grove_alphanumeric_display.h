/* 
 * grove_alphanumeric_display.h
 * A library for Grove - grove_alphanumeric_display
 *
 * Copyright (c) 2018 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Jerry Yip
 * Create Time: 2018-06
 * Version    : 0.1
 * Change Log :
 * Copyright (c) 2018 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : downey 
 * Create Time: 2018-06
 * Version    : 1.1
 * Change Log :for digital tube development.
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __GROVE_QUAD_ALPHANUMERIC_DISPLAY_H__
#define __GROVE_QUAD_ALPHANUMERIC_DISPLAY_H__

//#include "I2Cdev.h"
#include <Arduino.h>
#include "HT16K33_driver.h"

// #define TYPE_4_DEFAULT_I2C_ADDR    0x75
#define TYPE_4_DEFAULT_I2C_ADDR    0x71
#define TYPE_2_DEFAULT_I2C_ADDR    0x70

#define MAX_BIG_BUFFER_SIZE         (8*20)   

#define MAX_TUBE_COUNT  4



typedef enum
{
    FIRST_TUBE = 1,
    SECOND_TUBE,
    THIRD_TUBE,
    FOURTH_TUBE,
}TubeNum;

typedef enum{
    TYPE_2,
    TYPE_4,
}TubeType_t;


typedef enum{
    CNT_2 = 2,
    CNT_4 = 4,
}TubeCnt_t;

class Seeee_Digital_Tube : public HT16K33 {

public:
    Seeee_Digital_Tube();

    void setTubeType(TubeType_t type,uint8_t addr = TYPE_2_DEFAULT_I2C_ADDR);

    void clear();
    /**@brief Display number,If the param-num's len less than 4,The tubes display static number,otherwise,it displays scroll number.
     * When it displays scroll number,the param interval is scrolling interval(ms) .. 
     * @param num the number to display.
     * @param interval :the interval of scroll number.
     * */
    void displayNum(uint32_t num,uint32_t interval = 0);

    /**@brief Display string,If the param-str's len less than 4,The tubes display static string,otherwise,it displays scroll string.
     * When it displays scroll string,the param interval is scrolling interval(ms) .. 
     * @param str the str to display.
     * @param interval :the interval of scroll string.
     * */
    void displayString(char *str,uint32_t interval = 0);
    /**@brief Display all part of digital tube. 
     * 
     * */
    void fulDisplay();

    
    /**@brief Clear _buffer,just clear. 
     * 
     * */
    void clearBuf();
    
    
    /**@brief Display the contents of _buffer. 
     * 
     * */
    void display();

    /**@brief Specify the display char of a digital tube. 
     * @param tube_num The number of tube ,total 4.
     * @param num ,The number to display
     * */
    void setTubeSingleChar(TubeNum tube_num,char c);

    /**@brief Specify the display number of a digital tube. 
     * @param tube_num The number of tube ,total 4.
     * @param num ,The number to display
     * */
    void setTubeSingleNum(TubeNum tube_num,char num);

    /**@brief Set two points status.
     * @prarm upper_on if true,the upper point light on ,otherwise turn off; 
     * @prarm lower_on if true,the upper point light on ,otherwise turn off; 
     * */
    void setPoint(bool first_dot,bool second_dot);
private:
    void display_one_tube(TubeNum tube_num,uint16_t value);
    void replace_bit12(TubeNum tube_num,bool bit1,bool bit2);
    void setTubeBuf(TubeNum tube_num,char byte);
    int get_char_index(char c);
    void shiftDisplay(char *origin_disp_buf,char new_item);
    // Low1 High1 Low2 High2 ... Low8 High8
    uint8_t _buffer[16]; 
    //uint8_t _big_buffer[MAX_BIG_BUFFER_SIZE];
    //uint16_t _cursor_start, _cursor_end, _cursor_steps;
    uint16_t _ms;
    //orientation_type_t _orientation;
    //int8_t _offset_x, _offset_y;
    bool isLegalToDisplay(char byte);

    TubeType_t _type;  
    TubeCnt_t  _tube_cnt;
    uint16_t *disp_font_p;
    
};

#endif //__GROVE_LED_MATRIX_DRIVER_HT16K33__