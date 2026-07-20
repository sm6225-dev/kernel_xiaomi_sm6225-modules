/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef __REGMAP_SWR_H__
#define __REGMAP_SWR_H__

#include <linux/regmap.h>

struct swr_device;

extern struct regmap *__devm_regmap_init_swr(struct swr_device *swr,
		const struct regmap_config *config,
		struct lock_class_key *lock_key,
		const char *lock_name);

#ifndef devm_regmap_init_swr
#define devm_regmap_init_swr(swr, config) \
	__regmap_lockdep_wrapper(__devm_regmap_init_swr, #config, \
				swr, config)
#endif

#endif
