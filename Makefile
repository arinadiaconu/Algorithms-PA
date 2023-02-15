T1=walsh.cpp
T2=statistics.cpp
T3=prinel.cpp
T4=crypto.cpp
T5=regele.cpp

build:
	g++ -Wall -o walsh $(T1)
	g++ -Wall -o statistics $(T2)
	g++ -Wall -o prinel $(T3)
	g++ -Wall -o crypto $(T4)

run-p1:
	./walsh

run-p2:
	./statistics

run-p3:
	./prinel

run-p4:
	./crypto

run-p5:

clean:		
	rm -rf walsh
	rm -rf statistics
	rm -rf prinel
	rm -rf crypto