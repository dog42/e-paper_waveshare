/**
  ******************************************************************************
  * @file    edp4in2.h
  * @author  Waveshare Team
  * @version V1.0.0
  * @date    23-January-2018
  * @brief   This file describes initialisation of 4.2 and 4.2b e-Papers
  *
  ******************************************************************************
  */

unsigned char lut_dc_4in2[] = 
{
    0x00, 0x17, 0x00, 0x00, 0x00, 0x02, 0x00, 0x17, 0x17, 0x00, 0x00, 
    0x02, 0x00, 0x0A, 0x01, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x0E, 0x00, 
    0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

//R21H
unsigned char lut_ww_4in2[] = 
{
    0x40, 0x17, 0x00, 0x00, 0x00, 0x02, 0x90, 0x17, 0x17, 0x00, 0x00, 0x02, 0x40, 0x0A, 
    0x01, 0x00, 0x00, 0x01, 0xA0, 0x0E, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

//R22H    r
unsigned char lut_bw_4in2[] =
{
    0x40, 0x17, 0x00, 0x00, 0x00, 0x02, 0x90, 0x17, 0x17, 0x00, 0x00, 0x02, 0x40, 0x0A, 
    0x01, 0x00, 0x00, 0x01, 0xA0, 0x0E, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

//R24H    b
unsigned char lut_bb_4in2[] =
{
    0x80, 0x17, 0x00, 0x00, 0x00, 0x02, 0x90, 0x17, 0x17, 0x00, 0x00, 0x02, 0x80, 0x0A, 
    0x01, 0x00, 0x00, 0x01, 0x50, 0x0E, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

//R23H    w
unsigned char lut_wb_4in2[] =
{
    0x80, 0x17, 0x00, 0x00, 0x00, 0x02, 0x90, 0x17, 0x17, 0x00, 0x00, 0x02, 0x80, 0x0A, 
    0x01, 0x00, 0x00, 0x01, 0x50, 0x0E, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


int EPD_Init_4in2() 
{
    EPD_Reset();
    
    EPD_SendCommand(0x01);//POWER_SETTING
    EPD_SendData(0x03);   // VDS_EN, VDG_EN
    EPD_SendData(0x00);   // VCOM_HV, VGHL_LV[1], VGHL_LV[0]
    EPD_SendData(0x2F);   // VDH
    EPD_SendData(0x2F);   // VDL
    EPD_SendData(0xFF);   // VDHR
    
    EPD_Send_3(0x06, 0x17, 0x17, 0x17);//BOOSTER_SOFT_START
    EPD_SendCommand(0x04);//POWER_ON
    EPD_WaitUntilIdle();
    
    EPD_Send_2(0x00, 0xBF, 0x0B);//PANEL_SETTING: // KW-BF   KWR-AF  BWROTP 0f
    EPD_Send_1(0x30, 0x3C);//PLL_CONTROL: 3A 100HZ, 29 150Hz, 39 200HZ, 31 171HZ

    EPD_Send_4(0x61, 1, 144, 1, 44);// RESOLUTION_SETTING: HI(W), LO(W), HI(H), LO(H)  
    EPD_Send_1(0x82, 0x12);// VCM_DC_SETTING                   
    EPD_Send_1(0x50, 0x97);// VCOM_AND_DATA_INTERVAL_SETTING: VBDF 17|D7 VBDW 97  VBDB 57  VBDF F7  VBDW 77  VBDB 37  VBDR B7

    EPD_lut(0x20,44,&lut_dc_4in2[0]);// LUT_FOR_VCOM
    EPD_lut(0x21,42,&lut_ww_4in2[0]);// LUT_WHITE_TO_WHITE   
    EPD_lut(0x22,42,&lut_bw_4in2[0]);// LUT_BLACK_TO_WHITE
    EPD_lut(0x23,42,&lut_wb_4in2[0]);// LUT_WHITE_TO_BLACK
    EPD_lut(0x24,42,&lut_bb_4in2[0]);// LUT_BLACK_TO_BLACK

    EPD_SendCommand(0x10);//DATA_START_TRANSMISSION_1  
    delay(2);
    for(int i = 0; i < 400*300; i++)EPD_SendData(0xFF);//Red channel

    EPD_SendCommand(0x13);//DATA_START_TRANSMISSION_2
    delay(2);
    return 0;
    
}

unsigned char lut_dc_4in2b[] = 
{
    0x00, 0x17, 0x00, 0x00, 0x00, 0x02, 0x00, 0x17, 0x17, 0x00, 0x00, 
    0x02, 0x00, 0x0A, 0x01, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x0E, 0x00, 
    0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

//R21H
unsigned char lut_ww_4in2b[] = 
{
    0x40, 0x17, 0x00, 0x00, 0x00, 0x02, 0x90, 0x17, 0x17, 0x00, 0x00, 0x02, 0x40, 0x0A, 
    0x01, 0x00, 0x00, 0x01, 0xA0, 0x0E, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

//R22H    r
unsigned char lut_bw_4in2b[] =
{
    0x40, 0x17, 0x00, 0x00, 0x00, 0x02, 0x90, 0x17, 0x17, 0x00, 0x00, 0x02, 0x40, 0x0A, 
    0x01, 0x00, 0x00, 0x01, 0xA0, 0x0E, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

//R24H    b
unsigned char lut_bb_4in2b[] =
{
    0x80, 0x17, 0x00, 0x00, 0x00, 0x02, 0x90, 0x17, 0x17, 0x00, 0x00, 0x02, 0x80, 0x0A, 
    0x01, 0x00, 0x00, 0x01, 0x50, 0x0E, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

//R23H    w
unsigned char lut_wb_4in2b[] =
{
    0x80, 0x17, 0x00, 0x00, 0x00, 0x02, 0x90, 0x17, 0x17, 0x00, 0x00, 0x02, 0x80, 0x0A, 
    0x01, 0x00, 0x00, 0x01, 0x50, 0x0E, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

int EPD_Init_4in2b() 
{
    EPD_Reset();
    EPD_Send_3(0x06,0x17,0x17,0x17);//BOOSTER_SOFT_START
    EPD_SendCommand(0x04);//POWER_ON
    EPD_WaitUntilIdle();
    EPD_Send_1(0x00, 0x0F);//PANEL_SETTING
    EPD_Send_1(0x50,0xF7);// VCOM_AND_DATA_INTERVAL_SETTING
    

    EPD_SendCommand(0x10);//DATA_START_TRANSMISSION_1  
    delay(2);
    return 0;
}
