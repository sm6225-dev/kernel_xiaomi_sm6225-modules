/* SPDX-License-Identifier: GPL-2.0-only WITH Linux-syscall-note */
/*
 * Qualcomm compress offload extensions not present in mainline 5.15
 */
#ifndef __COMPRESS_PARAMS_COMPAT_H
#define __COMPRESS_PARAMS_COMPAT_H

#include <sound/compress_params.h>

/* Extra codec IDs from QC 4.19 kernel */
#ifndef SND_AUDIOCODEC_AC3
#define SND_AUDIOCODEC_AC3                   ((__u32) 0x00000015)
#endif
#ifndef SND_AUDIOCODEC_EAC3
#define SND_AUDIOCODEC_EAC3                  ((__u32) 0x00000019)
#endif
#ifndef SND_AUDIOCODEC_DTS
#define SND_AUDIOCODEC_DTS                   ((__u32) 0x00000018)
#endif
#ifndef SND_AUDIOCODEC_WMA_PRO
#define SND_AUDIOCODEC_WMA_PRO               ((__u32) 0x00000017)
#endif
#ifndef SND_AUDIOCODEC_DSD
#define SND_AUDIOCODEC_DSD                   ((__u32) 0x00000022)
#endif
#ifndef SND_AUDIOCODEC_TRUEHD
#define SND_AUDIOCODEC_TRUEHD                ((__u32) 0x00000024)
#endif
#ifndef SND_AUDIOCODEC_MP2
#define SND_AUDIOCODEC_MP2                   ((__u32) 0x00000013)
#endif
#ifndef SND_AUDIOCODEC_APTX
#define SND_AUDIOCODEC_APTX                  ((__u32) 0x00000020)
#endif
#ifndef SND_AUDIOCODEC_IEC61937
#define SND_AUDIOCODEC_IEC61937              ((__u32) 0x00000023)
#endif

/* Render mode */
#ifndef SNDRV_COMPRESS_RENDER_MODE_AUDIO_MASTER
#define SNDRV_COMPRESS_RENDER_MODE_AUDIO_MASTER 0
#endif
#ifndef SNDRV_COMPRESS_RENDER_MODE_STC_MASTER
#define SNDRV_COMPRESS_RENDER_MODE_STC_MASTER 1
#endif
#ifndef SNDRV_COMPRESS_RENDER_MODE_TTP
#define SNDRV_COMPRESS_RENDER_MODE_TTP 2
#endif

/* Clock recovery mode */
#ifndef SNDRV_COMPRESS_CLK_REC_MODE_NONE
#define SNDRV_COMPRESS_CLK_REC_MODE_NONE 0
#endif
#ifndef SNDRV_COMPRESS_CLK_REC_MODE_AUTO
#define SNDRV_COMPRESS_CLK_REC_MODE_AUTO 1
#endif

/* Timestamp flag */
#ifndef COMPRESSED_TIMESTAMP_FLAG
#define COMPRESSED_TIMESTAMP_FLAG 0x0001
#endif

/* QC-specific metadata keys for compressed offload */
#ifndef SNDRV_COMPRESS_RENDER_MODE
#define SNDRV_COMPRESS_RENDER_MODE     0x2000
#endif
#ifndef SNDRV_COMPRESS_CLK_REC_MODE
#define SNDRV_COMPRESS_CLK_REC_MODE    0x2001
#endif
#ifndef SNDRV_COMPRESS_RENDER_WINDOW
#define SNDRV_COMPRESS_RENDER_WINDOW   0x2002
#endif
#ifndef SNDRV_COMPRESS_START_DELAY
#define SNDRV_COMPRESS_START_DELAY     0x2003
#endif
#ifndef SNDRV_COMPRESS_ENABLE_ADJUST_SESSION_CLOCK
#define SNDRV_COMPRESS_ENABLE_ADJUST_SESSION_CLOCK 0x2004
#endif
#ifndef SNDRV_COMPRESS_ADJUST_SESSION_CLOCK
#define SNDRV_COMPRESS_ADJUST_SESSION_CLOCK 0x2005
#endif
#ifndef SNDRV_COMPRESS_IN_TTP_OFFSET
#define SNDRV_COMPRESS_IN_TTP_OFFSET   0x2006
#endif
#ifndef SNDRV_COMPRESS_PATH_DELAY
#define SNDRV_COMPRESS_PATH_DELAY      0x2007
#endif
#ifndef SNDRV_COMPRESS_DSP_POSITION
#define SNDRV_COMPRESS_DSP_POSITION    0x2008
#endif

