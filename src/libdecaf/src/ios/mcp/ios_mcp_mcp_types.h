#pragma once
#include "ios_mcp_config.h"
#include "ios_mcp_enum.h"

#include <cstdint>
#include <libcpu/be2_struct.h>
#include <common/structsize.h>

namespace ios::mcp
{

/**
 * \ingroup ios_mcp
 * @{
 */

#pragma pack(push, 1)

using MCPSysProdSettings = internal::SysProdConfig;
using MCPTitleId = uint64_t;

constexpr auto DefaultTitleId = static_cast<MCPTitleId>(-3);

struct MCPDevice
{
   //! Device type e.g. mlc, slc, usb
   be2_array<char, 8> type;

   //! This seems to be some 7 character unique identifier which is only set
   //! for mlc, ramdisk, usb
   be2_array<char, 128> unk0x08;

   //! Filesystem e.g. wfs, fat, isfs
   be2_array<char, 8> filesystem;

   //! Path, e.g. /vol/storage_mlc01
   be2_array<char, 0x27F> path;

   be2_val<MCPDeviceFlags> flags;

   //! Unique index - incrementing id in order of device added to system
   be2_val<uint32_t> uid;

   //! Device type index, e.g. 3 for /vol/storage_mlc03
   be2_val<uint32_t> index;
};
CHECK_OFFSET(MCPDevice, 0x00, type);
CHECK_OFFSET(MCPDevice, 0x08, unk0x08);
CHECK_OFFSET(MCPDevice, 0x88, filesystem);
CHECK_OFFSET(MCPDevice, 0x90, path);
CHECK_OFFSET(MCPDevice, 0x30F, flags);
CHECK_OFFSET(MCPDevice, 0x313, uid);
CHECK_OFFSET(MCPDevice, 0x317, index);
CHECK_SIZE(MCPDevice, 0x31B);

// Offsets of MCPTitleAppXml not verified.
struct MCPTitleAppXml
{
   be2_val<uint32_t> version;
   be2_val<uint64_t> os_version;
   be2_val<uint64_t> title_id;
   be2_val<uint16_t> title_version;
   be2_val<uint32_t> sdk_version;
   be2_val<uint32_t> app_type;
   be2_val<uint32_t> group_id;
   be2_array<uint8_t, 32> os_mask;
   be2_val<uint64_t> common_id;
};

struct MCPPPrepareTitleInfo
{
   struct Permission
   {
      be2_val<uint32_t> group;
      be2_val<uint64_t> mask;
   };

   be2_val<uint32_t> version;
   UNKNOWN(8);
   be2_val<MCPTitleId> titleId;
   be2_val<uint32_t> groupId;
   be2_val<uint32_t> cmdFlags;
   be2_array<char, 4096> argstr;
   be2_array<virt_ptr<char>, 64> argv;
   be2_val<uint32_t> max_size;
   be2_val<uint32_t> avail_size;
   be2_val<uint32_t> codegen_size;
   be2_val<uint32_t> codegen_core;
   be2_val<uint32_t> max_codesize;
   be2_val<uint32_t> overlay_arena;
   be2_val<uint32_t> num_workarea_heap_blocks;
   be2_val<uint32_t> num_codearea_heap_blocks;
   be2_array<Permission, 19> permissions;
   be2_val<uint32_t> default_stack0_size;
   be2_val<uint32_t> default_stack1_size;
   be2_val<uint32_t> default_stack2_size;
   be2_val<uint32_t> default_redzone0_size;
   be2_val<uint32_t> default_redzone1_size;
   be2_val<uint32_t> default_redzone2_size;
   be2_val<uint32_t> exception_stack0_size;
   be2_val<uint32_t> exception_stack1_size;
   be2_val<uint32_t> exception_stack2_size;
   be2_val<uint32_t> sdkVersion;
   be2_val<uint32_t> titleVersion;
   UNKNOWN(0x1270 - 0x124C);
};
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x00, version);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x0C, titleId);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x14, groupId);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x18, cmdFlags);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x1C, argstr);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x101C, argv);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x111C, max_size);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x1120, avail_size);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x1124, codegen_size);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x1128, codegen_core);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x112C, max_codesize);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x1130, overlay_arena);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x1134, num_workarea_heap_blocks);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x1138, num_codearea_heap_blocks);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x1220, default_stack0_size);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x1224, default_stack1_size);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x1228, default_stack2_size);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x122C, default_redzone0_size);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x1230, default_redzone1_size);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x1234, default_redzone2_size);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x1238, exception_stack0_size);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x123C, exception_stack1_size);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x1240, exception_stack2_size);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x1244, sdkVersion);
CHECK_OFFSET(MCPPPrepareTitleInfo, 0x1248, titleVersion);
CHECK_SIZE(MCPPPrepareTitleInfo, 0x1270);

struct MCPTitleListType
{
   be2_val<uint64_t> titleId;
   UNKNOWN(4);
   be2_array<char, 56> path;
   be2_val<MCPAppType> appType;
   UNKNOWN(0x54 - 0x48);
   be2_val<uint8_t> device;
   UNKNOWN(1);
   be2_array<char, 10> indexedDevice;
   be2_val<uint8_t> unk0x60;
};
CHECK_OFFSET(MCPTitleListType, 0x00, titleId);
CHECK_OFFSET(MCPTitleListType, 0x0C, path);
CHECK_OFFSET(MCPTitleListType, 0x44, appType);
CHECK_OFFSET(MCPTitleListType, 0x54, device);
CHECK_OFFSET(MCPTitleListType, 0x56, indexedDevice);
CHECK_OFFSET(MCPTitleListType, 0x60, unk0x60);
CHECK_SIZE(MCPTitleListType, 0x61);

struct MCPUpdateProgress
{
   UNKNOWN(0x38);
};
CHECK_SIZE(MCPUpdateProgress, 0x38);

#pragma pack(pop)

/** @} */

} // namespace ios::mcp
