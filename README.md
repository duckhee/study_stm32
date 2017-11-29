


stm32 study(m-3)


how to read binary code 

arm-none-eabi-objdump -D <elf_object>
= all section data/code 표시
arm-none-eabi-objdump -d <elf_object>
= program code 표시
arm-none-eabi-objdump -tT <elf_object>
= all symbol 표시

arm-none-eabi-readelf -S &lt;object&gt; <br>
= section header 추출<br>
arm-none-eabi-readelf -l '<object>'<br>
= program header table 추출<br>
arm-none-eabi-readelf -s &lt;object&gt;<br>
= symbol table 추출<br>
arm-none-eabi-readelf -e &lt;object&gt;<br>
= elf file header 추출<br>
arm-none-eabi-readelf -r &lt;object&gt;<br>
= 재배치 entry 추출<br>
arm-none-eabi-readelf -d &lt;object&gt;<br>
= 동적 세그먼트 추출<br>