/* Codec metadata struct (QC extension) */
struct snd_codec_metadata {
	__u32 length;
	__u32 offset;
	__u64 timestamp;
	__u32 reserved[4];
};

/*
 * In 5.15, struct snd_codec lost its .flags and .compr_passthr fields.
 * 4.19 layout: ...options, compr_passthr, flags, reserved[1]
 * 5.15 layout: ...options, reserved[3]
 */
#define snd_codec_get_flags(c) ((c)->reserved[1])
#define snd_codec_get_compr_passthr(c) ((c)->reserved[0])

/*
 * QC 4.19 extended WMA struct with decode params baked in.
 * 5.15 splits encode (snd_enc_wma) and decode (snd_dec_wma) structs.
 * We define a compat struct and accessor macros for code that references
 * the old combined layout through codec_options->wma.
 */
struct snd_enc_wma_qc {
	__u32 super_block_align;
	__u32 avg_bit_rate;
	__u32 bits_per_sample;
	__u32 channelmask;
	__u32 encodeopt;
	__u32 encodeopt1;
	__u32 encodeopt2;
};

/*
 * QC 4.19 flac_dec / vorbis_dec / alac structs.
 * 5.15 renamed flac_dec->flac_d, added separate decode structs.
 */
struct snd_dec_flac_qc {
	__u16 sample_size;
	__u16 min_blk_size;
	__u16 max_blk_size;
	__u16 min_frame_size;
	__u16 max_frame_size;
	__u16 reserved;
};

struct snd_dec_vorbis_qc {
	__u32 bit_stream_fmt;
};

struct snd_dec_alac_qc {
	__u32 frame_length;
	__u8  compatible_version;
	__u8  pb;
	__u8  mb;
	__u8  kb;
	__u32 max_run;
	__u32 max_frame_bytes;
	__u32 avg_bit_rate;
	__u32 channel_layout_tag;
	__u32 bit_depth;
};

struct snd_dec_ape_qc {
	__u16 compatible_version;
	__u16 compression_level;
	__u32 format_flags;
	__u32 blocks_per_frame;
	__u32 final_frame_blocks;
	__u32 total_frames;
	__u32 seek_table_present;
	__u16 bits_per_sample;
};

struct snd_dec_dsd_qc {
	__u32 blk_size;
};

struct snd_dec_aptx_qc {
	__u32 nap;
	__u32 uap;
	__u32 lap;
};

struct snd_dec_amrwbplus_qc {
	__u32 bit_stream_fmt;
};

/*
 * QC codec_options union with all the old fields.
 * Cast from the kernel's snd_codec_options at use sites.
 */
union snd_codec_options_qc {
	struct snd_enc_wma_qc wma;
	struct snd_enc_vorbis vorbis;
	struct snd_enc_real real;
	struct snd_enc_flac flac;
	struct snd_enc_generic generic;
	struct snd_dec_flac_qc flac_dec;
	struct snd_dec_vorbis_qc vorbis_dec;
	struct snd_dec_alac_qc alac;
	struct snd_dec_ape_qc ape;
	struct snd_dec_dsd_qc dsd_dec;
	struct snd_dec_aptx_qc aptx_dec;
	struct snd_dec_amrwbplus_qc amrwbplus;
} __attribute__((packed, aligned(4)));

/*
 * Cast helper: the kernel passes union snd_codec_options* but our code
 * needs the extended QC layout. The data arrives via ioctl from userspace
 * HAL (which uses the QC-extended struct), so the memory is big enough.
 */
#define QC_CODEC_OPTIONS(opts) ((union snd_codec_options_qc *)(opts))

#endif /* __COMPRESS_PARAMS_COMPAT_H */
