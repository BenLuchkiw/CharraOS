#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "efiCallbacks.h"
#include "efiProtocols.h"
 
typedef struct {
	uint64_t Signature;
	uint32_t Revision;
	uint32_t HeaderSize;
	uint32_t CRC32;
	uint32_t Reserved;
} EFI_TABLE_HEADER;
 
typedef struct {
	uint32_t MaxMode;
	uint32_t Mode;
	uint32_t Attribute;
	uint32_t CursorColumn;
	uint32_t CursorRow;
	uint8_t  CursorVisible;
} SIMPLE_TEXT_OUTPUT_MODE;
 
typedef struct {
	EFI_PVOID                    Reset;
	EFI_TEXT_STRING              OutputString;
	EFI_PVOID                    TestString;
	EFI_TEXT_QUERY_MODE          QueryMode;
	EFI_PVOID                    SetMode;
	EFI_TEXT_SET_ATTRIBUTE       SetAttribute;
	EFI_TEXT_CLEAR_SCREEN        ClearScreen;
	EFI_TEXT_SET_CURSOR_POSITION SetCursorPosition;
	EFI_TEXT_ENABLE_CURSOR       EnableCursor;
	SIMPLE_TEXT_OUTPUT_MODE      *Mode;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
 
typedef struct {
	EFI_INPUT_RESET    Reset;
	EFI_INPUT_READ_KEY ReadKeyStroke;
	EFI_PVOID          WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef struct {
	EFI_TABLE_HEADER 							Hdr;

	// Task priority services
	EFI_RAISE_TPL 								RaiseTPL;
	EFI_RESTORE_TPL 							RestoreTPL;
	// Memory service
	EFI_ALLOCATE_PAGES 							AllocatePages;
	EFI_FREE_PAGES 								FreePages;
	EFI_GET_MEMORY_MAP 							GetMemoryMap;
	EFI_ALLOCATE_POOL							AllocatePool;
	EFI_FREE_POOL								FreePool;
	// Event and timer services
	EFI_CREATE_EVENT 							CreateEvent;
	EFI_SET_TIMER 								SetTimer;
	EFI_WAIT_FOR_EVENT							WaitForEvent;
	EFI_SIGNAL_EVENT 							SignalEvent;
	EFI_CLOSE_EVENT 							CloseEvent;
	EFI_CHECK_EVENT 							CheckEvent;
	// Protocol handler services
	EFI_INSTALL_PROTOCOL_INTERFACE 				InstallProtocolInterface;
	EFI_REINSTALL_PROTOCOL_INTERFACE 			ReinstallProtocolInterface;
	EFI_UNINSTALL_PROTOCOL_INTERFACE 			UninstallProtocolInterface;
	EFI_HANDLE_PROTOCOL 						HandleProtocol;
	void* 										Reserved;
	EFI_REGISTER_PROTOCOL_NOTIFY 				RegisterProtocolNotify;
	EFI_LOCATE_HANDLE 							LocateHandle;
	EFI_LOCATE_DEVICE_PATH 						LocateDevicePath;
	EFI_INSTALL_CONFIGURATION_TABLE 			InstallConfigurationTable;
	// Image services
	EFI_IMAGE_LOAD 								LoadImage;
	EFI_IMAGE_START 							StartImage;
	EFI_EXIT 									Exit;
	EFI_IMAGE_UNLOAD 							UnloadImage;
	EFI_EXIT_BOOT_SERVICES 						ExitBootServices;
	// Miscellaneous services
	EFI_GET_NEXT_MONOTONIC_COUNT 				GetNextMonotonicCount;
	EFI_STALL 									Stall;
	EFI_SET_WATCHDOG_TIMER 						SetWatchdogTimer;
	// Driver support services
	EFI_CONNECT_CONTROLLER 						ConnectController;
	EFI_DISCONNECT_CONTROLLER					DisconnectController;
	// Open and close protocol services
	EFI_OPEN_PROTOCOL 							OpenProtocol;
	EFI_CLOSE_PROTOCOL 							CloseProtocol;
	EFI_OPEN_PROTOCOL_INFORMATION 				OpenProtocolInformation;
	// Library services
	EFI_PROTOCOLS_PER_HANDLE 					ProtocolsPerHandle;
	EFI_LOCATE_HANDLE_BUFFER 					LocateHandleBuffer;
	EFI_LOCATE_PROTOCOL 						LocateProtocol;
	EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES 	InstallMultipleProtocolInterfaces;
	EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES 	UninstallMultipleProtocolInterfaces;
	// 32-bit CRC services
	EFI_CALCULATE_CRC32 CalculateCRC32;
	// Miscellaneous services
	EFI_COPY_MEM 								CopyMem;
	EFI_SET_MEM 								SetMem;
	EFI_CREATE_EVENT_EX 						CreateEventEx;
} EFI_BOOT_SERVICES;
 
typedef struct {
	EFI_TABLE_HEADER                Hdr;
	EFI_PVOID                       FirmwareVendor;
	uint32_t                        FirmwareRevision;
	EFI_PVOID                       ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *ConIn;
	EFI_PVOID                       ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
	EFI_PVOID                       StandardErrorHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
	void                            *RuntimeServices;
	EFI_BOOT_SERVICES               *BootServices;
	UINTN                           NumberOfTableEntries;
	void                            *ConfigurationTable;
} EFI_SYSTEM_TABLE;