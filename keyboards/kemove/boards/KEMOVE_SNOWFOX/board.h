/*
    ChibiOS - Copyright (C) 2020 Codetector <codetector@codetector.cn>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef BOARD_H
#define BOARD_H
/*
 * Setup for Snowfox
 */

/*
 * Board identifier.
 */
#define SNOWFOX
#define BOARD_NAME                  "KEMOVE Snowfox"

#ifndef LPC11U35
#define LPC11U35
#endif

/*
 * I/O
 */
#define LINE_LED                                        PAL_LINE(IOPORT0, 1)

#define LINE_USBCONN                                    PAL_LINE(IOPORT0, 6)
#define LINE_USBVBUS                                    PAL_LINE(IOPORT0, 3)

#define LINE_ROW1                                       PAL_LINE(IOPORT1, 25)
#define LINE_ROW2                                       PAL_LINE(IOPORT0, 20)
#define LINE_ROW3                                       PAL_LINE(IOPORT1, 4)
#define LINE_ROW4                                       PAL_LINE(IOPORT1, 20)
#define LINE_ROW5                                       PAL_LINE(IOPORT1, 24)
#define LINE_ROW6                                       PAL_LINE(IOPORT1, 19)
#define LINE_ROW7                                       PAL_LINE(IOPORT1, 17)
#define LINE_ROW8                                       PAL_LINE(IOPORT1, 23)

#define LINE_COL1                                       PAL_LINE(IOPORT1, 18)
#define LINE_COL2                                       PAL_LINE(IOPORT0, 7)
#define LINE_COL3                                       PAL_LINE(IOPORT1, 28)
#define LINE_COL4                                       PAL_LINE(IOPORT1, 5)
#define LINE_COL5                                       PAL_LINE(IOPORT1, 2)
#define LINE_COL6                                       PAL_LINE(IOPORT1, 8)
#define LINE_COL7                                       PAL_LINE(IOPORT0, 22)
#define LINE_COL8                                       PAL_LINE(IOPORT0, 11)
#define LINE_COL9                                       PAL_LINE(IOPORT1, 11)


#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
    void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
