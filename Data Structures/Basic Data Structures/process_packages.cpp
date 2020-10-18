/**
 * The goal of this problem is to simulate the processing of network packets.
 * @file process_packages.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 */
#include <iostream>
#include <queue>
#include <vector>

/**
 * Struct to store the arrival and procees time for a request.
 **/
struct Request {
    Request(int arrival_time, int process_time)
        : arrival_time(arrival_time), process_time(process_time) {}

    int arrival_time;
    int process_time;
};

/**
 * Struct to store the dropped status of request and start time of request.
 **/
struct Response {
    Response(bool dropped, int start_time)
        : dropped(dropped), start_time(start_time) {}

    bool dropped;
    int start_time;
};

/**
 * Class to simulate the Buffer
 **/
class Buffer {
   public:
    Buffer(int size) : size_(size) {}

    /**
     * Function to simulate the processing of a request
     * @param request 'Request' object.
     * @return 'Response' object.
     **/
    Response Process(const Request &request) {
        if (!finish_time_.empty()) {
            if (request.arrival_time >= finish_time_.front()) {
                finish_time_.pop();
            }
        }
        if (finish_time_.empty()) {
            if (size_ > 0) {
                finish_time_.push(request.arrival_time + request.process_time);
                return Response(false, request.arrival_time);
            } else {
                return Response(true, 0);
            }
        } else {
            if (size_ > finish_time_.size()) {
                int start = std::max(finish_time_.back(), request.arrival_time);
                finish_time_.push(start + request.process_time);
                return Response(false, start);
            } else {
                return Response(true, 0);
            }
        }
    }

   private:
    int size_;
    std::queue<int> finish_time_;
};

/**
 * Function to read request from console.
 * @return vector of Request
 **/
std::vector<Request> ReadRequests() {
    std::vector<Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

/**
 * Function to process the Request
 * @param requests vector of Request
 * @param buffer Buffer object
 * @return vector of Response
 **/
std::vector<Response> ProcessRequests(const std::vector<Request> &requests,
                                      Buffer *buffer) {
    std::vector<Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

/**
 * Function to print the result on to the screen.
 * @param responses vector of Response
 **/
void PrintResponses(const std::vector<Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time)
                  << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector<Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector<Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
