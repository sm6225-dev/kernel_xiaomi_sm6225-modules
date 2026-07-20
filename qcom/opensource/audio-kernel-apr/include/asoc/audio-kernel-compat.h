/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef __AUDIO_KERNEL_COMPAT_H__
#define __AUDIO_KERNEL_COMPAT_H__

#include <sound/soc-component.h>

#ifndef snd_soc_component_read32
#define snd_soc_component_read32(component, reg) \
	snd_soc_component_read(component, reg)
#endif

#endif
