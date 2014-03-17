TestCore: TestCore.c++ Vector.c++ Resource.c++ Reporter.c++ Clock.c++ Lexer.c++ Parser.c++ Token.c++ Variant.c++ Util.c++ Environment.c++ System.c++ Script.c++
	g++ -pedantic -Wall TestCore.c++ Vector.c++ Resource.c++ Reporter.c++ Clock.c++ Lexer.c++ Parser.c++ Token.c++ Variant.c++ Util.c++ Environment.c++ System.c++ Script.c++ -o TestCore \
      -framework SDL2 -framework SDL2_image -framework SDL2_mixer -lgtest -lpthread -lgtest_main

TestDraw: TestDraw.c++ Resource.c++ Reporter.c++ Clock.c++
	g++ -pedantic -Wall Resource.c++ Reporter.c++ Clock.c++ TestDraw.c++ -o TestDraw \
      -framework SDL2 -framework SDL2_image -framework SDL2_mixer

TestAnimate: TestAnimate.c++ Resource.c++ Reporter.c++ Clock.c++
	g++ -pedantic -Wall Resource.c++ Reporter.c++ Clock.c++ TestAnimate.c++ -o TestAnimate \
      -framework SDL2 -framework SDL2_image -framework SDL2_mixer
      
TestScriptDraw: TestScriptDraw.c++ Resource.c++ Reporter.c++ Clock.c++ Lexer.c++ Parser.c++ Token.c++ Variant.c++ Util.c++ Environment.c++ System.c++
	g++ -pedantic -Wall TestScriptDraw.c++ Resource.c++ Reporter.c++ Clock.c++ Lexer.c++ Parser.c++ Token.c++ Variant.c++ Util.c++ Environment.c++ System.c++ -o TestScriptDraw \
      -framework SDL2 -framework SDL2_image -framework SDL2_mixer -lgtest -lpthread -lgtest_main


TestDemos: TestDemos.c++ Resource.c++ Reporter.c++ Clock.c++ Lexer.c++ Parser.c++ Token.c++ Variant.c++ Util.c++ Environment.c++ System.c++ Script.c++
	g++ -pedantic -Wall TestDemos.c++ Resource.c++ Reporter.c++ Clock.c++ Lexer.c++ Parser.c++ Token.c++ Variant.c++ Util.c++ Environment.c++ System.c++ Script.c++ -o TestDemos \
      -framework SDL2 -framework SDL2_image -framework SDL2_mixer -lgtest -lpthread -lgtest_main

clean:
	rm -f *.o TestCore TestDraw TestAnimate TestScriptDraw TestDemos