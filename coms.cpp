#include <iostream>
#include <string>
#include <sio_client.h>


using namespace std;

void OnOpenSocket(const string& nsp){
    cout << "Connected to server: " << nsp << endl;
}

void OnCloseSocket(const string& nsp){
    cout << "Disconnected from server: " << nsp << endl;
}

void OnOpenListener(){
    cout << "Connection opened" << endl;
}

void OnCloseListener(const sio::client::close_reason &reason){
    cout << "Connection Closed. Reason: " << reason << endl;
}

void OnCallback(const string& name, sio::message::ptr const& data, bool isAck, sio::message::list& ack_resp){
    // Check if the incoming message is a string
    if (data->get_flag() == sio::message::flag_string) {
        string received_message = data->get_string();
        cout << "Received message from server: " << received_message << endl;
    }

}

int main() {

    sio::client client;

    client.connect("http://localhost:3000");

    string message_to_send = "Hello from cpp";
    client.socket()->emit("cppEvent", message_to_send, nullptr);

    client.socket()->on("cppEvent", OnCallback);

    // handling connection events from websocket server
    client.set_socket_open_listener(OnOpenSocket);
    client.set_open_listener(OnOpenListener);
    client.set_close_listener(OnCloseListener);
    client.set_socket_close_listener(OnCloseSocket);

    cin.ignore();

    return 0;

}