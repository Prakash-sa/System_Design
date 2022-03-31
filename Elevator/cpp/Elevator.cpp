#include <bits/stdc++.h>
using namespace std;

enum class Direction{
    UP,
    DOWN,
    IDLE
};

enum class Location{
    INSIDE_ELEVATOR,
    OUTSIDE_ELEVATOR
};


class Request{
    public:
    int currentFloor;
    int desiredFloor;
    Direction direction;
    Location location;

    Request(int currentFloor1,int desiredFloor1,Direction direction1,Location location1){
        currentFloor=currentFloor1;
        desiredFloor=desiredFloor1;
        direction=direction1;
        location=location1;
    }
};

class Elevator{

    public:
    int currentFloor;
    Direction direction;
    priority_queue<Request,vector<Request>,greater<Request>> upQueue;
    priority_queue<Request> downQueue;

    Elevator(int currentFloor1){
        currentFloor=currentFloor1;
        direction=Direction::IDLE;
    }

    void sendUpRequest(Request upRequest){
        if(upRequest.location==Location::OUTSIDE_ELEVATOR){
            upQueue.push(new Request(upRequest.currentFloor,
            upRequest.currentFloor,
            Direction::UP,
            Location::OUTSIDE_ELEVATOR));
            cout<<"Append up request going to floor "<<upRequest.currentFloor<<endl;
        }
        upQueue.push(upRequest);
        cout<<"Append up request going to floor "<<upRequest.desiredFloor<<endl;
    }

    void sendDownRequest(Request downRequest){
        if(downRequest.location==Location::OUTSIDE_ELEVATOR){
            downQueue.push(new Request(downRequest.currentFloor,
            downRequest.currentFloor,Direction::DOWN,Location::OUTSIDE_ELEVATOR));
            cout<<"Append up request going to floor "<<downRequest.currentFloor<<endl;
        }
        downQueue.push(downRequest);
        cout<<"Append up request going to floor "<<downRequest.desiredFloor<<endl;
    }

    void processUpRequest(){
        while(!upQueue.empty()){
            Request upRequest=upQueue.top();
            upQueue.pop();
            currentFloor=upRequest.desiredFloor;
            cout<<"Processing up request. Elevator stopped at floor "<<currentFloor<<endl; 
        }
        if(!downQueue.empty()){
            direction=Direction::DOWN;
        }
        else direction=Direction::IDLE;
    }


    void processDownRequest(){
        while(!downQueue.empty()){
            Request downRequest=downQueue.front();
            downQueue.pop();
            currentFloor=downRequest.desiredFloor;
            cout<<"Processing up request. Elevator stopped at floor "<<currentFloor<<endl; 
        }
        if(!upQueue.empty()){
            direction=Direction::UP;
        }
        else direction=Direction::IDLE;
    }

    void processRequest(){
        if(direction==Direction::IDLE || direction==Direction::UP){
            processUpRequest();
            processDownRequest();
        }
        else {
            processDownRequest();
            processUpRequest();            
        }
    }

    
    void run(){
        while(!upQueue.empty() || !downQueue.empty()){
            processRequest();
        }
        cout<<"Finished all request\n";
        direction=Direction::IDLE;
    }

};

int main(){
    Elevator elevator=new Elevator(0);
    
    Request upRequest1 = new Request(elevator.currentFloor, 5, Direction::UP, Location::INSIDE_ELEVATOR);
    Request upRequest2 = new Request(elevator.currentFloor, 3, Direction::UP, Location::INSIDE_ELEVATOR);

    Request downRequest1 = new Request(elevator.currentFloor, 1, Direction::DOWN, Location::INSIDE_ELEVATOR);
    Request downRequest2 = new Request(elevator.currentFloor, 2, Direction::DOWN, Location::INSIDE_ELEVATOR);
    Request downRequest3 = new Request(4, 0, Direction::DOWN, Location::OUTSIDE_ELEVATOR);

    // Two people inside of the elevator pressed button to go up to floor 5 and 3.
    elevator.sendUpRequest(upRequest1);
    elevator.sendUpRequest(upRequest2);

    // One person outside of the elevator at floor 4 pressed button to go down to floor 0
    elevator.sendDownRequest(downRequest3);

    // Two person inside of the elevator pressed button to go down to floor 1 and 2.
    elevator.sendDownRequest(downRequest1);
    elevator.sendDownRequest(downRequest2);


    elevator.run();
}
