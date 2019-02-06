
trace2lxt: main.c lxt_write.c lxt2_write.c
	gcc -I. -Wall -Werror main.c lxt_write.c lxt2_write.c -lbz2 -lz -o trace2lxt

