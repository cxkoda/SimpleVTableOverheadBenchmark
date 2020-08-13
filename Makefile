%.o: %.cpp
	g++ -c $< -o $@

main: main.o Derived1.o Derived2.o Pure.o
	g++ $^ -o $@

clean:
	rm *.o main