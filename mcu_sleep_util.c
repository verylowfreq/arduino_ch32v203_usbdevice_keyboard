#include "ch32v20x.h"
#include "src/USB-Device-Keyboard/usb_pwr.h"


void MCU_Sleep_Wakeup_Operate( void )
{
    // EXTI_ClearFlag( EXTI_Line12 | EXTI_Line13 | EXTI_Line14 | EXTI_Line15 );
    // EXTI_ClearFlag( EXTI_Line4 | EXTI_Line5 | EXTI_Line6 | EXTI_Line7 );

//    printf( "Sleep\r\n" );
    __WFE( );
    
    // if( EXTI_GetFlagStatus( EXTI_Line12 | EXTI_Line13 | EXTI_Line14 | EXTI_Line15 ) != RESET  )
    // {
    //     EXTI_ClearFlag( EXTI_Line12 | EXTI_Line13 | EXTI_Line14 | EXTI_Line15 );
    //     Resume(RESUME_INTERNAL);
    // }
    // else if( EXTI_GetFlagStatus( EXTI_Line4 | EXTI_Line5 | EXTI_Line6 | EXTI_Line7 ) != RESET )
    // {
    //     EXTI_ClearFlag( EXTI_Line4 | EXTI_Line5 | EXTI_Line6 | EXTI_Line7 );
    //     Resume(RESUME_INTERNAL);
    // }
//    printf( "Wake\r\n" );
}
