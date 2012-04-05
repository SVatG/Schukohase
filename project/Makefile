# Binary name.
NAME = rainbows

# Object files, for the ARM9 binary and the ARM7 binary
OBJS = Main.o Truchet.o Radial.o Tunnel.o Pens.o ARM.o Drawing.o nitrofs.o \
       effect5.o effect6.o BoxBlock.o Loader.o VoxelBlock.o RainbowTable.o \
       DS3D/DS3D.o DS3D/Utils.o DS3D/Vector/VectorFixed.o \
       DS3D/Vector/MatrixFixed.o DS3D/Vector/QuaternionFixed.o \
			 effect7.o effect1.o effect2.o effect4.o effect0.o

OBJS7 = Main.arm7.o

#DEVKITPRO=../devkit/devkitPro

# Libraries to link into the respective binaries
LIBS = -L$(DEVKITPRO)/libnds/lib -lfat -lnds9 -lm -lmm9
LIBS7 = -L$(DEVKITPRO)/libnds/lib -lnds7 -lmm7

# Bitmaps, to be converted to .bin files by grit and then stored in the
# nitrofs under /gfx.
# This needs work so that the images are not remade every time the binary is
# compiled.
BITMAPS=gfx/aocubes.bin gfx/metaballs.bin gfx/unicorn.bin gfx/clouds.bin \
	gfx/svatg.bin gfx/bolder1.bin gfx/eis.bin gfx/kirsche.bin gfx/stars.bin

# Compiler setup
CC = $(DEVKITARM)/bin/arm-eabi-gcc
AS = $(DEVKITARM)/bin/arm-eabi-as
LD = $(DEVKITARM)/bin/arm-eabi-gcc

CFLAGS = -std=gnu99 -O3 -mcpu=arm9e -mtune=arm9e -ffast-math \
-mthumb -mthumb-interwork -I$(DEVKITPRO)/libnds/include -DARM9 $(DEFINES) \
-D__NITRO__ -DBINARY_NAME=\"$(NAME).nds\" -DDEBUG
CFLAGSARM = -std=gnu99 -Os -mcpu=arm9e -mtune=arm9e -ffast-math \
-marm -mthumb-interwork -I$(DEVKITPRO)/libnds/include -DARM9 $(DEFINES) \
-D__NITRO__ -DBINARY_NAME=\"$(NAME).nds\" -DDEBUG
CFLAGS7 = -std=gnu99 -O3 -ffast-math -fomit-frame-pointer -mcpu=arm7tdmi \
-mtune=arm7tdmi -mthumb -mthumb-interwork -I$(DEVKITPRO)/libnds/include -DARM7 $(DEFINES)
LDFLAGS = -specs=ds_arm9.specs -mthumb -mthumb-interwork -mno-fpu
LDFLAGS7 = -specs=./ds_arm7_.specs -mthumb -mthumb-interwork -mno-fpu

# Special rules for making png files into .bin files.
# Grit currently appends .img.bin, breaking this a little.
.SUFFIXES: .bin .png
.png.bin :
	$(DEVKITARM)/bin/grit $< -ftb -o$<

# Rules for the final binary
# Builds an NDS binary with a nitrofs file system with the files from /Datafiles
# in it appended.
$(NAME).nds: $(NAME).arm9 $(NAME).arm7
	$(DEVKITARM)/bin/grit gfx_source/pal_images/pal_reduced.png -gB8 -gb -ftb -ogfx/palette.png
	rm gfx/palette.img.bin
	cp gfx/*.bin Datafiles/gfx
	$(DEVKITARM)/bin/ndstool -c $@ -9 $(NAME).arm9 -7  ../devkit/devkitPro/libnds/default.arm7 -d Datafiles

# Arm9 / Arm7 binary rules
$(NAME).arm9: $(NAME).arm9.elf
	$(DEVKITARM)/bin/arm-eabi-objcopy -O binary $< $@

$(NAME).arm7: $(NAME).arm7.elf
	$(DEVKITARM)/bin/arm-eabi-objcopy -O binary $< $@

$(NAME).arm9.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

$(NAME).arm7.elf: $(OBJS7)
	$(LD) $(LDFLAGS7) -o $@ $(OBJS7) $(LIBS7)
Main.arm7.o: Main.arm7.c
	$(CC) $(CFLAGS7) -c -o $@ $<

Main.o: Main.c $(BITMAPS)

ARM.o: ARM.c
	$(CC) $(CFLAGSARM) -c -o $@ $<

# To clean, delete all binary objects and converted images
clean:
	rm -f $(NAME).nds $(NAME).arm9 $(NAME).arm7 $(NAME).arm9.elf $(NAME).arm7.elf $(OBJS) $(OBJS7) $(BITMAPS) gfx/*.c gfx/*.h gfx/*.bin *~ Datafiles/gfx/*

# Clean images only
cleanimages:
	rm -f $(BITMAPS) gfx/*.c gfx/*.h gfx/*.bin Datafiles/gfx/*

# Compile if neccesary and run in emulator
test: $(NAME).nds
	/usr/bin/wine $(DEVKITPRO)/nocash/NOCASH.EXE $(NAME).nds

run: $(NAME).nds
	open $(NAME).nds

install: $(NAME).nds
	cp $(NAME).nds /Volumes/NDS/
	hdiutil eject /Volumes/NDS/

# Send binary to flash card for testing on the system
todisk: $(NAME).nds
	/bin/rm -rf disk
	/bin/mkdir disk
	/usr/bin/sudo mount /dev/sdb1 disk
	/usr/bin/sudo cp $(NAME).nds disk/
	/bin/sleep 1
	/usr/bin/sudo umount disk
	/bin/rm -rf disk
