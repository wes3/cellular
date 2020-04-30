/*
 * Copyright 2020 u-blox Cambourne Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
    http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _CELLULAR_CFG_HW_PLATFORM_SPECIFIC_H_
#define _CELLULAR_CFG_HW_PLATFORM_SPECIFIC_H_

/* No #includes allowed here */

/* This header file contains hardware configuration information for
 * the u-blox C030-R412M board.
 */

/* ----------------------------------------------------------------
 * COMPILE-TIME MACROS FOR STM32F4: UART/USART
 * -------------------------------------------------------------- */

#ifndef CELLULAR_CFG_UART
/** The UART/USART HW block to use, a number between 1 and 8,
 * though only the USARTs (1, 2, 3 and 6) are capable of HW flow
 * control.
 */
# define CELLULAR_CFG_UART                           1
#endif

#ifndef CELLULAR_CFG_DMA
/** The DMA to use with the UART, either 1 or 2.
 */
# define CELLULAR_CFG_DMA                            1
#endif

#ifndef CELLULAR_CFG_DMA_STREAM
/** The stream of the given DMA to use, a number between 0 and 7.
 */
# define CELLULAR_CFG_DMA_STREAM                     0
#endif

#ifndef CELLULAR_CFG_DMA_CHANNEL
/** The channel of the given DMA to use, a number between 0 and 7.
 */
# define CELLULAR_CFG_DMA_CHANNEL                    0
#endif

#ifndef CELLULAR_CFG_RTS_THRESHOLD
/** The buffer threshold at which RTS is de-asserted, indicating the
 * cellular module should stop sending data to us.  Must be defined
 * if CELLULAR_CFG_PIN_RTS is not -1.
 */
# define CELLULAR_CFG_RTS_THRESHOLD                  100
#endif

/* ----------------------------------------------------------------
 * COMPILE-TIME MACROS FOR STM32F4: TIMx TIMER (USED FOR
 * RTOS TICK AND cellularPortGetTickTimeMs())
 * -------------------------------------------------------------- */

/** The TIMx TIMER instance to use.  Values can be 2, 3, 4, 5
 * or 7, others if you fiddle with the macro expansion of
 * CELLULAR_PORT_TIM_IRQ_N() in cellular_port_private.c
 * (because not all timer interrupts follow the same naming
 * convention).  Note that timers 1 and timers 8 to 11 are on
 * APB2, the rest on APB1, so if you have different clock
 * dividers on the two buses you will need to revisit
 * the numbers lower down.
 */
#ifndef CELLULAR_PORT_TICK_TIMER_INSTANCE
# define CELLULAR_PORT_TICK_TIMER_INSTANCE           2
#endif

/** The ST32F437VG processor on the C030-R412M board is 
 * driven from an external 8 MHz clock which PLL_HSE_XTAL
 * is assumed to multiply up to a SYSCLK value of 168 MHz.
 * The APBx clock is assumed to divide by 4, so
 * APBxCLK is 42 MHz (noting that timers 1 and 8 to 11 are on
 * APB2, the rest on APB1).  The prescaler for the APB timer
 * clocks (a 16 bit value) is then adjusted to give a 1 us
 * tick, so with a CELLULAR_PORT_TICK_TIMER_DIVIDER of
 * TIM_CLOCKDIVISION_DIV1 this is 42.  If your clocks are
 * different then the value of CELLULAR_PORT_TICK_TIMER_PRESCALER
 * (and, if necessary CELLULAR_PORT_TICK_TIMER_DIVIDER) should be
 * adjusted to obtain a 1 us tick.
 */
#ifndef CELLULAR_PORT_TICK_TIMER_PRESCALER
# define CELLULAR_PORT_TICK_TIMER_PRESCALER          42
#endif

/** If it is not possible to get enough range out of the
 * prescaler then this divider, possible values are:
 *
 * - 0      (TIM_CLOCKDIVISION_DIV1) for divide by 1
 * - 0x0100 (TIM_CR1_CKD_0) for divide by 2
 * - 0x0200 (TIM_CR1_CKD_1) for divide by 4
 */
#ifndef CELLULAR_PORT_TICK_TIMER_DIVIDER
# define CELLULAR_PORT_TICK_TIMER_DIVIDER            0
#endif

/** The auto-reload value, the 16-bit value at which the
 * timer will restart its count.  This is set such that
 * the overflow interrupt occurs every millisecond, which is
 * used for the RTOS tick.
 */
#ifndef CELLULAR_PORT_TICK_TIMER_PERIOD_US
# define CELLULAR_PORT_TICK_TIMER_PERIOD_US           1000
#endif

/** The number of 1 ms RTOS ticks at which the more lazy
 * overflow counter is incremented, allowing us to keep
 * 64 bit time.
 */
#ifndef CELLULAR_PORT_TICK_TIMER_OVERFLOW_PERIOD_MS
# define CELLULAR_PORT_TICK_TIMER_OVERFLOW_PERIOD_MS 60000
#endif

/* ----------------------------------------------------------------
 * COMPILE-TIME MACROS FOR STM32F4: PINS
 * -------------------------------------------------------------- */

/** Note: on STM32F4 the pin numbering has the bank number in the
 * upper nibble and the pin number in the lower nibble, so pin 15
 * is also known as PA_15 with value 0x0f and pin 16 is also known
 * as PB_0 with value 0x10, etc.
 */

#ifndef CELLULAR_CFG_PIN_ENABLE_POWER
/** The STM32F4 GPIO output that enables power to the cellular module.
 * -1 because there is no such facility on a C030 board.
 */
# define CELLULAR_CFG_PIN_ENABLE_POWER      -1
#endif

#ifndef CELLULAR_CFG_PIN_PWR_ON
/** The STM32F4 GPIO output that that is connected to the PWR_ON pin of
 * the cellular module.
 */
# define CELLULAR_CFG_PIN_PWR_ON            0x4e // AKA PE_14
#endif

#ifndef CELLULAR_CFG_PIN_VINT
/** The STM32F4 GPIO input that is connected to the VInt pin of the
 * cellular module.
 * -1 is used where there is no such connection.
 */
# define CELLULAR_CFG_PIN_VINT              -1
#endif

#ifndef CELLULAR_CFG_PIN_TXD
/** The STM32F4 GPIO output pin that sends UART data to the cellular
 * module.
 */
# define CELLULAR_CFG_PIN_TXD               0x09 // AKA PA_9
#endif

#ifndef CELLULAR_CFG_PIN_RXD
/** The STM32F4 GPIO input pin that receives UART data from the cellular
 * module.
 */
# define CELLULAR_CFG_PIN_RXD               0x0a // AKA PA_10
#endif

#ifndef CELLULAR_CFG_PIN_CTS
/** The STM32F4 GPIO input pin that the cellular modem will use to
 * indicate that data can be sent to it.
 * -1 is used where there is no such connection.
 */
# define CELLULAR_CFG_PIN_CTS               0x0b // AKA PA_11
#endif

#ifndef CELLULAR_CFG_PIN_RTS
/** The STM32F4 GPIO output pin that tells the cellular modem that it
 * can send more data to the STM32F4 UART.
 * -1 is used where there is no such connection.
 * If this is *not* -1 then be sure to set up
 * CELLULAR_CFG_RTS_THRESHOLD also.
 */
# define CELLULAR_CFG_PIN_RTS               0x0c // AKA PA_12
#endif

#endif // _CELLULAR_CFG_HW_PLATFORM_SPECIFIC_H_

// End of file