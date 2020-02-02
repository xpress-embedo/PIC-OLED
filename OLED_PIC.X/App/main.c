/*
 * @file i2.c
 * @author xpress_embedo
 * @date 1 Feb, 2020
 * 
 * @brief Main File of the Project
 *
 */

#include "main.h"
#include "OLED.h"

/* Local Variables */
static uint32_t millisecond = 0;

/* Local Function */
void timer0_init( void );
void system_init( void );

/* Start From Here*/
void main(void) 
{
  uint32_t timestamp = 0;
  system_init();
  OLED_ClearDisplay();
  OLED_Update();
  Delay_ms(1000);
  OLED_FillDisplay();
  OLED_Update();
  Delay_ms(1000);
  while(1);
  return;
}

/* Function Definitions */

/**
 * @breif Initialize the system
 */
void system_init( void )
{
  // Initialize 1ms Timer
  timer0_init ();
  // Initialize OLED
  OLED_Init ();
  Delay_ms(100);
}

/**
 * @brief Counts milliseconds till startup
 * @return This function returns the number of milliseconds elapsed till the 
 * system is powered up.
 */
uint32_t millis( void )
{
  uint32_t time = 0;
  GIE = 0;
  time = millisecond;
  GIE = 1;
  return time;
}

/**
 * @brief Initialize Timer0 Module to generate 1ms interrupt
 */
void timer0_init( void )
{
  // Code Generated Using mikroC Timer Calculator
  T0CON	= 0x88;
  TMR0H	= 0xD1;
  TMR0L = 0x20;
  ENABLE_INT();
  TMR0IE = 1;
}

/**
 * PIC18F Interrupt Service Routine
 */
void __interrupt() ISR_ROUTINE( void )
{
  if( TMR0IF )
  {
    TMR0IF = 0;
    TMR0H	= 0xD1;
    TMR0L = 0x20;
    millisecond++;
  }
}
