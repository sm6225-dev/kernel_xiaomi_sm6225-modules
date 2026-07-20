/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef __AUDIO_DAPM_COMPAT_H__
#define __AUDIO_DAPM_COMPAT_H__

#include <sound/soc-dapm.h>

#ifndef SND_SOC_DAPM_MICBIAS_E
#define SND_SOC_DAPM_MICBIAS_E(wname, wreg, wshift, winvert, wevent, wflags) \
{	.id = snd_soc_dapm_micbias, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshift, winvert), \
	.kcontrol_news = NULL, .num_kcontrols = 0, \
	.event = wevent, .event_flags = wflags}
#endif

#endif
