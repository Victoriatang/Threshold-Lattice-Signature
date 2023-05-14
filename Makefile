CC=g++ 
STRIP=strip
OBJ=test
OBJS=test1.cpp sign.cpp config.cpp poly.cpp polyvec.cpp ntt.cpp fips202.cpp intervaltest.cpp BitLTC1.cpp premul.cpp
CFLAGS= -Wall -g -lm 
$(OBJ):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
	$(STRIP) $@
$*.o:$%.c
	$(CC) $(CFLAGS) -c $< -o $@ 
.PHONY:clean
clean:
	$(RM) *.o test 