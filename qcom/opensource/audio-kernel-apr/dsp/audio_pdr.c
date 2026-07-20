// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2016-2017, The Linux Foundation. All rights reserved.
 * Ported to 5.15 PDR helper API
 */

#include <linux/module.h>
#include <linux/slab.h>
#include <linux/soc/qcom/pdr.h>
#include "audio_pdr.h"

#define AUDIO_SERVICE_NAME "avs/audio"
#define AUDIO_SERVICE_PATH "msm/adsp/audio_pd"

/* Values matching old service-notifier.h for audio_notifier.c compat */
#define SERVREG_NOTIF_SERVICE_STATE_DOWN_V01 0x0FFFFFFF
#define SERVREG_NOTIF_SERVICE_STATE_UP_V01   0x1FFFFFFF

static struct pdr_handle *audio_pdr_handle;
static struct pdr_service *audio_pdr_svc;
static struct notifier_block *audio_pdr_service_nb;

struct srcu_notifier_head audio_pdr_cb_list;

static void audio_pdr_status_cb(int state, char *service_path, void *priv)
{
	unsigned long pdr_state;
	unsigned long svc_opcode;

	switch (state) {
	case SERVREG_SERVICE_STATE_UP:
		pdr_state = AUDIO_PDR_FRAMEWORK_UP;
		svc_opcode = SERVREG_NOTIF_SERVICE_STATE_UP_V01;
		break;
	case SERVREG_SERVICE_STATE_DOWN:
	case SERVREG_SERVICE_STATE_EARLY_DOWN:
	default:
		pdr_state = AUDIO_PDR_FRAMEWORK_DOWN;
		svc_opcode = SERVREG_NOTIF_SERVICE_STATE_DOWN_V01;
		break;
	}

	if (audio_pdr_service_nb)
		audio_pdr_service_nb->notifier_call(audio_pdr_service_nb,
						    svc_opcode, NULL);

	srcu_notifier_call_chain(&audio_pdr_cb_list, pdr_state, NULL);
}

int audio_pdr_register(struct notifier_block *nb)
{
	if (nb == NULL) {
		pr_err("%s: Notifier block is NULL\n", __func__);
		return -EINVAL;
	}
	return srcu_notifier_chain_register(&audio_pdr_cb_list, nb);
}
EXPORT_SYMBOL(audio_pdr_register);

int audio_pdr_deregister(struct notifier_block *nb)
{
	if (nb == NULL) {
		pr_err("%s: Notifier block is NULL\n", __func__);
		return -EINVAL;
	}
	return srcu_notifier_chain_unregister(&audio_pdr_cb_list, nb);
}
EXPORT_SYMBOL(audio_pdr_deregister);

void *audio_pdr_service_register(int domain_id,
				 struct notifier_block *nb, int *curr_state)
{
	if ((domain_id < 0) || (domain_id >= AUDIO_PDR_DOMAIN_MAX)) {
		pr_err("%s: Invalid service ID %d\n", __func__, domain_id);
		return ERR_PTR(-EINVAL);
	}

	if (!audio_pdr_handle) {
		pr_err("%s: PDR handle not initialized\n", __func__);
		return ERR_PTR(-ENODEV);
	}

	audio_pdr_service_nb = nb;

	if (curr_state)
		*curr_state = SERVREG_NOTIF_SERVICE_STATE_DOWN_V01;

	return audio_pdr_handle;
}
EXPORT_SYMBOL(audio_pdr_service_register);

int audio_pdr_service_deregister(void *service_handle,
	struct notifier_block *nb)
{
	if (audio_pdr_service_nb == nb)
		audio_pdr_service_nb = NULL;
	return 0;
}
EXPORT_SYMBOL(audio_pdr_service_deregister);

static int __init audio_pdr_late_init(void)
{
	srcu_init_notifier_head(&audio_pdr_cb_list);

	audio_pdr_handle = pdr_handle_alloc(audio_pdr_status_cb, NULL);
	if (IS_ERR(audio_pdr_handle)) {
		pr_err("%s: pdr_handle_alloc failed %ld\n",
			__func__, PTR_ERR(audio_pdr_handle));
		audio_pdr_handle = NULL;
		srcu_notifier_call_chain(&audio_pdr_cb_list,
					 AUDIO_PDR_FRAMEWORK_DOWN, NULL);
		return -ENODEV;
	}

	audio_pdr_svc = pdr_add_lookup(audio_pdr_handle,
				       AUDIO_SERVICE_NAME,
				       AUDIO_SERVICE_PATH);
	if (IS_ERR(audio_pdr_svc)) {
		pr_err("%s: pdr_add_lookup failed %ld\n",
			__func__, PTR_ERR(audio_pdr_svc));
		pdr_handle_release(audio_pdr_handle);
		audio_pdr_handle = NULL;
		audio_pdr_svc = NULL;
		srcu_notifier_call_chain(&audio_pdr_cb_list,
					 AUDIO_PDR_FRAMEWORK_DOWN, NULL);
		return -ENODEV;
	}

	return 0;
}
module_init(audio_pdr_late_init);

static void __exit audio_pdr_late_exit(void)
{
	if (audio_pdr_handle)
		pdr_handle_release(audio_pdr_handle);
}
module_exit(audio_pdr_late_exit);

MODULE_DESCRIPTION("PDR framework driver");
MODULE_LICENSE("GPL v2");
