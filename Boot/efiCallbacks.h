#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t UINTN;

typedef UINTN EFI_STATUS;
 
typedef UINTN EFI_TPL;

typedef void* EFI_PVOID;
typedef void* EFI_HANDLE;

#define EFIAPI 
#define EFIERR(a) (a | ~(((EFI_STATUS)-1) >> 1))
#define EFI_ERROR(a) (a & ~(((EFI_STATUS)-1) >> 1))
#define EFI_NOT_READY EFIERR(6)

typedef struct {
	wchar_t ScanCode;
	wchar_t UnicodeChar;
} EFI_INPUT_KEY;

typedef EFI_STATUS (*EFI_TEXT_CLEAR_SCREEN)(void *This);
typedef EFI_STATUS (*EFI_TEXT_ENABLE_CURSOR)(void *This, uint8_t Visible);
typedef EFI_STATUS (*EFI_TEXT_SET_ATTRIBUTE)(void *This, UINTN Attribute);
typedef EFI_STATUS (*EFI_TEXT_STRING)(void *This, const wchar_t *String);
typedef EFI_STATUS (*EFI_TEXT_QUERY_MODE)(void *This, UINTN ModeNumber, UINTN *Columns, UINTN *Rows);
typedef EFI_STATUS (*EFI_TEXT_SET_CURSOR_POSITION)(void *This, UINTN Column, UINTN Row);

typedef EFI_STATUS (*EFI_INPUT_RESET)(void *This, bool ExtendedVerification);
typedef EFI_STATUS (*EFI_INPUT_READ_KEY)(void *This, EFI_INPUT_KEY *Key);

typedef EFI_TPL(EFIAPI *EFI_RAISE_TPL) (EFI_TPL NewTpl);
typedef void (EFIAPI *EFI_RESTORE_TPL) (EFI_TPL OldTpl);


typedef uint64_t EFI_PHYSICAL_ADDRESS;
typedef uint64_t EFI_VIRTUAL_ADDRESS;

