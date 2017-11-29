


stm32 study(m-3)


how to read binary code 

arm-none-eabi-objdump -D <elf_object>
= all section data/code 표시
arm-none-eabi-objdump -d <elf_object>
= program code 표시
arm-none-eabi-objdump -tT <elf_object>
= all symbol 표시

arm-none-eabi-readelf -S <object>
= section header 추출
arm-none-eabi-readelf -l <object>
= program header table 추출
arm-none-eabi-readelf -s <object>
= symbol table 추출
arm-none-eabi-readelf -e <object>
= elf file header 추출
arm-none-eabi-readelf -r <object>
= 재배치 entry 추출
arm-none-eabi-readelf -d <ojbect>
= 동적 세그먼트 추출
