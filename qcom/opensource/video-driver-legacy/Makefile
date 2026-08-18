# SPDX-License-Identifier: GPL-2.0-only

KBUILD_OPTIONS += VIDEO_ROOT=$(KERNEL_SRC)/$(M)
KBUILD_OPTIONS += BOARD_PLATFORM=bengal
KBUILD_OPTIONS += CONFIG_ARCH_BENGAL=y
KBUILD_OPTIONS += CONFIG_MSM_VIDC_V4L2=m

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(M) modules $(KBUILD_OPTIONS)

modules_install:
	$(MAKE) INSTALL_MOD_STRIP=1 -C $(KERNEL_SRC) M=$(M) modules_install

%:
	$(MAKE) -C $(KERNEL_SRC) M=$(M) $@ $(KBUILD_OPTIONS)

clean:
	rm -f *.o *.ko *.mod.c *.mod.o *~ .*.cmd Module.symvers
	rm -rf .tmp_versions