typedef enum {
	AllocateAnyPages,
	AllocateMaxAddress,
	AllocateAddress,
	MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef enum {
	EfiReservedMemoryType,
	EfiLoaderCode,
	EfiLoaderData,
	EfiBootServicesCode,
	EfiBootServicesData,
	EfiRuntimeServicesCode,
	EfiRuntimeServicesData,
	EfiConventionalMemory,
	EfiUnusableMemory,
	EfiACPIReclaimMemory,
	EfiACPIMemoryNVS,
	EfiMemoryMappedIO,
	EfiMemoryMappedIOPortSpace,
	EfiPalCode,
	EfiPersistentMemory,
	EfiMaxMemoryType
} EFI_MEMORY_TYPE;

typedef struct {
	uint32_t Type;
	EFI_PHYSICAL_ADDRESS PhysicalStart;
	EFI_VIRTUAL_ADDRESS VirtualStart;
	uint64_t NumberOfPages;
	uint64_t Attribute;
} EFI_MEMORY_DESCRIPTOR;

typedef EFI_STATUS (EFIAPI *EFI_ALLOCATE_PAGES) (EFI_ALLOCATE_TYPE Type, EFI_MEMORY_TYPE MemoryType, UINTN Pages, EFI_PHYSICAL_ADDRESS *Memory);
typedef EFI_STATUS (EFIAPI *EFI_FREE_PAGES) (EFI_PHYSICAL_ADDRESS Memory, UINTN Pages);
typedef EFI_STATUS (EFIAPI *EFI_GET_MEMORY_MAP) (UINTN *MemoryMapSize, EFI_MEMORY_DESCRIPTOR *MemoryMap, UINTN *MapKey, UINTN *DescriptorSize, uint32_t *DescriptorVersion);
typedef EFI_STATUS (EFIAPI *EFI_ALLOCATE_POOL) (EFI_MEMORY_TYPE PoolType, UINTN Size, void **Buffer);
typedef EFI_STATUS (EFIAPI *EFI_FREE_POOL) (void *Buffer);


typedef void *EFI_EVENT;
typedef void (EFIAPI *EFI_EVENT_NOTIFY) (EFI_EVENT Event,void *Context);

typedef enum {
	TimerCancel,
	TimerPeriodic,
	TimerRelative
} EFI_TIMER_DELAY;

typedef EFI_STATUS (EFIAPI *EFI_CREATE_EVENT) (uint32_t Type, EFI_TPL NotifyTpl, EFI_EVENT_NOTIFY NotifyFunction, void *NotifyContext, EFI_EVENT *Event);
typedef EFI_STATUS (EFIAPI *EFI_SET_TIMER) (EFI_EVENT Event, EFI_TIMER_DELAY Type, uint64_t TriggerTime);
typedef EFI_STATUS (EFIAPI *EFI_WAIT_FOR_EVENT) (UINTN NumberOfEvents, EFI_EVENT *Event, UINTN *Index);
typedef EFI_STATUS (EFIAPI *EFI_SIGNAL_EVENT) (EFI_EVENT Event);
typedef EFI_STATUS (EFIAPI *EFI_CLOSE_EVENT) (EFI_EVENT Event);
typedef EFI_STATUS (EFIAPI *EFI_CHECK_EVENT) (EFI_EVENT Event);


typedef struct {
	uint32_t Data1;
	uint16_t Data2;
	uint16_t Data3;
	uint8_t Data4[8];
} EFI_GUID;

typedef enum {
	EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;

typedef enum {
	AllHandles,
	ByRegisterNotify,
	ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

typedef struct _EFI_DEVICE_PATH_PROTOCOL {
	uint8_t Type;
	uint8_t SubType;
	uint8_t Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_INSTALL_PROTOCOL_INTERFACE) (EFI_HANDLE *Handle, EFI_GUID *Protocol, EFI_INTERFACE_TYPE InterfaceType, void *Interface);
typedef EFI_STATUS (EFIAPI *EFI_REINSTALL_PROTOCOL_INTERFACE) (EFI_HANDLE Handle, EFI_GUID *Protocol, void *OldInterface, void *NewInterface);
typedef EFI_STATUS (EFIAPI *EFI_UNINSTALL_PROTOCOL_INTERFACE) (EFI_HANDLE Handle, EFI_GUID *Protocol, void *Interface);
typedef EFI_STATUS (EFIAPI *EFI_HANDLE_PROTOCOL) (EFI_HANDLE Handle, EFI_GUID *Protocol, void **Interface);
typedef EFI_STATUS (EFIAPI *EFI_REGISTER_PROTOCOL_NOTIFY) (EFI_GUID *Protocol, EFI_EVENT Event, void **Registration);
typedef EFI_STATUS (EFIAPI *EFI_LOCATE_HANDLE) (EFI_LOCATE_SEARCH_TYPE SearchType, EFI_GUID *Protocol, void *SearchKey, UINTN *BufferSize, EFI_HANDLE *Buffer);
typedef EFI_STATUS (EFIAPI *EFI_LOCATE_DEVICE_PATH) (EFI_GUID *Protocol, EFI_DEVICE_PATH_PROTOCOL **DevicePath, EFI_HANDLE *Device);
typedef EFI_STATUS (EFIAPI *EFI_INSTALL_CONFIGURATION_TABLE) (EFI_GUID *Guid, void *Table);


typedef EFI_STATUS (EFIAPI *EFI_IMAGE_LOAD) (bool BootPolicy, EFI_HANDLE ParentImageHandle, EFI_DEVICE_PATH_PROTOCOL *DevicePath, void *SourceBuffer, UINTN SourceSize, EFI_HANDLE *ImageHandle);
typedef EFI_STATUS (EFIAPI *EFI_IMAGE_START) (EFI_HANDLE ImageHandle, UINTN *ExitDataSize, uint16_t **ExitData);
typedef EFI_STATUS (EFIAPI *EFI_EXIT) (EFI_HANDLE ImageHandle, EFI_STATUS ExitStatus, UINTN ExitDataSize, uint16_t *ExitData);
typedef EFI_STATUS (EFIAPI *EFI_IMAGE_UNLOAD) (EFI_HANDLE ImageHandle);
typedef EFI_STATUS (EFIAPI *EFI_EXIT_BOOT_SERVICES) (EFI_HANDLE ImageHandle, UINTN MapKey);


typedef EFI_STATUS (EFIAPI *EFI_GET_NEXT_MONOTONIC_COUNT) (uint64_t *Count);
typedef EFI_STATUS (EFIAPI *EFI_STALL) (UINTN Microseconds);
typedef EFI_STATUS (EFIAPI *EFI_SET_WATCHDOG_TIMER) (UINTN Timeout, uint64_t WatchdogCode, UINTN DataSize, uint16_t *WatchdogData);

typedef EFI_STATUS (EFIAPI *EFI_CONNECT_CONTROLLER) (EFI_HANDLE ControllerHandle, EFI_HANDLE *DriverImageHandle, EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath, bool Recursive);
typedef EFI_STATUS (EFIAPI *EFI_DISCONNECT_CONTROLLER) (EFI_HANDLE ControllerHandle, EFI_HANDLE DriverImageHandle, EFI_HANDLE ChildHandle);


typedef struct {
	EFI_HANDLE AgentHandle;
	EFI_HANDLE ControllerHandle;
	uint32_t Attributes;
	uint32_t OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

typedef EFI_STATUS (EFIAPI *EFI_OPEN_PROTOCOL) (EFI_HANDLE Handle, EFI_GUID *Protocol, void **Interface, EFI_HANDLE AgentHandle, EFI_HANDLE ControllerHandle, uint32_t Attributes);
typedef EFI_STATUS (EFIAPI *EFI_CLOSE_PROTOCOL) (EFI_HANDLE Handle, EFI_GUID *Protocol, EFI_HANDLE AgentHandle, EFI_HANDLE ControllerHandle);
typedef EFI_STATUS (EFIAPI *EFI_OPEN_PROTOCOL_INFORMATION) (EFI_HANDLE Handle, EFI_GUID *Protocol, EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer, UINTN *EntryCount);


typedef EFI_STATUS (EFIAPI *EFI_PROTOCOLS_PER_HANDLE) (EFI_HANDLE Handle, EFI_GUID ***ProtocolBuffer, UINTN *ProtocolBufferCount);
typedef EFI_STATUS (EFIAPI *EFI_LOCATE_HANDLE_BUFFER) (EFI_LOCATE_SEARCH_TYPE SearchType, EFI_GUID *Protocol, void *SearchKey, UINTN *NoHandles, EFI_HANDLE **Buffer);
typedef EFI_STATUS (EFIAPI *EFI_LOCATE_PROTOCOL) (EFI_GUID *Protocol, void *Registration, void **Interface);
typedef EFI_STATUS (EFIAPI *EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES) (EFI_HANDLE *Handle, ...);
typedef EFI_STATUS (EFIAPI *EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES) (EFI_HANDLE Handle, ...);


typedef EFI_STATUS (EFIAPI *EFI_CALCULATE_CRC32) (void *Data, UINTN DataSize, uint32_t *Crc32);


typedef void (EFIAPI *EFI_COPY_MEM) (void *Destination, void *Source, UINTN Length);
typedef void (EFIAPI *EFI_SET_MEM) (void *Buffer, UINTN Size, uint8_t Value);
typedef EFI_STATUS (EFIAPI *EFI_CREATE_EVENT_EX) (uint32_t Type, EFI_TPL NotifyTpl, EFI_EVENT_NOTIFY NotifyFunction, const void *NotifyContext, const EFI_GUID *EventGroup, EFI_EVENT *Event);


struct EFI_GRAPHICS_OUTPUT_PROTOCOL;

typedef enum {
	PixelRedGreenBlueReserved8BitPerColor,
	PixelBlueGreenRedReserved8BitPerColor,
	PixelBitMask,
	PixelBltOnly,
	PixelFormatMax
} EFI_GRAPHICS_PIXEL_FORMAT;

typedef struct {
	uint32_t RedMask;
	uint32_t GreenMask;
	uint32_t BlueMask;
	uint32_t ReservedMask;
} EFI_PIXEL_BITMASK;

typedef struct {
	uint8_t Blue;
	uint8_t Green;
	uint8_t Red;
	uint8_t Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL;

typedef struct {
	uint32_t Version;
	uint32_t HorizontalResolution;
	uint32_t VerticalResolution;
	EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
	EFI_PIXEL_BITMASK PixelInformation;
	uint32_t PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef enum {
 EfiBltVideoFill,
 EfiBltVideoToBltBuffer,
 EfiBltBufferToVideo,
 EfiBltVideoToVideo,
 EfiGraphicsOutputBltOperationMax
} EFI_GRAPHICS_OUTPUT_BLT_OPERATION;

typedef EFI_STATUS (EFIAPI *EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE) (struct EFI_GRAPHICS_OUTPUT_PROTOCOL *This, uint32_t ModeNumber, UINTN *SizeOfInfo, EFI_GRAPHICS_OUTPUT_MODE_INFORMATION **Info);
typedef EFI_STATUS (EFIAPI *EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE) (struct EFI_GRAPHICS_OUTPUT_PROTOCOL *This, uint32_t ModeNumber);
typedef EFI_STATUS (EFIAPI *EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT) (struct EFI_GRAPHICS_OUTPUT_PROTOCOL *This, EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer, EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation, UINTN SourceX,
					UINTN SourceY, UINTN DestinationX, UINTN DestinationY, UINTN Width, UINTN Height, UINTN Delta);