/** @file
*
*  Copyright (c) 2011, ARM Limited. All rights reserved.
*
*  This program and the accompanying materials
*  are licensed and made available under the terms and conditions of the BSD License
*  which accompanies this distribution.  The full text of the license may be found at
*  http://opensource.org/licenses/bsd-license.php
*
*  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
*  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
*
**/

#include <Uefi.h>

#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>

#include <Protocol/RealTimeClock.h>
#include <Protocol/EmbeddedExternalDevice.h>



EMBEDDED_EXTERNAL_DEVICE   *gTPS65950;
INT16                      TimeZone = EFI_UNSPECIFIED_TIMEZONE;

/**
  Returns the current time and date information, and the time-keeping capabilities
  of the hardware platform.

  @param  Time                  A pointer to storage to receive a snapshot of the current time.
  @param  Capabilities          An optional pointer to a buffer to receive the real time clock
  device's capabilities.

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval EFI_INVALID_PARAMETER Time is NULL.
  @retval EFI_DEVICE_ERROR      The time could not be retrieved due to hardware error.

  **/
EFI_STATUS
EFIAPI
LibGetTime(
	OUT EFI_TIME                *Time,
	OUT EFI_TIME_CAPABILITIES   *Capabilities
)
{
	EFI_STATUS            Status;
	ASSERT(FALSE);
	return (Status == EFI_SUCCESS) ? Status : EFI_DEVICE_ERROR;
}

/**
  Sets the current local time and date information.

  @param  Time                  A pointer to the current time.

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval EFI_INVALID_PARAMETER A time field is out of range.
  @retval EFI_DEVICE_ERROR      The time could not be set due due to hardware error.

  **/
EFI_STATUS
EFIAPI
LibSetTime(
	IN EFI_TIME *Time
)
{
	EFI_STATUS Status;
	UINT8      Data;
	UINT8      MonthDayCount[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	EFI_TPL    OldTpl;
	ASSERT(FALSE);
	// Input validation according both to UEFI spec and hardware constraints
	// UEFI spec says valid year range is 1900-9999 but TPS only supports 2000-2099
	if ((Time == NULL)
		|| (Time->Year < 2000 || Time->Year > 2099)
		|| (Time->Month < 1 || Time->Month > 12)
		|| (Time->Day < 1 || Time->Day > MonthDayCount[Time->Month])
		|| (Time->Hour > 23)
		|| (Time->Minute > 59)
		|| (Time->Second > 59)
		|| (Time->Nanosecond > 999999999)
		|| ((Time->TimeZone < -1440 || Time->TimeZone > 1440) && Time->TimeZone != 2047)
		) {
		return EFI_INVALID_PARAMETER;
	}

	return (Status == EFI_SUCCESS) ? Status : EFI_DEVICE_ERROR;
}

/**
  Returns the current wakeup alarm clock setting.

  @param  Enabled               Indicates if the alarm is currently enabled or disabled.
  @param  Pending               Indicates if the alarm signal is pending and requires acknowledgement.
  @param  Time                  The current alarm setting.

  @retval EFI_SUCCESS           The alarm settings were returned.
  @retval EFI_INVALID_PARAMETER Any parameter is NULL.
  @retval EFI_DEVICE_ERROR      The wakeup time could not be retrieved due to a hardware error.

  **/
EFI_STATUS
EFIAPI
LibGetWakeupTime(
	OUT BOOLEAN     *Enabled,
	OUT BOOLEAN     *Pending,
	OUT EFI_TIME    *Time
)
{
	return EFI_UNSUPPORTED;
}

/**
  Sets the system wakeup alarm clock time.

  @param  Enabled               Enable or disable the wakeup alarm.
  @param  Time                  If Enable is TRUE, the time to set the wakeup alarm for.

  @retval EFI_SUCCESS           If Enable is TRUE, then the wakeup alarm was enabled. If
  Enable is FALSE, then the wakeup alarm was disabled.
  @retval EFI_INVALID_PARAMETER A time field is out of range.
  @retval EFI_DEVICE_ERROR      The wakeup time could not be set due to a hardware error.
  @retval EFI_UNSUPPORTED       A wakeup timer is not supported on this platform.

  **/
EFI_STATUS
EFIAPI
LibSetWakeupTime(
IN BOOLEAN      Enabled,
OUT EFI_TIME    *Time
)
{
	return EFI_UNSUPPORTED;
}

/**
  This is the declaration of an EFI image entry point. This can be the entry point to an application
  written to this specification, an EFI boot service driver, or an EFI runtime driver.

  @param  ImageHandle           Handle that identifies the loaded image.
  @param  SystemTable           System Table for this image.

  @retval EFI_SUCCESS           The operation completed successfully.

  **/
EFI_STATUS
EFIAPI
LibRtcInitialize(
	IN EFI_HANDLE                            ImageHandle,
	IN EFI_SYSTEM_TABLE                      *SystemTable
)
{
	EFI_STATUS    Status;
	EFI_HANDLE    Handle;
	UINT8         Data;
	EFI_TPL       OldTpl;

	DEBUG((EFI_D_ERROR, "RealTimeClockLib:LibRtcInitialize:RealTimeClock need impl!!!\n"));
	return Status;
}

/**
  Fixup internal data so that EFI can be call in virtual mode.
  Call the passed in Child Notify event and convert any pointers in
  lib to virtual mode.

  @param[in]    Event   The Event that is being processed
  @param[in]    Context Event Context
  **/
VOID
EFIAPI
LibRtcVirtualNotifyEvent(
	IN EFI_EVENT        Event,
	IN VOID             *Context
)
{
	DEBUG((EFI_D_ERROR, "RealTimeClockLib:LibRtcVirtualNotifyEvent need impl!!!\n"));
	return;
}
