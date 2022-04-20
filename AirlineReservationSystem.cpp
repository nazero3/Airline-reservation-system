#include "AirlineReservationSystem.h"

void AirlineReservationSystem::addPassenger(const std::string &firstname, const std::string &lastname) {
    Passenger * newPass = new Passenger(firstname, lastname);
    BSTNode<Passenger>* findPass = new BSTNode<Passenger>();
    findPass = passengers.search(*newPass);
    if(findPass == NULL)
        passengers.insert(*newPass);
}

Passenger* AirlineReservationSystem::searchPassenger(const std::string& firstname, const std::string& lastname) {

    BSTNode<Passenger>* tmp = this->passengers.search(Passenger::Passenger(firstname, lastname));
    Passenger* x = new Passenger(tmp->data.getFirstname(), tmp->data.getLastname());
    return x;
}
void AirlineReservationSystem::addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    BSTNode<Flight>* flightNode = new BSTNode<Flight>();
    flightNode = flights.getRoot();
    Flight* f = new Flight(flightCode, departureTime, arrivalTime, departureCity, arrivalCity, economyCapacity, businessCapacity);
    while (flightNode != NULL && flightNode->data != *f)
        flightNode = flights.getSuccessor(flightNode, inorder);
    flights.insert(*f);
   
    
}

std::vector<Flight *> AirlineReservationSystem::searchFlight(const std::string &departureCity, const std::string &arrivalCity) {
    std::vector<Flight *> fs{};
    BSTNode<Flight>* flight = this->flights.getRoot();
    if (flight == NULL) return fs;
    while (flight != NULL)
    {
        if (flight->data.getDepartureCity() == departureCity && flight->data.getArrivalCity() == arrivalCity) {
            //flightCode, departureTime, arrivalTime, departureCity, arrivalCity, economyCapacity, businessCapacity
            Flight* a = new Flight(flight->data.getFlightCode(), flight->data.getDepartureTime(), flight->data.getArrivalTime(), flight->data.getDepartureCity(), flight->data.getArrivalCity(),
                flight->data.getEconomyCapacity(), flight->data.getBusinessCapacity());
            fs.push_back(a);
            }
        else {
            flights.getSuccessor(flight, inorder);
        }
    }
    
    return fs;
    

}

void AirlineReservationSystem::issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    Passenger* person = new Passenger(firstname, lastname);
    BSTNode<Flight>* flightNode = new BSTNode<Flight>();
    flightNode = flights.getRoot();
    
    if (this->passengers.contains(passengers.search(*person))) {
        while (flightNode->data.getFlightCode() != flightCode && flightNode != NULL)
        {
            flightNode = flights.getSuccessor(flightNode, inorder);
        }
    }

    Ticket* t = new Ticket(person, &flightNode->data,ticketType);
}

void AirlineReservationSystem::saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    Passenger* passenger = new Passenger(firstname, lastname);
    BSTNode<Flight>* flightNode = new BSTNode<Flight>();
    BSTNode<Passenger>* passNode = new BSTNode<Passenger>();
    flightNode = flights.getRoot();
    passNode = passengers.getRoot();
    while (flightNode->data.getFlightCode() != flightCode && flightNode != NULL) {
        flightNode = flights.getSuccessor(flightNode, preorder);
        if (flightNode == NULL)
            break;
    }
        
    while (passNode->data.getFirstname() != firstname && passNode->data.getLastname() != lastname && passNode != NULL)
    {
        passNode = passengers.getSuccessor(passNode, preorder);
        if (passNode == NULL)
            break;
    }
    
    //Flight* flight = &flightNode->data;
    Ticket* ticket = new Ticket(passenger,&flightNode->data,ticketType);
    
    freeTicketRequests.enqueue(*ticket);
}

void AirlineReservationSystem::executeTheFlight(const std::string &flightCode) {
    Queue<Ticket>* tickets = new Queue<Ticket>();

    BSTNode<Flight>* flightNode = new BSTNode<Flight>();
    flightNode = flights.getRoot();
    while (flightNode->data.getFlightCode() != flightCode)
        flightNode = flights.getSuccessor(flightNode, preorder);
    for (int i = 0; i < freeTicketRequests.size(); i++)
    {
        if (freeTicketRequests.peek().getFlight()->getFlightCode() == flightCode) {
            if (!flightNode->data.isCompleted() && !freeTicketRequests.isEmpty()) {
                flightNode->data.addTicket(freeTicketRequests.dequeue());
            }
            else if(!freeTicketRequests.isEmpty()) {
                tickets->enqueue(freeTicketRequests.dequeue()) ;
            }
        }

    }
    for (int i = 0; i < tickets->size(); i++)
    {
        freeTicketRequests.enqueue(tickets->dequeue());
    }

    flightNode->data.isCompleted();

}

void AirlineReservationSystem::print() const {
    std::cout << "# Printing the airline reservation system ..." << std::endl;

    std::cout << "# Passengers:" << std::endl;
    passengers.print(inorder);

    std::cout << "# Flights:" << std::endl;
    flights.print(inorder);

    std::cout << "# Free ticket requests:" << std::endl;
    freeTicketRequests.print();

    std::cout << "# Printing is done." << std::endl;
}
