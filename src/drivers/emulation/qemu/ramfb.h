/* SPDX-License-Identifier: GPL-2.0-or-later */

#ifndef RAMFB_H
#define RAMFB_H

#include <stdint.h>

#define fourcc_code(a, b, c, d) ((u32)(a) | ((u32)(b) << 8) | \
                                ((u32)(c) << 16) | ((u32)(d) << 24))
#define DRM_FORMAT_XRGB8888 fourcc_code('X', 'R', '2', '4')

enum video_log2_bpp {
	VIDEO_BPP1	= 0,
	VIDEO_BPP2,
	VIDEO_BPP4,
	VIDEO_BPP8,
	VIDEO_BPP16,
	VIDEO_BPP32,
};

/*
 * Convert enum video_log2_bpp to bytes and bits. Note we omit the outer
 * brackets to allow multiplication by fractional pixels.
 */
#define VNBYTES(bpix)	((1 << (bpix)) / 8)

#define VNBITS(bpix)	(1 << (bpix))

enum video_format {
	VIDEO_UNKNOWN,
	VIDEO_RGBA8888,
	VIDEO_X8B8G8R8,
	VIDEO_X8R8G8B8,
	VIDEO_X2R10G10B10,
};

/* ramfb configuration details to read into etc/ramfb fw_cfg file */
typedef struct FwCfgRamfb {
	uint64_t addr;    /* Address of an allocated framebuffer */
	uint32_t fourcc;  /* Pixel format in Linux DRM fourcc code */
	uint32_t flags;   /* Unknown, appears unused */
	uint32_t width;   /* Width of the requested ramfb display */
	uint32_t height;  /* Height of the requested ramfb display */
	uint32_t stride;  /* Number of bytes per line? */
} __packed FwCfgRamfb;

void fw_cfg_ramfb_init(void);

#endif /* RAMFB_H */
