#pragma warning (disable:4786)
#pragma warning (disable:4503)

#include "RailSystem.h"

void RailSystem::reset(void) {
    for (auto &e : cities) {
        e.second->visited = false;
        // set cost and distance to infinity
        e.second->total_fee = INT_MAX;
        e.second->total_distance = INT_MAX;
        e.second->from_city = "";
    }
}

RailSystem::RailSystem(string const &filename) {
    load_services(filename);
}

void RailSystem::load_services(string const &filename) {

    ifstream inf(filename.c_str());
    string from, to;
    int fee, distance;

    while ( inf.good() ) {

        // Read in the from city, to city, the fee, and distance.
        inf >> from >> to >> fee >> distance;

        if ( inf.good() ) {
            // add city if it does not exist yet
            if (cities.find(from) == cities.end()) {
                City* city = new City(from);
                cities[city->name] = city;
            }
            // add city if it does not exist yet
            if (cities.find(to) == cities.end()) {
                City* city = new City(to);
                cities[city->name] = city;
            }
            // add services that go FROM this city into TO city
            if (outgoing_services.find(from) == outgoing_services.end())
                outgoing_services[from] = list<Service*>{};
            outgoing_services[from].push_back(new Service{to, fee, distance});
        }
    }

    inf.close();
}

RailSystem::~RailSystem(void) {
    // clear city
    for (auto &pair : cities) {
        delete pair.second;
    }
    // clear services
    for (auto &pair : outgoing_services) {
        for (auto &serv : pair.second) {
            delete serv;
        }
    }
}

void RailSystem::output_cheapest_route(const string& from,
                const string& to, ostream& out) {

    reset();
    pair<int, int> totals = calc_route(from, to);

    if (totals.first == INT_MAX) {
        out << "There is no route from " << from << " to " << to << "\n";
    } else {
        out << "The cheapest route from " << from << " to " << to << "\n";
        out << "costs " << totals.first << " euros and spans " << totals.second
            << " kilometers\n";
        cout << recover_route(to) << "\n\n";
    }
}

bool RailSystem::is_valid_city(const string& name) {

    return cities.count(name) == 1;
}

pair<int, int> RailSystem::calc_route(string from, string to) {
    // You can use another container, unvisited
    priority_queue<City*, vector<City*>, Cheapest> candidates;

    // Implement Dijkstra's shortest path algorithm to
    // find the cheapest route between the cities

    // Mark initial city as known location
    cities[from]->total_fee = 0;
    cities[from]->total_distance = 0;

    // add all nodes to be examined
    for (const auto&pair : cities) {
        candidates.push(pair.second);
    }

    while (candidates.size() > 0) {
        // find nearest city
        City* closest = candidates.top();
        if (closest->total_distance == INT_MAX) {
            // there is a disconnected subgraph, we can quit search
            candidates.empty();
            break;
        }
        // mark as visited, remove
        cities[closest->name]->visited = true;
        candidates.pop();
        // if we found the city as "closest", we can quit search
        if (closest->name == to) {
            candidates.empty();
            break;
        }
        // iterate over adjacent vertices
        for (const auto& neibour_service : outgoing_services[closest->name]) {
            // relaxation
            City* neibour = cities[neibour_service->destination];
            int alt_fee = closest->total_fee + neibour_service->fee;
            if (alt_fee < neibour->total_fee)
            {
                neibour->total_fee = alt_fee;
                // distance follows fee
                int alt_dist = closest->total_distance + neibour_service->distance;
                neibour->total_distance = alt_dist;
                // record previous node
                neibour->from_city = closest->name;
            }
        }
        std::make_heap(const_cast<City**>(&candidates.top()),
                        const_cast<City**>(&candidates.top()) + candidates.size(),
                        Cheapest());
    }

    // Return the total fee and total distance.
    // Return (INT_MAX, INT_MAX) if not path is found.
    if (cities[to]->visited) {
            return pair<int,int>(cities[to]->total_fee, cities[to]->total_distance);
    } else {
            return pair<int,int>(INT_MAX, INT_MAX);
    }

}

string RailSystem::recover_route(const string& city) {
    // walk backwards through the cities
    // container to recover the route we found
    City* c = cities[city];
    // add last city
    string ret = c->name;
    while (c->from_city != "") {
        // add cities in reverse
        c = cities[c->from_city];
        ret = c->name + " to " + ret;
    }
    // return string
    return ret;
}


Route RailSystem::getCheapestRoute(const string& from, const string& to){
    assert(is_valid_city(from));
    assert(is_valid_city(to));
    reset();
    pair<int, int> p =  calc_route(from,to);
    return Route(from,to,p.first,p.second);
}
