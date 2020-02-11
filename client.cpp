#include <pthread.h>
#include "client_wss.hpp"
#include "server_wss.hpp"
#include <future>

using namespace std;

using WssClient = SimpleWeb::SocketClient<SimpleWeb::WSS>;

int main() {
  WssClient client("localhost:8080/echo", false); // Second Client() parameter set to false: no certificate verification
  client.on_message = [](shared_ptr<WssClient::Connection> connection, shared_ptr<WssClient::InMessage> in_message) {
    cout << "Client: Message received: \"" << in_message->string() << "\"" << endl;
    
    string out_message;
	cout << "Enter message ('Close' to close connection): ";
	cin >> out_message;
	
	if(out_message != "Close"){
	  cout << "Client: Sending message: \"" << out_message << "\"" << endl;
	  connection->send(out_message);
    }
    else{
	  cout << "Client: Sending close connection" << endl;
	  connection->send_close(1000);
	}
  };

  client.on_open = [](shared_ptr<WssClient::Connection> connection) {
    cout << "Client: Opened connection" << endl;
    
    string out_message;
    cout << "Enter message ('Close' to close connection): ";
	cin >> out_message;
	
	if(out_message != "Close"){
	  cout << "Client: Sending message: \"" << out_message << "\"" << endl;
	  connection->send(out_message);
    }
    else{
	  cout << "Client: Sending close connection" << endl;
	  connection->send_close(1000);
	}
  };

  client.on_close = [](shared_ptr<WssClient::Connection> connection, int status, const string & /*reason*/) {
    cout << "Client: Closed connection with status code " << status << endl;
  };

  // See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
  client.on_error = [](shared_ptr<WssClient::Connection> /*connection*/, const SimpleWeb::error_code &ec) {
    cout << "Client: Error: " << ec << ", error message: " << ec.message() << endl;
  };

  client.start();
  
}
