.PHONY: main clean

main:
	@echo ------------------------------------------------------------------------------------------------------------------------
	@echo creating an elf file through linking for arduino to process
	@echo ------------------------------------------------------------------------------------------------------------------------
	avr-gcc -mmcu=atmega328p -O2 -I include -o build/main.elf src/main.c drivers/temp.c drivers/usart.c drivers/drive.c drivers/millisMicrosDelay.c drivers/ultrasonic.c -Wl,-u,vfprintf -lprintf_flt -lm 
	@echo 
	@echo 
	@echo ------------------------------------------------------------------------------------------------------------------------
	@echo converting elf to hex file for arduino to execute
	@echo ------------------------------------------------------------------------------------------------------------------------
	avr-objcopy -O ihex build/main.elf build/main.hex
	@echo 
	@echo 
	@echo ------------------------------------------------------------------------------------------------------------------------
	@echo pushing code into the atmega328p
	@echo ------------------------------------------------------------------------------------------------------------------------
	avrdude -c arduino -p m328p -P COM4 -U build/main.hex

clean:
	rm -f build/*
