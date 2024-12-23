# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++17 -I./include -I./field -I./game -I./abilities -I./lb4

# Цель по умолчанию
all: test_class

# Сборка программы из объектных файлов
test_class: test_class.o field/FieldSegment.o field/Ship.o field/ShipManager.o field/Field.o game/Exceptions.o field/Cell.o abilities/Abilities.o abilities/AbilitiesManager.o game/User.o game/Bot.o game/Game.o game/GameState.o lb4/Observer.o  lb4/InputProcessor.o lb4/CommandMapper.o lb4/FieldRendering.o 
	$(CXX) $(CXXFLAGS) test_class.o field/FieldSegment.o field/Ship.o field/ShipManager.o field/Field.o game/Exceptions.o field/Cell.o abilities/Abilities.o abilities/AbilitiesManager.o game/User.o game/Bot.o game/Game.o game/GameState.o lb4/Observer.o lb4/InputProcessor.o lb4/CommandMapper.o lb4/FieldRendering.o -o test_class

# Компиляция test_class.cpp в test_class.o
src/test_class.o: src/test_class.cpp field/FieldSegment.h field/Ship.h field/ShipManager.h field/Field.h game/Exceptions.h field/Cell.h abilities/Abilities.h abilities/AbilitiesManager.h game/User.h game/Bot.h game/Game.h game/GameState.h lb4/Observer.h lb4/GameManage.h lb4/InputProcessor.h lb4/CommandMapper.h lb4/FieldRendering.h lb4/GameDisplay.h
	$(CXX) $(CXXFLAGS) -c src/test_class.cpp -o src/test_class.o

# Компиляция FieldSegment.cpp в FieldSegment.o
field/FieldSegment.o: field/FieldSegment.cpp field/FieldSegment.h
	$(CXX) $(CXXFLAGS) -c field/FieldSegment.cpp -o field/FieldSegment.o

# Компиляция Ship.cpp в Ship.o
field/Ship.o: field/Ship.cpp field/Ship.h
	$(CXX) $(CXXFLAGS) -c field/Ship.cpp -o field/Ship.o

# Компиляция ShipManager.cpp в ShipManager.o
field/ShipManager.o: field/ShipManager.cpp field/ShipManager.h
	$(CXX) $(CXXFLAGS) -c field/ShipManager.cpp -o field/ShipManager.o

# Компиляция Field.cpp в Field.o
field/Field.o: field/Field.cpp field/Field.h
	$(CXX) $(CXXFLAGS) -c field/Field.cpp -o field/Field.o

# Компиляция Exceptions.cpp в Exceptions.o
game/Exceptions.o: game/Exceptions.cpp game/Exceptions.h
	$(CXX) $(CXXFLAGS) -c game/Exceptions.cpp -o game/Exceptions.o

# Компиляция Cell.cpp в Cell.o
field/Cell.o: field/Cell.cpp field/Cell.h
	$(CXX) $(CXXFLAGS) -c field/Cell.cpp -o field/Cell.o

# Компиляция Abilities.cpp в Abilities.o
abilities/Abilities.o: abilities/Abilities.cpp abilities/Abilities.h
	$(CXX) $(CXXFLAGS) -c abilities/Abilities.cpp -o abilities/Abilities.o

# Компиляция AbilitiesManager.cpp в AbilitiesManager.o
abilities/AbilitiesManager.o: abilities/AbilitiesManager.cpp abilities/AbilitiesManager.h
	$(CXX) $(CXXFLAGS) -c abilities/AbilitiesManager.cpp -o abilities/AbilitiesManager.o

# Компиляция User.cpp в User.o
game/User.o: game/User.cpp game/User.h
	$(CXX) $(CXXFLAGS) -c game/User.cpp -o game/User.o

# Компиляция Bot.cpp в Bot.o
game/Bot.o: game/Bot.cpp game/Bot.h
	$(CXX) $(CXXFLAGS) -c game/Bot.cpp -o game/Bot.o

# Компиляция GameState.cpp в GameState.o
game/GameState.o: game/GameState.cpp game/GameState.h game/Game.h
	$(CXX) $(CXXFLAGS) -c game/GameState.cpp -o game/GameState.o

# Компиляция Game.cpp в Game.o
game/Game.o: game/Game.cpp game/Game.h game/GameState.h
	$(CXX) $(CXXFLAGS) -c game/Game.cpp -o game/Game.o

# Компиляция Observer.cpp в Observer.o
lb4/Observer.o: lb4/Observer.cpp lb4/Observer.h
	$(CXX) $(CXXFLAGS) -c lb4/Observer.cpp -o lb4/Observer.o

# Компиляция InputProcessor.cpp в InputProcessor.o
lb4/InputProcessor.o: lb4/InputProcessor.cpp lb4/InputProcessor.h
	$(CXX) $(CXXFLAGS) -c lb4/InputProcessor.cpp -o lb4/InputProcessor.o

# Компиляция CommandMapper.cpp в CommandMapper.o
lb4/CommandMapper.o: lb4/CommandMapper.cpp lb4/CommandMapper.h
	$(CXX) $(CXXFLAGS) -c lb4/CommandMapper.cpp -o lb4/CommandMapper.o

# Компиляция CommandMapper.cpp в CommandMapper.o
lb4/FieldRendering.o: lb4/FieldRendering.cpp lb4/FieldRendering.h
	$(CXX) $(CXXFLAGS) -c lb4/FieldRendering.cpp -o lb4/FieldRendering.o

# Очистка объектных файлов и исполняемого файла
clean:
	rm -f src/*.o field/*.o game/*.o abilities/*.o lb4/*.o test_class

# Указание, что цели 'all' и 'clean' являются псевдоцелями
.PHONY: all clean