import java.util.*;



public class Elevator{

    int currentFloor;
    Direction direction;
    PriorityQueue<Request>upQueue;
    PriorityQueue<Request>downQueue;



    public Elevator(int currentFloor){
        this.currentFloor=currentFloor;
        this.direction=Direction.IDLE;
        upQueue=new PriorityQueue<Request>((a,b)-> a.desiredFloor-b.desiredFloor);
        downQueue=new PriorityQueue<Request>((a,b)->b.desiredFloor-a.desiredFloor);
    }

    public void sendUpRequest(Request upRequest){
        if(upRequest.location==Location.OUTSIDE_ELEVATOR){
            upQueue.offer(new Request(upRequest.currentFloor,upRequest.currentFloor
            ,Direction.UP,Location.OUTSIDE_ELEVATOR));
            System.out.println("Append up request going to floor");
        }
        upQueue.offer(upRequest);
        System.out.println("Append up request going to floor");
    }

    public void sendDownRequest(Request downRequest){
        if(downRequest.location==Location.OUTSIDE_ELEVATOR){
            downQueue.offer(new Request(downRequest.currentFloor,
            downRequest.currentFloor,
            Direction.DOWN,Location.OUTSIDE_ELEVATOR));
            System.out.println("Append down request going to floor");
        }

        downQueue.offer(downRequest);
        System.out.println("Append down request going to floor");
    }

    public void run(){
        while(!upQueue.isEmpty() || !downQueue.isEmpty()){
            processRequests();
        }
        System.out.println("Finished all requests");
        this.direction=Direction.IDLE;
    }

    private void processRequests(){
        if(this.direction==Direction.UP || this.direction==Direction.IDLE){
            processUpRequest();
            processDownRequest();
        }
        else {
            processDownRequest();
            processUpRequest();
        }
    }

    private void processUpRequest(){
        while(!upQueue.isEmpty()){
            Request upRequest=upQueue.poll();
            this.currentFloor=upRequest.desiredFloor;
            System.out.println("Processing up requests. Elevator stopped at floor "+ this.currentFloor+".");
        }
        if(!downQueue.isEmpty()){
            this.direction=Direction.DOWN;
        }
        else {
            this.direction=Direction.IDLE;
        }
    }

    private void processDownRequest(){
        while(!downQueue.isEmpty()){
            Request downRequest=downQueue.poll();
            this.currentFloor=downRequest.desiredFloor;
            System.out.println("Processing down requests. Elevator stopped at floor "+ this.currentFloor+".");
        }
        if(!downQueue.isEmpty()){
            this.direction=Direction.UP;
        }
        else {
            this.direction=Direction.IDLE;
        }
    }

    public static void main(String[] args){
        Elevator elevator=new Elevator(0);
        Request upRequest1 = new Request(elevator.currentFloor, 5, Direction.UP, Location.INSIDE_ELEVATOR);
        Request upRequest2 = new Request(elevator.currentFloor, 3, Direction.UP, Location.INSIDE_ELEVATOR);

        Request downRequest1 = new Request(elevator.currentFloor, 1, Direction.DOWN, Location.INSIDE_ELEVATOR);
        Request downRequest2 = new Request(elevator.currentFloor, 2, Direction.DOWN, Location.INSIDE_ELEVATOR);
        Request downRequest3 = new Request(4, 0, Direction.DOWN, Location.OUTSIDE_ELEVATOR);

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

}