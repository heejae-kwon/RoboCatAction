EXE=RoboCatServer.exe

GPP_SWITCHES=-std=c++11 -Wno-multichar

INCLUDEDIR1=./RoboCat/Inc
INCLUDEDIR2=./RoboCatServer/Inc
INCLUDEDIR3=./SDL/include

GPPPARAMS=$(GPP_SWITCHES) -I$(INCLUDEDIR1) -I$(INCLUDEDIR2) -I$(INCLUDEDIR3)

server:
	g++ $(GPPPARAMS) -c RoboCat/Src/AckRange.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/DeliveryNotificationManager.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/Engine.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/GameObject.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/GameObjectRegistry.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/InFlightPacket.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/InputState.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/MemoryBitStream.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/Mouse.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/Move.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/MoveList.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/NetworkManager.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/RoboCat.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/RoboCatPCH.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/RoboMath.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/ScoreBoardManager.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/SocketAddress.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/SocketAddressFactory.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/SocketUtil.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/StringUtils.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/TCPSocket.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/Timing.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/UDPSocket.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/World.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/Yarn.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/HyperYarn.cpp
	g++ $(GPPPARAMS) -c RoboCat/Src/BallOfYarn.cpp
	g++ $(GPPPARAMS) -c RoboCatServer/Src/ClientProxy.cpp
	g++ $(GPPPARAMS) -c RoboCatServer/Src/MouseServer.cpp
	g++ $(GPPPARAMS) -c RoboCatServer/Src/NetworkManagerServer.cpp
	g++ $(GPPPARAMS) -c RoboCatServer/Src/ReplicationManagerServer.cpp
	g++ $(GPPPARAMS) -c RoboCatServer/Src/ReplicationManagerTransmissionData.cpp
	g++ $(GPPPARAMS) -c RoboCatServer/Src/RoboCatServer.cpp
	g++ $(GPPPARAMS) -c RoboCatServer/Src/RoboCatServerPCH.cpp
	g++ $(GPPPARAMS) -c RoboCatServer/Src/Server.cpp
	g++ $(GPPPARAMS) -c RoboCatServer/Src/ServerMain.cpp
	g++ $(GPPPARAMS) -c RoboCatServer/Src/YarnServer.cpp
	g++ $(GPPPARAMS) -c RoboCatServer/Src/HyperYarnServer.cpp
	g++ $(GPPPARAMS) -c RoboCatServer/Src/BallOfYarnServer.cpp

	g++ -o $(EXE) AckRange.o DeliveryNotificationManager.o Engine.o GameObject.o GameObjectRegistry.o InFlightPacket.o InputState.o MemoryBitStream.o Mouse.o Move.o MoveList.o NetworkManager.o RoboCat.o RoboCatPCH.o RoboMath.o ScoreBoardManager.o SocketAddress.o SocketAddressFactory.o SocketUtil.o StringUtils.o TCPSocket.o Timing.o UDPSocket.o World.o Yarn.o HyperYarn.o BallOfYarn.o ClientProxy.o MouseServer.o NetworkManagerServer.o ReplicationManagerServer.o ReplicationManagerTransmissionData.o RoboCatServer.o RoboCatServerPCH.o Server.o ServerMain.o YarnServer.o HyperYarnServer.o BallOfYarnServer.o

clean:
	rm *.o
	rm $(EXE)