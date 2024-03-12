/*
 * DIOLCFG.c
 *
 * Created: 8/26/2021 9:42:00 AM
 *  Author: Dell
 */ 

#include "DIO_INTERFACE.h"
const DIO_PinStatus_type PinsStatusArray[32]=
{
	
	OUTPUT,      /* Port A Pin 0 */
	OUTPUT,      /* Port A Pin 1 */
	OUTPUT,      /* Port A Pin 2 */
	OUTPUT,      /* Port A Pin 3 */
	OUTPUT,      /* Port A Pin 4 */
	OUTPUT,      /* Port A Pin 5 */
	OUTPUT,      /* Port A Pin 6 */
	OUTPUT,      /* Port A Pin 7 */
	OUTPUT,      /* Port B Pin 0  / */
	OUTPUT,      /* Port B Pin 1  /*/
	OUTPUT,		 /* Port B Pin 2  / INT2 */
	OUTPUT,		 /* Port B Pin 3  /  OC0 */
	INFREE,		 /* Port B Pin 4 / *SS *User defined in master case* */
	OUTPUT,		 /* Port B Pin 5 / MOSI *User defined in master case* */
	INFREE,		 /* Port B Pin 6 / MISO *User defined in slave case* */
	OUTPUT,		 /* Port B Pin 7 / SCK  *User defined in master case* */
	OUTPUT,		 /* Port C Pin 0 */
	OUTPUT,		 /* Port C Pin 1 */
	OUTPUT,		 /* Port C Pin 2 */
	OUTPUT,		 /* Port C Pin 3 */
	OUTPUT,		 /* Port C Pin 4 */
	OUTPUT,		 /* Port C Pin 5 */
	OUTPUT,		 /* Port C Pin 6 */
	OUTPUT,		 /* Port C Pin 7 */
	OUTPUT,		 /* Port D Pin 0 , RX*/
	OUTPUT,		 /* Port D Pin 1 , TX*/
    OUTPUT,      /* Port D Pin 2  / INT0  */
	OUTPUT,      /* Port D Pin 3  / INT1  */
	OUTPUT,		 /* Port D Pin 4  / OCR1B */
	INFREE,		 /* Port D Pin 5  / OCR1A */
	INFREE,		 /* Port D Pin 6  / ICP   */
	OUTPUT		 /* Port D Pin 7 */
};	