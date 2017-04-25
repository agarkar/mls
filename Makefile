CC = gcc
CFLAGS = -g -Wall
OBJECTS = myLs.o

mls : myLs.o
	@$(CC) $(CFLAGS) $(OBJECTS) -o mls
	@rm -rf *.o
	@echo -e "successfully compiled\nnow run :: make install"
	@echo -e "if you are not using bash....\n(substitute user) su to root and type make install_all"

install: myLs.o
	@echo "Installing"
	@./install
	@echo "Successfully installed"
	@echo -e "restart the shell/terminal/konsole\nenjoy.... :D"
	@echo "use mls custom command from any directory to use this utility"
	@rm -rf *.o

install_all :
	@echo "Installing"
	@cp mls /usr/bin
	@echo "Successfully installed"
	@echo -e "restart the shell/terminal/konsole\nenjoy.... :D"
	@echo "use mls custom command from any directory to use this utility"
	

myLs.o : myLs.c myLs.h
	@$(CC) $(CFLAGS) -c myLs.c

clean :
	@rm -rf mls
	@echo "cleaned..."
