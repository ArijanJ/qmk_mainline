VIA_ENABLE = yes
CONSOLE_ENABLE = yes
EXTRAKEY_ENABLE = yes
NKRO_ENABLE = yes

KEY_OVERRIDE_ENABLE = yes

# MACCEL
MACCEL_VIA_ENABLE = no
SRC += ./maccel/maccel.c
ifeq ($(strip $(VIA_ENABLE)), yes)
	ifeq ($(strip $(MACCEL_VIA_ENABLE)), yes)
		SRC += ./maccel/maccel_via.c
	endif
endif
OPT_DEFS += -DMACCEL_ENABLE
