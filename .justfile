@default:
    just --list --list-heading ''

# initial setup for project
setup:
    pio pkg update

# build the project
build:
    pio run

# generate compile_commands.json
compiledb:
    pio run --target compiledb

# upload the code to the device
upload:
    pio run --target upload

# monitor serial output
monitor:
    pio device monitor

# clean the project
clean:
    pio run --target clean

# disassemble firmware.elf
# asm:
#     cd {{ justfile_directory() }}/.pio/build/uno && pio pkg exec -- avr-objdump -S -D firmware.elf > firmware.asm
#

# test stuff
test:
    pio test --without-uploading

# intialize a vim editor based project
init-vim:
    pio project init --ide vim

# run all steps: build, upload, and monitor
all: build upload monitor
