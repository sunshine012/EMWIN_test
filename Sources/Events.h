/* ###################################################################
**     Filename    : Events.h
**     Project     : PE_Test
**     Processor   : MK70FN1M0VMJ15
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-04-08, 17:17, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "GPIO1.h"
#include "TU1.h"
#include "GPIO2.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "Bit1.h"
#include "Bit2.h"
#include "LCDC1.h"
#include "SM1.h"
#include "DMACH1.h"
#include "DMA1.h"
#include "Bit3.h"
#include "USB1.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  TU1_OnCounterRestart (module Events)
**
**     Component   :  TU1 [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void TU1_OnCounterRestart(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  AS1_OnError (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnError(void);

/*
** ===================================================================
**     Event       :  AS1_OnRxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnRxChar(void);

/*
** ===================================================================
**     Event       :  AS1_OnTxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnTxChar(void);

/*
** ===================================================================
**     Event       :  AS1_OnFullRxBuf (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnFullRxBuf(void);

/*
** ===================================================================
**     Event       :  AS1_OnFreeTxBuf (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnFreeTxBuf(void);

/*
** ===================================================================
**     Event       :  DMACH1_OnComplete (module Events)
**
**     Component   :  DMACH1 [DMAChannel_LDD]
*/
/*!
**     @brief
**         Called at the end of a DMA transfer. If the Half complete
**         property in initialization section is enabled, this event is
**         also called when current major iteration count reaches the
**         halfway point. See SetEventMask() and GetEventMask() methods.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void DMACH1_OnComplete(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  DMACH1_OnError (module Events)
**
**     Component   :  DMACH1 [DMAChannel_LDD]
*/
/*!
**     @brief
**         Called when error in channel settings is detected. See
**         SetEventMask() and GetEventMask() methods.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void DMACH1_OnError(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  USB1_OnHostDeviceDeattach (module Events)
**
**     Component   :  USB1 [USB_LDD]
*/
/*!
**     @brief
**         Called after the device has been successfully attached (see
**         OnResetRecovery() event) and the deattach condition is
**         detected,  OnDeattach() event is enabled and USB module is
**         enabled. See SetEventMask() and GetEventMask() methods.
**     @param
**         UserDataPtr     - User data pointer. This
**                           pointer is passed as the parameter of Init
**                           method.
*/
/* ===================================================================*/
void USB1_OnHostDeviceDeattach(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  USB1_OnHostResetRecovery (module Events)
**
**     Component   :  USB1 [USB_LDD]
*/
/*!
**     @brief
**         Called 10 ms later (reset recovery time) after the reset
**         signaling is stopped, OnResetRecovery() event is enabled and
**         USB module is enabled. See SetEventMask() and GetEventMask()
**         methods. As soon as this event is invoked attached device
**         can be accessed by the SendXX()/RecvXX() methods.
**     @param
**         UserDataPtr     - User data pointer. This
**                           pointer is passed as the parameter of Init
**                           method.
**     @param
**         CurrentSpeed    - Current device speed.
*/
/* ===================================================================*/
void USB1_OnHostResetRecovery(LDD_TUserData *UserDataPtr, LDD_USB_TBusSpeed CurrentSpeed);

/*
** ===================================================================
**     Event       :  USB1_OnHostResumeRecovery (module Events)
**
**     Component   :  USB1 [USB_LDD]
*/
/*!
**     @brief
**         Called 10 ms later (resume recovery time) after the resume
**         signaling is stopped, OnResumeRecovery() event is enabled
**         and USB module is enabled. See SetEventMask() and
**         GetEventMask() methods. As soon as this event is invoked
**         attached device can be accessed by the SendXX()/RecvXX()
**         methods.
**     @param
**         UserDataPtr     - User data pointer. This
**                           pointer is passed as the parameter of Init
**                           method.
*/
/* ===================================================================*/
void USB1_OnHostResumeRecovery(LDD_TUserData *UserDataPtr);

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
