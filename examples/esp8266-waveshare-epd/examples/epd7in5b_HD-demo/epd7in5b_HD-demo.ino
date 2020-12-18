#include "DEV_Config.h"
#include "EPD.h"
#include "GUI_Paint.h"
#include "imagedata.h"
#include <stdlib.h>

void setup() {
 
  DEV_Module_Init();
  printf("EPD_7IN5B_HD_test Demo\r\n");
  DEV_Delay_ms(50);
  printf("e-Paper Init and Clear...\r\n");
  EPD_7IN5B_HD_Init();
  EPD_7IN5B_HD_Clear();
  DEV_Delay_ms(200);
  //Create a new image cache
  UBYTE *Image;
  UWORD Imagesize = ((EPD_7IN5B_HD_WIDTH % 8 == 0) ? (EPD_7IN5B_HD_WIDTH / 8 ) : (EPD_7IN5B_HD_WIDTH / 8 + 1)) * EPD_7IN5B_HD_HEIGHT/2;
  if ((Image = (UBYTE *)malloc(Imagesize)) == NULL) {
    printf("Failed to apply for black memory...\r\n");
    while(1);
  }
  printf("NewImage:Image\r\n");
  Paint_NewImage(Image, 880, 264 , 0, WHITE);

  //Select Image
  Paint_SelectImage(Image);
  Paint_Clear(WHITE);
  
#if 1   // Drawing on the image
  /*Horizontal screen*/
  //1.Draw black image
  Paint_SelectImage(Image);
  Paint_Clear(WHITE);
  Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
  Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
  Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
  Paint_DrawPoint(10, 110, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
  Paint_DrawLine(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
  Paint_DrawLine(70, 70, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
  Paint_DrawRectangle(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawRectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawString_EN(10, 0, "waveshare", &Font16, BLACK, WHITE);
  Paint_DrawString_CN(10, 120, "微雪电子", &Font24CN, WHITE, BLACK);
  Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);  
  EPD_7IN5B_HD_Displaypart(Image,0,0,880,264,0);

  //2.Draw red image
  Paint_SelectImage(Image);
  Paint_Clear(WHITE);
  Paint_DrawCircle(160, 95, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawCircle(210, 95, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawLine(85, 95, 125, 95, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  Paint_DrawLine(105, 75, 105, 115, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  Paint_DrawString_CN(130, 0, "你好abc", &Font12CN, BLACK, WHITE);
  Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, BLACK);
  Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
  EPD_7IN5B_HD_Displaypart(Image,0,0,880,264,1);
  DEV_Delay_ms(3000);
 

  EPD_7IN5B_HD_Displaypart(gImage_7in5b_HD_b,135,145,240,240,0);
  EPD_7IN5B_HD_Displaypart(gImage_7in5b_HD_b,505,145,240,240,1);
  DEV_Delay_ms(3000);
  
#endif
  printf("Clear...\r\n");
  EPD_7IN5B_HD_Clear();
  printf("Goto Sleep...\r\n");
  EPD_7IN5B_HD_Sleep();
  free(Image);
  Image = NULL;
}

/* The main loop -------------------------------------------------------------*/
void loop()
{
  //
}
