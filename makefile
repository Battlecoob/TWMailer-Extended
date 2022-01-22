# $@: target, $^ dependencies, % pattern

COMPILER=g++
FLAGS=-Wall -pthread -std=c++11 
LIBS= -lldap -llber 
OBJDIR= obj
OTHER= $(addprefix $(OBJDIR)/, functions.o message.class.o user.struct.o)
SERVER= $(addprefix $(OBJDIR)/, server.class.o messageHandler.class.o clientConnected.class.o clientHandler.class.o clientStats.class.o)
CLIENT= $(addprefix $(OBJDIR)/, client.class.o inputValidator.o)
DATEBASE= $(addprefix $(OBJDIR)/,)

all: client server

client: obj/client.o $(CLIENT) $(OTHER)
	$(COMPILER) $(FLAGS) $^ -o $@ $(LIBS)

server: obj/server.o $(SERVER) $(OTHER) $(DATEBASE)
	$(COMPILER) $(FLAGS) $^ -o $@ $(LIBS)

obj/%.o: %.cpp 
	$(COMPILER) $(FLAGS) -c $^ -o $@

obj/%.o: Other/%.cpp 
	$(COMPILER) $(FLAGS) -c $^ -o $@

obj/%.o: Database/%.cpp 
	$(COMPILER) $(FLAGS) -c $^ -o $@

obj/%.o: Server/%.cpp
	$(COMPILER) $(FLAGS) -c $^ -o $@

obj/%.o: Client/%.cpp
	$(COMPILER) $(FLAGS) -c $^ -o $@

clean:
	rm client server obj/*.o



# # $@: target, $^ dependencies, % pattern

# COMPILER=g++
# FLAGS=-Wall -pthread -std=c++11 
# LIBS= -lldap -llber 
# OBJDIR= obj
# OTHER= $(addprefix $(OBJDIR)/, functions.o)
# SERVER= $(addprefix $(OBJDIR)/, server.class.o)
# CLIENT= $(addprefix $(OBJDIR)/, client.class.o inputValidator.o)
# # DATEBASE= $(addprefix $(OBJDIR)/,)

# all: client server

# client: obj/client.o $(CLIENT) $(OTHER)
# 	$(COMPILER) $(FLAGS) $^ -o $@ $(LIBS)

# server: obj/server.o $(SERVER) $(OTHER) $(DATEBASE)
# 	$(COMPILER) $(FLAGS) $^ -o $@ $(LIBS)

# obj/%.o: %.cpp 
# 	$(COMPILER) $(FLAGS) -c $^ -o $@

# obj/%.o: Infrastructure/%.cpp 
# 	$(COMPILER) $(FLAGS) -c $^ -o $@

# obj/%.o: Database/%.cpp 
# 	$(COMPILER) $(FLAGS) -c $^ -o $@

# obj/%.o: SERVER/%.cpp
# 	$(COMPILER) $(FLAGS) -c $^ -o $@

# obj/%.o: CLIENT/%.cpp
# 	$(COMPILER) $(FLAGS) -c $^ -o $@

# clean:
# 	rm *.o client server obj/*.o