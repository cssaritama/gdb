. ${srcdir}/emulparams/elf32bmip.sh

OUTPUT_FORMAT="elf32-littlemips"
BIG_OUTPUT_FORMAT="elf32-bigmips"
LITTLE_OUTPUT_FORMAT="elf32-littlemips"

TEXT_START_ADDR=0x0100000
ARCH=mips:5900
MACHINE=
MAXPAGESIZE=128
EMBEDDED=yes
DYNAMIC_LINK=FALSE

unset DATA_ADDR
SHLIB_TEXT_START_ADDR=0
unset GENERATE_SHLIB_SCRIPT
