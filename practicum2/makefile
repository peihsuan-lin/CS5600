all: server rfs

server: server.c server_utils.c
	gcc server.c server_utils.c -o server

rfs: client.c command.c file_utils.c
	gcc client.c command.c file_utils.c -o rfs
clean:
	rm -f server rfs